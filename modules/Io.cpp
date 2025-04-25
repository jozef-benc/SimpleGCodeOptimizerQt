#include "Io.h"
#include <fstream>
#include <stdexcept>

/**
 * Funkcia nacita vsetky riadky zo suboru a vrati ich ako vektor stringov.
 */
std::vector<std::string> readLinesFromFile(const std::filesystem::path& fileNameWithPath)
{
    std::vector<std::string> lines;
    std::ifstream file(fileNameWithPath);

    // Skontrolujeme, ci sa subor podarilo otvorit
    if (!file.is_open()) {
        // Ak sa nepodari otvorit subor, vyhodime vynimku
        throw std::runtime_error("Unable to open file for reading: " + fileNameWithPath.string());
    }

    std::string line;
    // Citame subor po jednotlivych riadkoch
    while (std::getline(file, line)) {
        lines.push_back(line); // Pridame kazdy riadok do vektora
    }

    return lines; // Vratime nacitane riadky
}

/**
 * Funkcia zapise vsetky riadky zo vstupneho vektora do suboru.
 */
void writeLinesToFile(const std::filesystem::path& fileNameWithPath, const std::vector<std::string>& lines)
{
    std::ofstream file(fileNameWithPath);

    // Skontrolujeme, ci sa subor podarilo otvorit na zapis
    if (!file.is_open()) {
        // Ak sa nepodari otvorit subor na zapis, vyhodime vynimku
        throw std::runtime_error("Unable to open file for writing: " + fileNameWithPath.string());
    }

    // Prechadzame vsetky riadky a zapisujeme ich do suboru
    for (const auto& line : lines) {
        file << line << '\n'; // Kazdy riadok ukoncime novym riadkom v subore
    }
}
