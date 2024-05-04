#include "Animal.h"

Animal::Animal(char letter_id, Organism::OrganismType animal_type, int health, const std::tuple<int, int>& coords)
        : Organism::Organism(letter_id, animal_type, health, coords) {}

// Methods:

void Animal::moveTo(const std::tuple<int, int>& new_location){
    // Make sure only adjacent moves are happenening (no diagonal moves)
    int x_disp = std::get<0>(m_coords) - std::get<0>(new_location);
    int y_disp = std::get<1>(m_coords) - std::get<1>(new_location);

    if (x_disp > 1 || x_disp < -1){
        std::cerr << "Error: trying to move animal too far!\n";
        Helper::quit(9);
    }
    if (y_disp > 1 || y_disp < -1){
        std::cerr << "Error: trying to move animal too far!\n";
        Helper::quit(9);
    }
    if (x_disp != 0 && y_disp != 0){
        std::cerr << "Error: animal can only move by 1 adjacent square!\n";
        Helper::quit(9);
    }

    // Update location
    std::get<0>(m_coords) = std::get<0>(new_location);
    std::get<1>(m_coords) = std::get<1>(new_location);
}

void Animal::eat(Organism* org){
    // Restore health
    if (org->getType() == Organism::PlantEnum){
        Plant* plant {dynamic_cast<Plant*>(org)};
        this->addHealth(plant->getEnergyPoints());
    }
    else{
        this->addHealth(org->getCurrentHealth());
    }

    // Move to eaten organism's location
    std::tuple<int, int> org_coords = org->getCoords();
    std::get<0>(m_coords) = std::get<0>(org_coords);
    std::get<1>(m_coords) = std::get<1>(org_coords);

    // Kill the eaten organism
    org->die();
}

bool Animal::hungryEnoughToEat(Organism* const org){
    // See how hungry this is
    int hunger = this->getMaxHealth() - this->getCurrentHealth();

    // See how much food is the org
    int consume_size;
    if (org->getType() == Organism::PlantEnum){
        Plant* plant {dynamic_cast<Plant*>(org)};
        consume_size = plant->getEnergyPoints();
    }
    else
        consume_size = org->getCurrentHealth();
    
    // See if this is hungry enough to eat the org
    if (hunger >= consume_size)
        return true;

    return false;
}

void Animal::update(const std::vector<Organism*>& organisms, const std::tuple<int, int>& map_dimensions){
    // Find all adjacent organisms
    bool eaten = false;
    std::vector<Organism*> adjacent_organisms;
    for(Organism* org : organisms){
        // Skip over plants that are de-spawned
        if (!org->isAlive())
            continue;

        // Skip over myself
        if (org->getID() == this->getID())
            continue;

        // See if this is an adjacent organism
        if (this->isNextTo(org)){
            // See if it's edible
            if(this->isPredatorTo(org)){
                //See if animal is hungry enough to eat org
                if (this->hungryEnoughToEat(org)){
                    this->addHealth(-1); // Animal needs to expend 1 energy point to reach organism to eat
                    this->eat(org);
                    eaten = true;
                    break;
                }
            }

            // If org is not edible/eaten, note it as just another adjecent org and continue
            adjacent_organisms.push_back(org);
        }
    }

    // If animal ate something during above search, it has already completed its update
    if (eaten)
        return;

    // Code below will make a random move to some free adjacent location
    // Doing so will automatically flee from any nearby predators
    int current_x_coord = std::get<0>(m_coords);
    int current_y_coord = std::get<1>(m_coords);
    
    // Get all possible adjacent locations
    std::tuple<int, int> adjacent_locations[4];
    int array_index = 0;
    for(int i = 0; i < 2; i++){
        for(int j = -1; j <=1; j+=2){
            // Logic to calculate adjacent locations
            std::tuple<int, int> adjacent_location;
            if (i % 2 == 0){
                int new_x_coord = current_x_coord + j;
                if (new_x_coord < 0 || new_x_coord >= std::get<0>(map_dimensions)) // Boundary detection (location of {-1, -1} indicates a location that is impossible to move to)
                    adjacent_location = {-1, -1};
                else
                    adjacent_location = {current_x_coord + j, current_y_coord};
            }
            else{
                int new_y_coord = current_y_coord + j;
                if (new_y_coord < 0 || new_y_coord >= std::get<1>(map_dimensions)) // Boundary detection (location of {-1, -1} indicates a location that is impossible to move to)
                    adjacent_location = {-1, -1};
                else
                    adjacent_location = {current_x_coord, current_y_coord + j};
            }

            adjacent_locations[array_index] = adjacent_location;
            array_index++;

        }
    }

    // Shuffle adjacent locations to make movements random
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(std::begin(adjacent_locations), std::end(adjacent_locations), rng);

    // Move to first unoccupied location
    bool moved = false;
    for(std::tuple<int, int> location : adjacent_locations){
        if (location == std::tuple<int, int>{-1, -1}) // Make sure new location isn't out of bounds
            continue;

        bool occupied = false;
        for (Organism* adjacent_org : adjacent_organisms){
            if (adjacent_org->getCoords() == location){
                occupied = true;
                break;
            }
        }

        if (!occupied){ // Move to unoccupied location
            this->addHealth(-1);
            this->moveTo(location);
            moved = true;
            break;
        }
    }

    // If animal is unable to move, simply decrease its health by 1 and move on
    if (!moved)
        this->addHealth(-1);
}