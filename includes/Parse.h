#pragma once

/**
 * @file Parse.h
 * @brief Obsahuje funkcie na parsovanie textovych riadkov do CNC prikazov.
 *
 * Tento subor obsahuje funkcie na prevod textovych riadkov do strukturovanych
 * prikazov pre dalsie spracovanie a optimalizaciu.
 */

#include <string>
#include <vector>
#include <memory>
#include "Command.h"

/**
 * @brief Parsuje jeden riadok CNC kodu do objektu Command.
 *
 * @param line Textovy riadok na parsovanie.
 * @return Ukazovatel na vytvoreny Command, alebo nullptr ak parsovanie zlyha.
 */
std::shared_ptr<Command> parseCommand(const std::string& line);

/**
 * @brief Parsuje viacero riadkov CNC kodu.
 *
 * @param lines Vektor textovych riadkov na parsovanie.
 * @return Vektor ukazovatelov na prikazy.
 */
std::vector<std::shared_ptr<Command>> parseCommands(const std::vector<std::string>& lines);
