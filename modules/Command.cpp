#include "Command.h"
#include <cstdio>
#include <cmath>

/**
 * Konstruktor pre MovementCommand bez inicializacie.
 */
MovementCommand::MovementCommand() = default;

/**
 * Kopirovaci konstruktor pre MovementCommand.
 */
MovementCommand::MovementCommand(const MovementCommand&) = default;

/**
 * Operator priradenia pre MovementCommand.
 */
MovementCommand& MovementCommand::operator=(const MovementCommand&) = default;

/**
 * Konstruktor MovementCommand s nastavenim suradnic X a Y.
 */
MovementCommand::MovementCommand(double x, double y) : m_x(x), m_y(y) {}

/**
 * Operator porovnania dvoch pohybovych prikazov podla suradnic.
 * Porovnava sa s malou toleranciou (epsilon) aby sa osetrili chyby zaokruhlovania.
 */
bool MovementCommand::operator==(const MovementCommand& other) const
{
    constexpr double epsilon = 1e-6;
    return (std::abs(m_x - other.m_x) < epsilon) && (std::abs(m_y - other.m_y) < epsilon);
}

/**
 * Pomocna funkcia na konverziu cisla na retazec s tromi desatinnymi miestami (verzia pre l-Value).
 */
std::string MovementCommand::double2String(const double d) const&
{
    char buf[16];
    std::snprintf(buf, sizeof(buf), "%.3f", d);
    return buf;
}

/**
 * Pomocna funkcia na konverziu cisla na retazec s tromi desatinnymi miestami (verzia pre r-Value).
 */
std::string MovementCommand::double2String(const double d) const&&
{
    char buf[16];
    std::snprintf(buf, sizeof(buf), "%.3f", d);
    return buf;
}

/**
 * Vrati textovu reprezentaciu pohyboveho prikazu ako "X<suradnica> Y<suradnica>".
 */
std::string MovementCommand::toString() const
{
    return "X" + double2String(m_x) + " Y" + double2String(m_y);
}

/**
 * Vrati textovu reprezentaciu prikazu G0 s prislusnymi suradnicami.
 */
std::string G0::toString() const
{
    return "G0 X" + double2String(m_x) + " Y" + double2String(m_y);
}

/**
 * Vrati textovu reprezentaciu prikazu G1 s prislusnymi suradnicami.
 */
std::string G1::toString() const
{
    return "G1 X" + double2String(m_x) + " Y" + double2String(m_y);
}

/**
 * Vrati textovu reprezentaciu prikazu M3 (zapnutie horaka).
 */
std::string M3::toString() const
{
    return "M3";
}

/**
 * Vrati textovu reprezentaciu prikazu M5 (vypnutie horaka).
 */
std::string M5::toString() const
{
    return "M5";
}
