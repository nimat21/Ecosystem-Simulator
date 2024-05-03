## Main Function (`main.cpp`)

#### Overview:
The `main` function acts as the program's entry point, orchestrating the initialization of the ecosystem, running the simulation, and handling user interactions.

#### Key Steps:
1. **File Handling**: Extracts file paths for the map and species files from command-line arguments.
2. **Initialization**: Retrieves map dimensions and organism coordinates, parses species information, and creates organism objects.
3. **Simulation Loop**: Executes the main simulation loop, allowing users to interact with and control the simulation.
4. **Cleanup**: Deletes organism objects before ending the program.

## Organism Class (`Organism.h`)

#### Overview:
The `Organism` class serves as the foundation for all organisms within the ecosystem. It's designed as an abstract class to encapsulate common attributes and behaviors shared by all organisms.

#### Key Attributes:
1. **Unique Identifier**: `m_id` uniquely identifies each organism.
2. **Type Identification**: `m_letter_id` and `m_type` distinguish the organism type.
3. **Health Management**: Tracks current and maximum health points (`m_current_health` and `m_max_health`) **NOTE**: In the project spec, this was referred to as *energy level* rather than health. So `m_current_health` can be thought of as the organism's current energy level, and `m_max_health` can be thought of as the organism's max energy level.
4. **Spatial Information**: Stores coordinates (`m_coords`) to locate organisms on the map.
5. **Liveness Indicator**: `m_alive` flag denotes whether the organism is alive.
6. **Predator/Prey Settings**: `m_PREDATORS_MAP`/`m_PREY_MAP` keep track of predator/prey relations between various organism types.

#### Key Methods:
1. **Update**: Virtual method `update` defines the generic behavior for updating an organism's state.

#### Additional Notes:
- **Abstraction**: By defining common attributes and methods in the `Organism` class, it ensures consistency and allows for polymorphic behavior.
- **Predator-Prey Relationships**: The static `predators` and `prey` map is vital for modeling interactions between different species, influencing behavior and population dynamics.

## Plant Class (`Plant.h`)

#### Overview:
The `Plant` class, derived from `Organism`, represents vegetation within the ecosystem. It extends the base class with plant-specific attributes and behaviors.

#### Additional Attributes:
1. **Energy Points**: `m_energy_points` quantify the energy level of the plant.

#### Additional Methods:
1. **Revive**: `revive` method restores a plant to its maximum health, bringing it back to life.
2. **Update Override**: Overrides the `update` method to implement plant-specific behavior.

## Animal Class (`Animal.h`)

#### Overview:
The `Animal` class, also derived from `Organism`, models animal organisms. It augments the base class with characteristics and actions specific to animals.

#### Additional Methods:
1. **Update Override**: `update` method is overridden to implement animal-specific behavior.
2. **Eating Behavior**: `eat` method simulates the animal consuming another organism, regulating energy and population dynamics.
3. **Movement Capability**: `moveTo` method allows animals to move up/down/left/right by 1 unit

## Ecosystem Class (`Ecosystem.h`)

#### Overview:
The `Ecosystem` class acts as the central hub for managing the simulation's ecosystem, providing methods for initialization and data handling.

#### Methods:
1. **Map Handling**: Methods like `getMapDimensions` and `getOrgCoords` extract map information and organism coordinates from files.
2. **Species Management**: `getSpeciesInfo` parses species data from files, facilitating organism creation.

#### Additional Notes:
- **Input Validation**: Robust input validation ensures data integrity and prevents runtime errors.

## Helper Class (`Helper.h`)

#### Methods:
1. **Terminal Operations**: `moveCursor` and `clearScreen` facilitate terminal manipulation for displaying simulation output.
2. **Utility Functions**: Methods like `sleep`, `fileExists`, and input validators streamline common tasks and enhance user experience.

#### Additional Notes:
- **Utility Functions**: The `Helper` class encapsulates commonly used functionalities, promoting code reuse and maintainability.
- **User Interaction**: Providing user-friendly interfaces and feedback mechanisms enhances the simulation's usability and accessibility.