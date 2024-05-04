#include "Ecosystem.h"

int main(int argc, char* argv[]){
    Helper::clearScreen();

    // Extract map file and species file paths from command line arguments
    std::filesystem::path map_file;
    std::filesystem::path species_file;

    if (argc >= 3) { // Ensure there are enough command line arguments
        map_file = argv[1];
        species_file = argv[2];
    }
    else {
        std::cerr << "Error: Insufficient command line arguments. Please provide paths for map file and species file.\n";
        Helper::quit(8);
    }

    // G E T   M A P   I N F O
    // Get map dimensions
    std::tuple<int, int> map_dimensions = Ecosystem::getMapDimensions(map_file);

    // Get coordinate info for all organisms in the map
    std::vector<std::tuple<char, std::tuple<int, int>>> organism_coords_vect;
    Ecosystem::getOrgCoords(map_file, organism_coords_vect);

    // G E T   S P E C I E S   I N F O
    std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> species_info;
    Ecosystem::getSpeciesInfo(species_file, species_info);

    // M A K E   O R G A N I S M   O B J E C T S
    std::vector<Organism*> organisms;
    for (const auto& org : organism_coords_vect) {
        char org_char_ID = std::get<0>(org);
        auto coords = std::get<1>(org);
        int x_coord = std::get<0>(coords);
        int y_coord = std::get<1>(coords);

        // Get organism info from species info map
        if (species_info.find(std::string(1, org_char_ID)) != species_info.end()) {
            std::tuple<std::string, std::string, std::string> info = species_info[std::string(1, org_char_ID)];
            std::string species = std::get<0>(info);
            int health;
            try {
                health = std::stoi(std::get<1>(info));
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: Please give an integer value for " << species << " health\n";
                Helper::quit(7);
            }

            // Create actual plant/animal objects
            Organism* org_ptr = nullptr;
            std::string lowercase_species;
            std::transform(species.begin(), species.end(), std::back_inserter(lowercase_species), [](unsigned char c) { return std::tolower(c); });
            try {
                if (lowercase_species == "plant") {
                    int energy_points = std::stoi(std::get<2>(info));
                    org_ptr = new Plant(org_char_ID, energy_points, health, coords);
                } 
                else if (lowercase_species == "herbivore") {
                    org_ptr = new Animal(org_char_ID, Organism::HerbivoreEnum, health, coords);
                } 
                else if (lowercase_species == "omnivore") {
                    org_ptr = new Animal(org_char_ID, Organism::OmnivoreEnum, health, coords);
                } 
                else {
                    std::cerr << "Error: Check if you misspelled a species name\n";
                    Helper::quit(6);
                }
            } 
            catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid arguments given for " << lowercase_species << std::endl;
                Helper::quit(6);
            }

            if (org_ptr) {
                organisms.push_back(org_ptr);
            }
        } else {
            std::cerr << "Error: species info not found for organism " << org_char_ID << ". Please include this species in your species list"<< "\n";
            Helper::quit(5);
        }
    }

    // M A I N   S I M U L A T I O N   C O D E

    // simulation constants (used for printing, getting user input, etc)
    const std::string OPTIONS_MENU =
    "Options menu:\n"
    "1. Run 1 iteration\n"
    "2. Run a batch of iterations\n"
    "3. Exit the program\n"
    "Please enter your choice from the menu above: ";

    const int MIN_OPTION_CHOICE = 1;
    const int MAX_OPTION_CHOICE = 3;
    const std::string BATCH_PROMPT = "Enter desired batch size: ";
    const int DEFAULT_SLEEP_TIME = 100;
    const std::string SLEEP_TIME_PROMPT = "Enter desired pause time between iterations (in milliseconds): ";

    // simulation variables
    int total_iterations = 0;
    int todo_iterations;
    int sleep_time;
    int user_choice;

    // Actual simulation code
    do{
        // Display completed iterations
        Helper::clearScreen();
        std::cout << "Iterations completed: " << total_iterations << '\n';
        Ecosystem::printEcosystem(organisms, map_dimensions);

        // Get user choice from menu
        std::cout << OPTIONS_MENU;
        user_choice = Helper::getUserChoice(MIN_OPTION_CHOICE, MAX_OPTION_CHOICE);
        switch(user_choice){
            case 1:
                todo_iterations = 1;
                sleep_time = DEFAULT_SLEEP_TIME;
                break;

            case 2:
                todo_iterations = Helper::getPositiveInteger(BATCH_PROMPT);
                sleep_time = Helper::getPositiveInteger(SLEEP_TIME_PROMPT);
                break;
            
            case 3:
                continue;
            
            default:
                std::cout << "This isn't supposed to happen >:(\n";
        }

        // Update ecosystem
        for (int i = 0; i < todo_iterations; i++){
            // Update iteration counter
            total_iterations++;

            // Update organisms
            for (Organism* org : organisms){
                if (org->getType() == Organism::PlantEnum){
                    Plant* plant {dynamic_cast<Plant*>(org)};
                    plant->update(organisms, map_dimensions);
                }
                else{
                    Animal* animal {dynamic_cast<Animal*>(org)};
                    animal->update(organisms, map_dimensions);
                }
            }

            // Clean up any eaten animals
            auto it = organisms.begin();
            while (it != organisms.end()) {
                Organism* org = *it;
                if (!org->isAlive() && (org->getType() != Organism::PlantEnum)) {
                    delete org; // Free memory allocated for the organism
                    it = organisms.erase(it); // Remove the organism from the vector and advance the iterator
                } else {
                    it++; // Move to the next organism
                }
            }

            // Display updated ecosystem
            Helper::clearScreen();
            std::cout << "Iteration " << total_iterations << ":\n";
            Ecosystem::printEcosystem(organisms, map_dimensions);
            Helper::sleep(sleep_time);
        }

    } while (user_choice != MAX_OPTION_CHOICE);

    // Clean up allocated memory
    for (Organism* org : organisms) {
        delete org;
    }

    // Quit program successfully
    Helper::quit(0);

    return 0;
}