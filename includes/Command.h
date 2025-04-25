#pragma once

/**
 * @file Command.h
 * @brief Obsahuje definicie zakladnych prikazov pre CNC kod.
 *
 * Tento subor definuje zakladnu triedu Command a jej potomkov
 * ako pohybove a technologicke prikazy (G0, G1, M3, M5).
 */

#include <string>

/**
 * @brief Zakladna trieda reprezentujuca prikaz.
 */
class Command
{
public:
    virtual ~Command() = default;

    /**
     * @brief Vrati textovu reprezentaciu prikazu.
     * @return Textova reprezentacia prikazu.
     */
    virtual std::string toString() const = 0;

    /**
     * @brief Konverzia prikazu na std::string.
     * @return Textova reprezentacia prikazu.
     */
    explicit operator std::string() const;
};

/**
 * @brief Zakladna trieda pre pohybove prikazy (G0, G1).
 */
class MovementCommand : public Command
{
public:
    MovementCommand();
    MovementCommand(const MovementCommand&);
    MovementCommand(MovementCommand&&) noexcept = delete;
    MovementCommand& operator=(const MovementCommand&);
    MovementCommand& operator=(MovementCommand&&) noexcept = delete;
    explicit MovementCommand(double x, double y);

    /**
     * @brief Porovna dva pohybove prikazy podla suradnic.
     * @param other Druhy prikaz na porovnanie.
     * @return true ak su suradnice zhodne, inak false.
     */
    bool operator==(const MovementCommand& other) const;

    /**
     * @brief Konvertuje cislo na retazec s tromi desatinnymi miestami.
     * @param d Cislo na konverziu.
     * @return Retazec vo formate %.3f.
     */
    std::string double2String(const double d) const&;
    std::string double2String(const double d) const&&;

    /**
     * @brief Vrati textovu reprezentaciu pohyboveho prikazu.
     * @return Textova reprezentacia (X, Y suradnice).
     */
    virtual std::string toString() const override;

public:
    double m_x;
    double m_y;
};

/**
 * @brief Pohybovy prikaz G0 (rychly presun).
 */
class G0 : public MovementCommand
{
public:
    using MovementCommand::MovementCommand;

    /**
     * @brief Vrati textovu reprezentaciu G0 prikazu.
     * @return Textova reprezentacia prikazu.
     */
    virtual std::string toString() const override;
};

/**
 * @brief Pohybovy prikaz G1 (rezanie).
 */
class G1 : public MovementCommand
{
public:
    using MovementCommand::MovementCommand;

    /**
     * @brief Vrati textovu reprezentaciu G1 prikazu.
     * @return Textova reprezentacia prikazu.
     */
    virtual std::string toString() const override;
};

/**
 * @brief Prikaz M3 (zapnutie horaka).
 */
class M3 : public Command
{
public:
    /**
     * @brief Vrati textovu reprezentaciu M3 prikazu.
     * @return Textova reprezentacia prikazu.
     */
    virtual std::string toString() const override;
};

/**
 * @brief Prikaz M5 (vypnutie horaka).
 */
class M5 : public Command
{
public:
    /**
     * @brief Vrati textovu reprezentaciu M5 prikazu.
     * @return Textova reprezentacia prikazu.
     */
    virtual std::string toString() const override;
};
