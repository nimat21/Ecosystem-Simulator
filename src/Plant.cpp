#include "Plant.h"

Plant::Plant(char letter_id, int energy_points, int regrowth_coefficient, const std::tuple<int, int>& coords)
    : Organism::Organism(letter_id, Organism::PlantEnum, regrowth_coefficient, coords), m_energy_points{energy_points} 
    {}

// Setters & Getters:

int Plant::getRegrowthCoefficient() const{
    return Organism::getMaxHealth();
}

int Plant::getEnergyPoints() const{
    return m_energy_points;
}

// Methods:

void Plant::revive(){
    m_current_health = m_max_health;
    m_alive = true;
}

void Plant::update(const std::vector<Organism*>& organisms, const std::tuple<int, int>& map_dimensions){
    // If plant is dead, add 1 to its health
    if (!this->isAlive()){
        if (this->getCurrentHealth() < this->getMaxHealth()){
            this->addHealth(1);
        }

        // If plant is currently not alive and its coordinates are not occupied by another organism, revive it
        if (this->getCurrentHealth() >= this->getMaxHealth()){
            // Check if another organism is standing on the plant
            bool occupied = false;
            for(Organism* org : organisms){
                if (org->getID() == this->getID())
                    continue;

                if (org->getCoords() == m_coords){
                    occupied = true;
                    break;
                }
            }

            if (!occupied)
                this->revive();
        }
    }
}