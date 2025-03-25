#pragma once

#include <filesystem>
#include <unordered_set>
#include <string>

namespace fs = std::filesystem;

void scanDirectory(const fs::path&, const std::unordered_set<std::string>&);
