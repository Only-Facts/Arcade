# Arcade Documentation

## Overview

Arcade is built as a modular program. The executable `arcade` is the core of the project. It does not directly contain any game logic or graphics implementation. Instead, it loads shared libraries at runtime from the `./lib/` directory.

There are two types of libraries:

- graphics libraries
- game libraries

Each library must be compiled as a shared object (`.so`) and must follow the interfaces defined in the project.

The goal of this architecture is to make the program extensible. A new game can be added without changing the core, and a new graphics library can also be added without rewriting existing games.

---

## General architecture

The project is separated into three main parts:

- the core
- the graphics libraries
- the game libraries

The core is responsible for:

- loading libraries dynamically
- checking that the selected library is valid
- displaying the menu
- letting the user choose a game
- switching between games and graphics libraries at runtime
- forwarding user input
- running the main loop
- handling scores and general program flow

A graphics library is responsible for:

- initializing its backend
- reading user input
- converting low-level input into abstract actions
- rendering the current frame
- shutting down properly when the library is unloaded

A game library is responsible for:

- storing the game state
- updating game logic
- receiving abstract input actions
- returning the elements that must be displayed
- managing score and game-specific rules

The game libraries and graphics libraries must stay independent from each other.  
A game must not depend on ncurses, SDL2, or any other rendering backend.  
A graphics library must not contain game logic.

---

## Role of the shared interfaces

The communication between the core and the plugins is done through shared interfaces.

The game interface defines what the core expects from a game library.  
A game must be able to:

- reset itself
- update itself
- receive input
- return what should be displayed
- return the current score
- return its name

The graphics interface defines what the core expects from a graphics library.  
A graphics library must be able to:

- initialize its rendering system
- shut it down
- clear the frame
- draw the current game state
- display the rendered frame
- return user input to the core

Because all plugins use the same interfaces, the core can handle them in a generic way.  
This is what makes runtime switching possible.

---

## Shared data

The project also uses common data types shared by the whole architecture.

These shared types are used to:

- identify the type of a plugin
- represent user input in a generic way
- represent the elements that must be displayed on screen

For example, the game can describe a wall, a player, an enemy, food, or text using common display data. The graphics library reads this data and decides how to render it on screen.

This approach allows the game to stay completely independent from the rendering backend.

---

## Dynamic loading

The project uses dynamic loading to handle plugins at runtime.

The loading process is the following:

1. the user launches the program with one graphics library as argument
2. the core loads this graphics library
3. the core scans the `./lib/` directory to find available game and graphics libraries
4. the menu is displayed
5. the user chooses a game
6. the core loads the selected game library
7. the main loop starts
8. during execution, the user can switch to another game or another graphics library

This mechanism allows the program to be extended without recompiling the whole project.

---

## How a new game library is implemented

To create a new compatible game library, the developer must:

1. create a class implementing the game interface
2. implement all required methods
3. keep the full game state inside the class
4. translate the game state into common display data
5. export the creation function expected by the core
6. compile the result as a shared object in `./lib/`

A game library must only deal with:

- game rules
- score
- movement
- collisions
- win or lose conditions
- generation of display data

A game library must not:

- use ncurses, SDL2, or any graphics library directly
- process raw keyboard events directly
- contain menu logic
- handle library switching

This separation ensures that the same game can run with multiple graphics backends without modification.

---

## How a new graphics library is implemented

To create a new compatible graphics library, the developer must:

1. create a class implementing the graphics interface
2. initialize the backend correctly
3. convert backend events into abstract input actions
4. read the display data received from the core
5. render each element on screen
6. export the creation function expected by the core
7. compile the result as a shared object in `./lib/`

A graphics library must only deal with:

- backend initialization
- window or terminal management
- rendering
- input polling
- backend cleanup

A graphics library must not:

- implement game logic
- store scores
- decide the rules of a game
- depend on a specific game

This allows the same graphics backend to render multiple games.

---

## Main loop

The main loop always follows the same general logic.

First, the graphics library returns one abstract input action.  
Then the core handles global actions such as:

- quit
- restart
- return to menu
- next game
- previous game
- next graphics library
- previous graphics library

If the action is a gameplay action, it is sent to the current game.

The game then updates its internal state.  
After that, the game produces the display data representing the current frame.  
Finally, the graphics library renders this frame.

So the flow is always:

- input from graphics
- processing in core
- update in game
- rendering in graphics

This design keeps the responsibilities clearly separated.

---

## Menu and runtime switching

The menu is managed by the core. It is responsible for displaying:

- the list of available game libraries
- the list of available graphics libraries
- the player name field
- the scores

The user can select a game from the menu, start it, go back to the menu later, and switch to another game or graphics library without restarting the executable.

This is one of the most important parts of the project, because it proves that the core handles libraries generically and dynamically.

---

## Scores

The Arcade platform must keep a register of player scores.

This is handled by the core, not by the graphics libraries and not directly by the games.  
A game only provides its current score.  
The core is responsible for:

- saving scores
- loading scores
- associating scores with a player name and a game name
- displaying scores in the menu

This keeps the game plugins simple and focused on gameplay only.

---

## Compilation rules

Every plugin must:

- be compiled as a shared object
- be placed in the `./lib/` directory
- expose the correct creation function
- use only the shared project interfaces and types

Examples of valid output files:

- `lib/arcade_ncurses.so`
- `lib/arcade_sdl2.so`
- `lib/arcade_snake.so`
- `lib/arcade_pacman.so`

The core executable must not directly link to the game and graphics libraries as normal source modules. They must be loaded dynamically at runtime.

---

## Compatibility rules

A plugin is compatible with the Arcade core if:

- it implements the correct interface
- it exports the expected symbol
- it is compiled as a `.so`
- it is placed in `./lib/`
- it only uses the common project types for communication

If one of these conditions is not respected, the core must reject the library.

---

## Explanatory manual

The Arcade project is designed to separate responsibilities clearly.

The core manages the application as a whole. It controls startup, dynamic loading, menu navigation, game launching, library switching, and score management. It never contains the logic of a specific game and never depends on a specific rendering backend.

A game plugin contains only the rules and state of a game. It receives abstract input and returns abstract display data. Because of this, it can run with any compatible graphics library.

A graphics plugin contains only backend-specific code. It handles rendering and input, but it does not know the rules of the current game. It only interprets the display data it receives.

The loader is used to open shared libraries, retrieve the exported symbols, and unload them when necessary. The directory scanner is used to detect which libraries are available in `./lib/` and classify them as game or graphics plugins.

This architecture makes the project easy to extend. A new game can be added by implementing the game interface and compiling a new `.so`. A new graphics library can be added in the same way. The core does not need to be rewritten each time a new module is added.

This design is the main strength of the Arcade project, because it demonstrates the use of abstraction, dynamic loading, and modular programming in C++.
