# Multi-threadingSimulation
GHOSTBUSTERS
# Ghostbuster-Inspired Simulation

A multi-threaded C simulation where hunters work to identify a ghost roaming through a haunted building. Inspired by paranormal investigation games and movies.

![Ghostbusters Theme](https://img.icons8.com/color/96/000000/ghost.png)

## Key Features
- **Haunted Building**: 13 interconnected rooms including Van, Basement, and Bedrooms
- **4 Ghost Types**: Poltergeist, Banshee, Bullies, Phantom with unique evidence patterns
- **Hunter Team**: 4 players with specialized equipment (EMF, Thermometer, etc.)
- **Real-Time Mechanics**: 
  - Ghost leaves paranormal evidence
  - Hunters collect evidence while managing fear
  - Threaded movement/actions
- **Win Conditions**:
  - Hunters identify ghost type before getting too scared/bored
  - Ghost escapes if hunters fail

## Installation
```bash
# Requires GCC and pthreads
make clean && make
