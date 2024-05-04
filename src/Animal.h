#ifndef ANIMAL_H
#define ANIMAL_H

#include "Organism.h"
#include "Plant.h"

class Animal : public Organism{
    public:
    Animal(char letter_id, Organism::OrganismType animal_type, int health, const std::tuple<int, int>& coords);

    // Methods:

    /*
    Move to new coordinates
    New coordinates must be within 1 unit of current coordinates, otherwise error will occur and organism will not move
    */
    void moveTo(const std::tuple<int, int>& new_location);
    
    /*
    Eat another organism
    - this.addHealth(org.getCurrentHealth())
    - org.die()
    - this.m_coords = org.getCoords()
    */
    void eat(Organism* org);

    /*
    See if this is hungry enough to eat org
    */
    bool hungryEnoughToEat(Organism* const org);

    /*
    Given a vector of organisms and a specific animal type, update this animal object as follows:
    - If animal sees an edible organism adjacent to it and if animal is hungry enough to eat the organism, animal will eat the organism
    - Otherwise, animal will move randomly in some direction
        This will automatically allow animal to flee from any adjacent predators
    */
    void update(const std::vector<Organism*>& organisms, const std::tuple<int, int>& map_dimensions) override;
};

#endif