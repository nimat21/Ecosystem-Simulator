#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include <limits>
#include <fstream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <random>

#include "Plant.h"
#include "Animal.h"
#include "Ecosystem.h"
#include "Helper.h"

using namespace std::string_literals;

class Ecosystem {
public:

    /*
    - Given the path to a map, this will return a tuple containing the map dimensions
    - Tuple format: (map_width, map_height)
    */
    static std::tuple<int, int> getMapDimensions(const std::filesystem::path& file_path);

    /*
    - Give the path to the map and the vector you want the results to be saved to
    - This will update the vector so that it's like ('a', <x_coordinates, y_coordinates>) where 'a' is the letter ID of the organism, and the tuple is the organism's coordinates
    */
    static void getOrgCoords(const std::filesystem::path& file_path, std::vector<std::tuple<char, std::tuple<int, int>>>& organism_coords_vect, int offset = 0);

    /*
    - Give the path to the species list and the unordered map you want the info to be stored in
    - The info will be stored in the unordered map like (char (species letter id), <organism type, health, energy points (only if it's a plant)>)
    */
    static void getSpeciesInfo(const std::filesystem::path& file_path, std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>>& species_info);

    /*
    - Given a vector of organisms and map dimensions, print the current ecosystem
    */
    static void printEcosystem(const std::vector<Organism*>& organisms, const std::tuple<int, int>& map_dimensions);
};

#endif