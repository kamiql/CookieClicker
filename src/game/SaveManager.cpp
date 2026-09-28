#include "game/SaveManager.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <stdexcept>

SaveData SaveManager::load(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        return {};
    }

    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Spielstand konnte nicht geöffnet werden.");
    }

    nlohmann::json json;
    file >> json;

    SaveData data;

    data.cookies = json.value("cookies", std::uint64_t{0});


    return data;
}

void SaveManager::save(
    const std::filesystem::path& path,
    const SaveData& data
) {
    if (!path.parent_path().empty()) {
        std::filesystem::create_directories(path.parent_path());
    }

    const nlohmann::json json = {
        {"cookies", data.cookies}
    };

    std::ofstream file(path, std::ios::trunc);
    if (!file) {
        throw std::runtime_error("Spielstand konnte nicht geschrieben werden.");
    }

    file << json.dump(2) << '\n';

    if (!file) {
        throw std::runtime_error("Fehler beim Schreiben des Spielstands.");
    }
}