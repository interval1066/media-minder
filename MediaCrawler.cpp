#include "stdafx.h"
#include "MediaCrawler.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;

namespace internal
{
    // Function to parse comma-separated extensions into a set
    std::unordered_set<std::string>
        parseExtensions(const std::string& extStr)
    {
        std::unordered_set<std::string> extensions;
        std::istringstream stream(extStr);
        std::string ext;

        while (std::getline(stream, ext, ',')) {
            if (!ext.empty())
                extensions.insert("." + ext); // Ensure extensions have a dot prefix
        }
        return extensions;
    }

    // Function to check if a string is valid UTF-8 (for Linux/macOS)
    bool
        isValidUTF8(const std::string& str)
    {
        int numBytes = 0;
        for (unsigned char c : str) {
            if (numBytes == 0) {
                if ((c >> 5) == 0b110) numBytes = 1;       // 2-byte UTF-8 sequence
                else if ((c >> 4) == 0b1110) numBytes = 2; // 3-byte UTF-8 sequence
                else if ((c >> 3) == 0b11110) numBytes = 3; // 4-byte UTF-8 sequence
                else if (c >> 7) return false; // Invalid UTF-8 start byte
            }
            else {
                if ((c >> 6) != 0b10) return false; // Invalid continuation byte
                --numBytes;
            }
        }
        return numBytes == 0;
    }

    // Function to recursively scan directories
    void
    scanDirectory(const fs::path& directory, const std::unordered_set<std::string>& validExtensions)
    {
        try {
            for (const auto& entry : fs::recursive_directory_iterator(directory, fs::directory_options::skip_permission_denied)) {
                if (entry.is_regular_file()) {
                    std::string ext = entry.path().extension().string();
                    if (validExtensions.find(ext) != validExtensions.end()) {
#ifdef _WIN32
                        // Use wstring for Unicode filenames on Windows
                        std::wcout << entry.path().wstring() << std::endl;
#else
                        std::string filename = entry.path().string();
                        if (isValidUTF8(filename)) {
                            std::cout << filename << std::endl;
                        } // Ignore non-UTF-8 filenames
#endif
                    }
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error scanning directory: " << e.what() << std::endl;
        }
    }
}
