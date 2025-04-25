#pragma once

/**
 * @file Io.h
 * @brief Obsahuje funkcie na nacitanie a zapisovanie riadkov zo suboru.
 *
 * Tento subor poskytuje zakladne IO operacie pre nacitanie a zapis CNC suborov
 */

#include <string>
#include <vector>
#include <filesystem>

/**
 * @brief Nacita vsetky riadky zo suboru.
 *
 * @param fileNameWithPath Cesta a nazov suboru, z ktoreho nacitavame.
 * @return Vektor riadkov nacitanych zo suboru.
 */
std::vector<std::string> readLinesFromFile(const std::filesystem::path& fileNameWithPath);

/**
 * @brief Zapise vsetky riadky do suboru.
 *
 * @param fileNameWithPath Cesta a nazov suboru, do ktoreho zapisujeme.
 * @param lines Vektor riadkov na zapisanie.
 */
void writeLinesToFile(const std::filesystem::path& fileNameWithPath, const std::vector<std::string>& lines);
