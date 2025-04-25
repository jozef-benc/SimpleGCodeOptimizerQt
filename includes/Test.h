#pragma once

/**
 * @file Test.h
 * @brief Obsahuje funkcie na optimalizaciu a testovanie CNC prikazov.
 *
 * Tento subor obsahuje testovacie funkcie na detekciu duplicit, navratov
 * a celkovu optimalizaciu CNC prikazov podla zadanych pravidiel.
 */

#include <vector>
#include <memory>

class Command;
class MovementCommand;

namespace impl
{
/**
 * @brief Pokusi sa pretypovat prikaz na MovementCommand.
 *
 * @param command Prikaz na konverziu.
 * @return Ukazovatel na MovementCommand alebo nullptr.
 */
const MovementCommand* castToMovementCommand(const Command& command);
}

/**
 * @brief Otestuje, ci su dva prikazy identicke (duplicita).
 *
 * @param current Aktualny prikaz.
 * @param previous Predchadzajuci prikaz.
 * @return true ak NIE su duplicity, false ak su.
 */
bool testDuplicity(const Command& current, const Command& previous);

/**
 * @brief Otestuje, ci prikaz nepredstavuje navrat na predoslu poziciu.
 *
 * @param current Aktualny prikaz.
 * @param previous Predchadzajuci prikaz (ignoruje sa).
 * @param previousOfPrevious Predchadzajuci predchadzajuci prikaz.
 * @return true ak sa nevraciame, false ak ano.
 */
bool testReturnToPoint(const Command& current, const Command& previous, const Command& previousOfPrevious);

/**
 * @brief Moznosti optimalizacie CNC kodu.
 */
enum class EOptimizeMode
{
	the_same_movement = 0x00'01, ///< Odstranit pohyby na rovnake miesto.
	returning_back    = 0x00'02, ///< Odstranit navraty spat na bod.
};

/**
 * @brief Operator OR pre kombinovanie optimalizacnych modov.
 *
 * @param op1 Prvy mod.
 * @param op2 Druhy mod.
 * @return Skombinovane mody.
 */
EOptimizeMode operator | (const EOptimizeMode op1, const EOptimizeMode op2);

/**
 * @brief Operator AND pre kontrolu, ci je mod zapnuty.
 *
 * @param op1 Prvy mod.
 * @param op2 Druhy mod.
 * @return true ak je mod aktivny.
 */
bool operator & (const EOptimizeMode op1, const EOptimizeMode op2);

/**
 * @brief Optimalizuje zoznam CNC prikazov podla zvoleneho modu.
 *
 * @param input Vstupne prikazy.
 * @param mode Optimalizacny mod.
 * @return Optimalizovane prikazy.
 */
std::vector<std::shared_ptr<Command>> optimize(std::vector<std::shared_ptr<Command>> input, const EOptimizeMode mode);
