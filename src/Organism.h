#ifndef ORGANISM_H
#define ORGANISM_H

#include "Helper.h"

#include <vector>
#include <tuple>
#include <random>
#include <unordered_map>
#include <sstream>

class Organism{
    public:
    enum OrganismType{
        PlantEnum = 0,
        HerbivoreEnum = 1,
        OmnivoreEnum = 2,
        COUNT
    };
    
    private:
    OrganismType m_type{};
    static int m_id_counter; // Used to come up with a unique ID for every organism created
    int m_id{}; // Unique ID
    char m_letter_id{}; // Letter ID. Multiple organisms can have the same letter ID
    int m_color; // Unique ANSI Escape color code for organism
    static std::unordered_map<OrganismType, std::vector<int>> m_colorMap; // Used for setting colors for each organism type
    static const std::unordered_map<OrganismType, std::vector<OrganismType>> m_PREDATORS_MAP; // Map that's like: {organism type (plant/herbivore/omnivore etc) : list of other organism types that are a predator to key organism}
    static const std::unordered_map<OrganismType, std::vector<OrganismType>> m_PREY_MAP; // Map that's like: {organism type (plant/herbivore/omnivore etc) : list of other organism types that are prey to key organism}
    
    // Private methods:
    void setHealth(int health); // Set both max health & current health to health. This is currently only used in the constructor
    void setColor(); // Set m_color to some random value from m_colorMap

    protected:
    bool m_alive{true};
    int m_max_health{};
    int m_current_health{};
    std::tuple<int, int> m_coords;

    public:
    Organism(char letter_id, OrganismType type, int health, const std::tuple<int, int>& coords);

    // Setters & Getters:

    int getID() const;

    char getLetterID() const;

    OrganismType getType() const;

    std::tuple<int, int> getCoords() const;

    int getMaxHealth() const;

    int getCurrentHealth() const;

    std::vector<Organism::OrganismType> getPredators() const;

    std::vector<Organism::OrganismType> getPrey() const;

    int getColor() const;

    bool isAlive() const;

    // Methods:

    /*
    - Set current health to 0
    - Set alive to false
    */
    void die();

    /*
    - See if this is a predator to org
    */
    bool isPredatorTo(const Organism* const org) const;

    /*
    - See if this is a prey to org
    */
    bool isPreyTo(const Organism* const org) const;

    /*
    - current health += heal amount
    - heal amount can be negative to reduce health of organism
    */
    void addHealth(int heal_amount);

    /*
    - Get a string containing the organism's letter ID in its corresponding oclor
    */
    std::string getLetterIDColored() const;

    /*
    - See if this and parameter org have any coordiantes in common.
    - Ex: if this is located at (3, 5) and parameter org is located at (2, 5), the common coordinate is the y-coordinate
    - returning 0 = x-coordinate is common, returning 1 = y-coordinate is common
    */
    int getCommonCoordinate(const Organism* const org) const;

    /*
    - See if this and parameter org are within 1 unit of distance away from each other
    - Only accounts for directly above/below/left/right. No diagonal detection
    */
    bool isNextTo(const Organism* const org) const;

    /*
    - Given a vector of all organisms in the simulation as well as the map dimensions, update this organism.
    - Since plants and animals have different behaviors and need to be updated differently, this is a virtual method that will be overridden.
    */
    virtual void update(const std::vector<Organism*>& organisms, const std::tuple<int, int>& map_dimensions) = 0;
};

#endif