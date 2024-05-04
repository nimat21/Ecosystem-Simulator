#include "Organism.h"

int Organism::m_id_counter {0}; // This will be used for making unique IDs for each organism

std::unordered_map<Organism::OrganismType, std::vector<int>> Organism::m_colorMap = {
    {Organism::PlantEnum, {2, 10, 35, 40, 70, 83, 119}},        // Plants will be some shade of green
    {Organism::HerbivoreEnum, {4, 6, 14, 32, 39, 123}},    // Herbivores will be some shade of blue
    {Organism::OmnivoreEnum, {1, 9, 160, 167, 196, 197, 198}}   // Omnivores will be some shade of red
};

// This is a map that's like (organism : organism predators list)
const std::unordered_map<Organism::OrganismType, std::vector<Organism::OrganismType>> Organism::m_PREDATORS_MAP = {
    {PlantEnum, {HerbivoreEnum, OmnivoreEnum}},
    {HerbivoreEnum, {OmnivoreEnum}},
    {OmnivoreEnum, {}}
};

// This is a map that's like (organism : organism prey list)
const std::unordered_map<Organism::OrganismType, std::vector<Organism::OrganismType>> Organism::m_PREY_MAP = {
    {PlantEnum, {}},
    {HerbivoreEnum, {PlantEnum}},
    {OmnivoreEnum, {PlantEnum, HerbivoreEnum}}
};

Organism::Organism(char letter_id, OrganismType type, int health, const std::tuple<int, int>& coords)
    : m_id(m_id_counter++), m_letter_id(letter_id), m_type(type), m_coords(coords) {
    // Initialize organism health
    setHealth(health);

    // Set unique color for this organism
    setColor();
}

// Setters & Getters

int Organism::getID() const{
    return m_id;
}

char Organism::getLetterID() const{
    return m_letter_id;
}

Organism::OrganismType Organism::getType() const{
    return m_type;
}

std::tuple<int, int> Organism::getCoords() const{
    return m_coords;
}

int Organism::getMaxHealth() const{
    return m_max_health;
}

int Organism::getCurrentHealth() const{
    return m_current_health;
}

void Organism::setHealth(int health){
    m_max_health = health;
    m_current_health = health;
}

bool Organism::isAlive() const{
    return m_alive;
}

std::vector<Organism::OrganismType> Organism::getPredators() const {
    // Find the entry for this organism's type in the predators map
    auto it = m_PREDATORS_MAP.find(m_type);
    if (it != m_PREDATORS_MAP.end()) {
        return it->second; // Return the vector of predators for this organism's type
    }
    else {
        return {}; // If the organism's type is not found in the map, return an empty vector
    }
}

std::vector<Organism::OrganismType> Organism::getPrey() const {
    // Find the entry for this organism's type in the prey map
    auto it = m_PREY_MAP.find(m_type);
    if (it != m_PREY_MAP.end()) {
        return it->second; // Return the vector of prey for this organism's type
    }
    else {
        return {}; // If the organism's type is not found in the map, return an empty vector
    }
}

void Organism::setColor() {
    if (m_colorMap.find(m_type) != m_colorMap.end() && !m_colorMap[m_type].empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, m_colorMap[m_type].size() - 1);
        int index = dis(gen);
        m_color = m_colorMap[m_type][index];
    } else {
        std::cerr << "Color vector for OrganismType not initialized or empty.\n";
    }
}

int Organism::getColor() const{
    return m_color;
}

// Methods

void Organism::die(){
    m_current_health = 0;
    m_alive = false;
}

void Organism::addHealth(int heal_amount){
    m_current_health += heal_amount;
    if (m_current_health > m_max_health)
        m_current_health = m_max_health;
    
    if (m_current_health <= 0)
        this->die();
}

bool Organism::isPredatorTo(const Organism* const org) const{
    std::vector<Organism::OrganismType> org_predators = org->getPredators();

    // Check if org has no predators
    if (org_predators.empty())
        return false;
    
    // Check each and every predator of org and see if this is a predator
    for (Organism::OrganismType org_type : org_predators){
        if (m_type == org_type)
            return true;
    }
    return false;
}

bool Organism::isPreyTo(const Organism* const org) const{
    std::vector<Organism::OrganismType> org_prey = org->getPrey();

    // Check if org has no prey
    if (org_prey.empty())
        return false;
    
    // Check each and every prey of org and see if this is a prey
    for (Organism::OrganismType org_type : org_prey){
        if (m_type == org_type)
            return true;
    }
    return false;
}

std::string Organism::getLetterIDColored() const{
    std::stringstream ss;
    ss << "\033[38;5;" << m_color << "m";
    ss << getLetterID();
    ss << "\033[0m";
    return ss.str();
}

int Organism::getCommonCoordinate(const Organism* const org) const{
    std::tuple<int, int> org_coords = org->getCoords();
    if (std::get<0>(m_coords) == std::get<0>(org_coords)){
        return 0;
    } else if (std::get<1>(m_coords) == std::get<1>(org_coords)){
        return 1;
    } else{
        return -1;
    }
}

bool Organism::isNextTo(const Organism* const org) const{
    int common_coordinate = this->getCommonCoordinate(org);
    if (common_coordinate == -1){ // If these organisms don't have any coordinates in common, they cannot be next to each other
        return false;
    } 
    
    int uncommon_coordinate = 1 - common_coordinate;
    std::tuple<int, int> org_coords = org->getCoords();

    // See how far the organisms are in 1 dimension
    // Ex: if we're comparing (2, 5) to (4, 5), distance is 2 - 4 = -2 --> not nearby
    //  if we're comparing (3, 2) to (3, 1), distance = 2 - 1 = 1 --> nearby
    int distance;
    if (uncommon_coordinate == 0){
        distance = std::get<0>(m_coords) - std::get<0>(org_coords);
    }
    else if (uncommon_coordinate == 1){
        distance = std::get<1>(m_coords) - std::get<1>(org_coords);
    }

    if (distance >= -1 && distance <= 1)
        return true;


    return false;
}