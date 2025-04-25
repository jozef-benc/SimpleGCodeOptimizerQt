#include "Test.h"
#include "Command.h"

#include <typeinfo>

namespace impl
{
/**
 * Pokusi sa pretypovat prikaz na MovementCommand.
 * Ak prikaz nie je pohybovy, vrati nullptr.
 */
const MovementCommand* castToMovementCommand(const Command& command)
{
    return dynamic_cast<const MovementCommand*>(&command);
}

/**
 * Skontroluje, ci prikaz je typu M3 (zapnutie horaka).
 */
bool isM3(const Command& command)
{
    return typeid(command) == typeid(M3);
}

/**
 * Skontroluje, ci prikaz je typu M5 (vypnutie horaka).
 */
bool isM5(const Command& command)
{
    return typeid(command) == typeid(M5);
}
}

// ************************************************************
/**
 * Skontroluje, ci su dva prikazy zhodne.
 * - Ak su pohybove prikazy, porovnaju sa ich suradnice.
 * - Ak su nepohybove prikazy, porovnava sa ich typ (M3, M5).
 * - Ak su zhodne, je to duplicita (funkcia vrati false).
 */
bool testDuplicity(const Command& current, const Command& previous)
{
    auto currMove = impl::castToMovementCommand(current);
    auto prevMove = impl::castToMovementCommand(previous);

    if (currMove && prevMove)
    {
        // Porovnavame suradnice pohybovych prikazov
        return !(*currMove == *prevMove); // true = not duplicate, false = duplicate
    }
    else
    {
        // Porovnavame typ prikazu (napr. M3 == M3 alebo M5 == M5)
        return typeid(current) != typeid(previous); // Different commands
    }
}

// ************************************************************
/**
 * Skontroluje, ci sa nevraciame na bod, kde sme boli predtym.
 *
 * - Ak sa aktualny bod zhoduje s bodom pred dvoma krokmi dozadu, vratime false.
 * - Inak vratime true.
 */
bool testReturnToPoint(const Command& current, const Command& previous, const Command& previousOfPrevious)
{
    auto currMove = impl::castToMovementCommand(current);
    auto prevPrevMove = impl::castToMovementCommand(previousOfPrevious);

    if (currMove && prevPrevMove)
    {
        return !(*currMove == *prevPrevMove);
    }

    return true;
}

// ************************************************************
/**
 * Definicia operatora OR pre kombinovanie optimalizacnych modov.
 */
EOptimizeMode operator | (const EOptimizeMode op1, const EOptimizeMode op2)
{
    return static_cast<EOptimizeMode>(static_cast<int>(op1) | static_cast<int>(op2));
}

/**
 * Definicia operatora AND pre zistenie, ci je mod zapnuty.
 */
bool operator & (const EOptimizeMode op1, const EOptimizeMode op2)
{
    return (static_cast<int>(op1) & static_cast<int>(op2)) != 0;
}

// ************************************************************
/**
 * Funkcia optimalizuje zoznam prikazov podla nastaveneho rezimu.
 *
 * Realizuje tieto optimalizacie:
 * - Odstrani rovnake za sebou iduce prikazy (napr. dva G1 na rovnake suradnice).
 * - Odstrani navraty na predchadzajuci bod (vracanie sa spat).
 * - Odstrani pary M3 a M5 (alebo M5 a M3) iduce po sebe, ked sa stav horaka nezmeni.
 */
std::vector<std::shared_ptr<Command>> optimize(std::vector<std::shared_ptr<Command>> input, const EOptimizeMode mode)
{
    std::vector<std::shared_ptr<Command>> output;

    if (input.empty()) return output;

    for (size_t i = 0; i < input.size(); ++i)
    {
        // Specialne pravidlo: ak mame M3 nasledovane M5, alebo M5 nasledovane M3
        if (i >= 1)
        {
            bool isPrevM3 = impl::isM3(*input[i - 1]);
            bool isPrevM5 = impl::isM5(*input[i - 1]);
            bool isCurrM3 = impl::isM3(*input[i]);
            bool isCurrM5 = impl::isM5(*input[i]);

            if ((isPrevM3 && isCurrM5) || (isPrevM5 && isCurrM3))
            {
                // Ak narazime na takuto dvojicu, odstranime predchadzajuci prikaz a preskocime aktualny
                if (!output.empty())
                {
                    output.pop_back();
                }
                continue; // Preskocime aj aktualny prikaz
            }
        }

        // Odstranenie rovnakych pohybov na rovnake miesto (duplicity)
        if (i >= 1 && (mode & EOptimizeMode::the_same_movement))
        {
            if (!testDuplicity(*input[i], *input[i - 1]))
            {
                continue; // Duplicita, preskocit
            }
        }

        // Odstranenie navratov na predoslu poziciu
        if (i >= 2 && (mode & EOptimizeMode::returning_back))
        {
            if (!testReturnToPoint(*input[i], *input[i - 1], *input[i - 2]))
            {
                continue; // Navrat, preskocit
            }
        }

        // Ak prikaz presiel vsetkymi testami, pridame ho do vystupneho zoznamu
        output.push_back(input[i]);
    }

    return output;
}
