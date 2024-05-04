#include "Ecosystem.h"

std::tuple<int, int> Ecosystem::getMapDimensions(const std::filesystem::path& file_path) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open " << file_path << " for reading\n";
        Helper::quit(1);
    }

    // Find map dimensions
    int width = 0;
    int height = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (line.size() > width) { // Find max width
            width = line.size();
        }
        height++;
    }

    return {width, height};
}

void Ecosystem::getOrgCoords(const std::filesystem::path& file_path, std::vector<std::tuple<char, std::tuple<int, int>>>& organism_coords_vect, int offset) {
    std::ifstream file_(file_path);

    if (!file_.is_open()){
        std::cerr << "Error: Couldn't open " << file_path << " for reading\n";
        Helper::quit(1);
    }

    // Note: I'm doing an offset of x (each coordinate is x greater than actual value) because of the way I'm printing to terminal, and also to leave room for borders when printing
    // Note 2: This was a really stupid idea so I just default to offset = 0 now, but I'm still allowing the parameter just in case I want to change the code in the future
    int y_coord = offset;
    while (file_){
        std::string strInput;
        std::getline(file_, strInput);
        // Analyze line and extract any char info if char is found
        for(int i = 0; i < strInput.size(); i++){
            char c = strInput[i];
            // If this char is not a space, it is some organism. Save it.
            if (c != ' '){
                std::tuple<int, int> coords = std::make_tuple(i+offset, y_coord);
                std::tuple<char, std::tuple<int, int>> organism_info = std::make_tuple(c, coords);
                organism_coords_vect.push_back(organism_info);
            }
        }

        y_coord++;
    }
    file_.close();
}

void Ecosystem::getSpeciesInfo(const std::filesystem::path& file_path, std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>>& species_info) {
    std::ifstream file_(file_path);

    if (!file_.is_open()) {
        std::cerr << "Error: Couldn't open " << file_path << " for reading\n";
        Helper::quit(3);
    }

    std::string line;
    while (std::getline(file_, line)) {
        try {
            std::istringstream iss(line);
            std::string organismType, organismCharID;

            if (iss >> organismType >> organismCharID) {
                std::string health, energy_points;
                if (organismType == "plant" && iss >> health >> energy_points) { // Extract plant info (health + energy points)
                    species_info[organismCharID] = std::make_tuple(organismType, health, energy_points);
                }
                else if (iss >> health) { // Extract animal info (just health)
                    species_info[organismCharID] = std::make_tuple(organismType, health, "");
                }
            }
        } catch (...) {
            std::cerr << "Error: Invalid formatting in " << file_path << '\n';
            Helper::quit(6);
        }
    }
    file_.close();
}

void Ecosystem::printEcosystem(const std::vector<Organism*>& organisms, const std::tuple<int, int>& map_dimensions) {
    int map_offset = 1; // This is needed for printing alignment purposes
    std::stringstream ss; // This is where we'll be making the ecosystem map

    // Initialize empty map
    int max_height = std::get<1>(map_dimensions) + 2, max_width = std::get<0>(map_dimensions) + 2;
    for (int i = 0; i < max_height; i++){
        for (int j = 0; j < max_width; j++){
            // Print horizontal borders
            if (i == 0 || i == (max_height - 1))
                ss << '-';
            
            // Print vertical borders
            else if (j == 0 || j == (max_width - 1))
                ss << '|';
            
            else
                ss << ' ';
        }
        ss << '\n';
    }
    std::string ecosystem_str = ss.str();

    // Take note of where each organism needs to be plotted
    // The pair is {index in ss string where org should be inserted (i had to do some math to figure this out), org colored ID (this is a string bc I need a bunch of weird characters to produce the color along w/ the actual ID char)}
    std::vector<std::pair<int, std::string>> plotting_info;
    for (Organism* org : organisms){
        if (!org->isAlive())
            continue;
        
        // Get organism info
        std::tuple<int, int> coords = org->getCoords();
        int x_coord = std::get<0>(coords) + map_offset, y_coord = std::get<1>(coords) + map_offset;

        // Calculate where organism needs to be plotted & take note
        int map_coord = ((max_width + 1) * y_coord) + x_coord;
        std::string colored_ID = org->getLetterIDColored();
        plotting_info.push_back({map_coord, colored_ID});
    }

    // Plot organisms
    /*
    Note: I'm plotting organisms from bottom to top.
    This is because when i "plot" an organism, I'm literally inserting this organism's colored ID (which is a long string that displays as colored output) into ss.
    This causes ss to be sort of "extended". For example, imagine this is ss: "abcdefg" and I want to add "hello" and "world" at indexes 2 and 5 respectively.
    If I add "hello" first at index 2, ss becomes "abhellocdefg". Notice that now, index 5 is right after 'l' rather than 'e' because adding the "hello" ended up extending ss and messing with its old indexing.
    But this problem can be fixed if I just add the bottom-most words first, i.e. first add "world" at index 5 and then "hello" at index 2. ss will then look like:
    - "abcdehellofg" after adding 1st word
    - "abhellocdehellofg" after adding 2nd word
    This is the same logic I'm applying to plot the organisms and not mess up their spacing on the map.
    */
    while (!plotting_info.empty()) {
        // Find highest organism
        int highest_map_coords = -1;
        for (const auto& info : plotting_info) {
            if (info.first > highest_map_coords)
                highest_map_coords = info.first;
        }

        // Plot this organism
        for (auto it = plotting_info.begin(); it != plotting_info.end(); ++it) {
            if (it->first != highest_map_coords)
                continue;

            ecosystem_str.replace(highest_map_coords, 1, it->second);
            it = plotting_info.erase(it); // Erase the organism from the plotting list
            break; // Exit the loop after plotting one organism
        }
    }

    std::cout << ecosystem_str;
    return;
}