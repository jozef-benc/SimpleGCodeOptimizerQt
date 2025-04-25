#include "Parse.h"
#include <regex>
#include <algorithm>
#include <cctype>

/**
 * Pomocna funkcia na odstranenie bielych znakov na zaciatku a na konci retazca.
 * Zdroj inspiracie: https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 */
std::string trim(const std::string& str)
{
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) ++start;

    auto end = str.end();
    do { --end; } while (end != start && std::isspace(*end));

    return std::string(start, end + 1);
}

/**
 * Funkcia sa pokusi naparsovat jeden riadok do objektu Command.
 * Ak riadok nezodpoveda ziadnemu platnemu formatu, vrati nullptr.
 */
std::shared_ptr<Command> parseCommand(const std::string& rawLine)
{
    // Najskor odstranime nepotrebne medzery z riadku
    std::string line = trim(rawLine);
    // Definujeme regularne vyrazy na hladanie G0/G1 a M3/M5 prikazov
    // - regexove prikazy vytvorene pomocou ChatGPT
    static const std::regex moveCommandRegExp(R"(G([01])\s+X(-?\d+(\.\d+)?)\s+Y(-?\d+(\.\d+)?))");
    static const std::regex mCommandRegExp(R"(M[35])");

    std::smatch match;

    // Skusime najprv naparsovat pohybove prikazy G0 alebo G1
    if (std::regex_match(line, match, moveCommandRegExp))
    {
        int type = std::stoi(match[1].str());
        double x = std::stod(match[2].str());
        double y = std::stod(match[4].str());

        // Podla typu vytvorime spravny pohybovy prikaz
        if (type == 0) return std::make_shared<G0>(x, y);
        if (type == 1) return std::make_shared<G1>(x, y);
    }
    // Ak nesedi na pohybove prikazy, skusime technologicke M3 alebo M5
    else if (std::regex_match(line, match, mCommandRegExp))
    {
        if (line == "M3") return std::make_shared<M3>();
        if (line == "M5") return std::make_shared<M5>();
    }

    // Ak sa riadok neda naparsovat, vratime nullptr
    return nullptr;
}

/**
 * Funkcia naparsuje vsetky vstupne riadky do vektora prikazov Command.
 */
std::vector<std::shared_ptr<Command>> parseCommands(const std::vector<std::string>& lines)
{
    std::vector<std::shared_ptr<Command>> commands;

    // Prechadzame kazdy riadok zvlast
    for (const std::string& line : lines)
    {
        auto cmd = parseCommand(line);
        if (cmd) {
            // Ak sa riadok podarilo naparsovat, pridame prikaz do zoznamu
            commands.push_back(cmd);
        }
        // Ak sa nepodarilo naparsovat, riadok ignorujeme
    }
    // Vratime vektor platnych prikazov
    return commands;
}
