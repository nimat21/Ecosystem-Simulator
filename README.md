## Overview

Welcome to the Ecosystem Simulator! The Ecosystem Simulator is a C++ project designed to simulate the dynamics of a simple terrestrial ecosystem. Organisms such as plants, herbivores, and omnivores populate a rectangular map, each exhibiting distinct behavior based on their characteristics.

### Organism Behavior

- **Plants**: Plants remain stationary and regrow over time according to their `regrowth coefficient`. For example, if a plant with a `regrowth coefficient` of 3 has been eaten, then it will respawn in 3 iterations (assuming no animal is standing over it). They provide energy points when consumed by animals.
- **Herbivores**: Herbivores move around the ecosystem to find and consume plants. They have a maximum energy level that limits the number of energy points they can absorb. They are also hunted by omnivores so they will attempt to flee when they detect an omnivore nearby.
- **Omnivores**: Omnivores exhibit similar behavior to herbivores but can consume both plants and herbivores.

### Example Species List

Each species is defined by its category (plant, herbivore, or omnivore), a one-letter identifier, and specific characteristics such as regrowth coefficient or maximum energy level. 
The format to include plants in your species list file should be as follows: `plant` *`<one-letter id> <regrowth coefficient> <energy points>`*.
The format to include animals in your species file should be as follows: `herbivore/omnivore` *`<one-letter id> <max energy level>`*
Here's an example list of species that can be used with the simulator:
```
plant a 1 5
plant b 3 10
herbivore A 20
herbivore B 15
omnivore C 40
omnivore D 30
```
More example lists can be seen in the `input` directory.

### Area Map

The area map is a two-dimensional grid where each character represents either open space or the position of a living organism. Living organisms are referenced using their corresponding one-letter identifiers as defined in the list of species. Here's an example of a 10x10 area map that can be used with the simulator that works with the example species list above:
```
        aa
b     D   
          
 a a   B  
   a  A   
          
bb        
b         
 bbb      
      C   
```
More example maps acn be seen in the `input` directory.

## How to Use

Before getting started, ensure you have the following dependencies installed on your system:

- C++ compiler (e.g., g++)
- GNU Make
- An up-to-date terminal (I don't know what version it must be, but if it's old then you'll get really weird behavior during the simulation)

To use the Ecosystem Simulator, follow these steps:

1. Clone the repository to your local machine: `git clone <repository_url>`

2. Navigate to the `src` directory

3. Place your map and species list files in the `input` directory of the project.

4. Run the source files using the provided Makefile by simply running the `make` command

5. Run the simulator with the desired input files (map and species list) like so: `./ecosystem.bin ../input/map.txt ../input/species.txt`. Replace `../input/map.txt` and `../input/species.txt` with your desired map/species files. 
To run the sample program, use the command `make sample`.

## Extra Credit
This project includes two additional features that enhance its functionality beyond the initial project specifications:

1. **Color-coded Organisms:** Each organism in the ecosystem is represented with its character ID displayed in a color unique to its species type. Plants are depicted in green, herbivores in blue, and omnivores in red. This visual distinction allows for easy identification and analysis of different organism types within the simulation. This was done using ANSI Escape Code colors.
2. **Flexible Iteration Control:** In addition to single-step iteration, users can choose to run multiple iterations of the ecosystem simulation in a batch. This feature enables users to specify the number of iterations to run and adjust the `sleep_time` between each iteration. By controlling the pace of updates, users can observe the ecosystem dynamics in detail or expedite the simulation for faster analysis.

These extra credit features provide added depth and usability to the ecosystem simulation, enhancing the overall user experience and analytical capabilities.