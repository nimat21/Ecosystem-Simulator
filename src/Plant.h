#ifndef PLANT_H
#define PLANT_H

#include "Organism.h"

class Plant : public Organism{
    const int m_energy_points{};

    public:
    Plant(char letter_id, int energy_points, int regrowth_coefficient, const std::tuple<int, int>& coords);

    // Setters & Getters:

    /*
    - For plants, regrowth coefficient is synonymous with max health.
    - Current health is like growth status. When current health >= max health, plant can regrow
    */
    int getRegrowthCoefficient() const;

    /*
    - This will stay constant for the plant throughout its life cycle.
    */
    int getEnergyPoints() const;

    // Methods:

    /*
    - current health = max health
    - alive = true
    */
    void revive();

    /*
    Given a vector of organisms, update this plant object as follows:
    - If a plant is dead, add 1 to its health
    - If its health >= max_health, revive it
    */
    void update(const std::vector<Organism*>& organisms, const std::tuple<int, int>& map_dimensions) override;
};

#endif