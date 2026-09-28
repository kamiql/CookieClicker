#pragma once

#include "game/SaveData.hpp"

#include <filesystem>

class SaveManager {
public:
    static SaveData load(const std::filesystem::path& path);
    static void save(const std::filesystem::path& path, const SaveData& data);
};