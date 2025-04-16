# Project-3-IT206
Flippy Bird Game Readme file
# Flappy Bird Deluxe - README FILE



Flappy Bird Deluxe is a classic arcade-style game implemented in C++ for the console. Players control a bird, navigating it through a series of randomly generated pipes by making it fly upwards. The goal is to achieve the highest score possible by successfully passing through the gaps between the pipes without colliding with them or the ground. This enhanced version includes features like selectable bird skins, difficulty levels, a high score system, and clear instruction

 1. Game Controls

SPACEBAR: Makes the bird fly upwards. This action decreases the `birdPos` variable, moving the bird up on the console screen.
ESC: Exits the current game and returns to the main menu.
P: Pauses the game. Pressing 'r' resumes the gameplay.

2. Game Features

1)Selectable Bird Skins:  Players can choose from three different visual representations for their bird before starting the game. The `birdSkins` 3D array stores these different skins.
 2)Difficulty Levels: Three difficulty settings (Easy, Medium, Hard) affect the `gameSpeed`, making the game faster as the difficulty increases. This is controlled in the `selectDifficulty()` function.
3)Scoring System: The score increases by 1 for each successfully passed pipe. The `score` variable tracks the current game score, and the `updateScore()` function displays it.
4)High Score: The game keeps track of the highest score achieved across all gameplay sessions, stored in the `highScore` variable and saved/loaded from the `highscore.txt` file.
5)Game Over: The game ends if the bird collides with a pipe or the ground. The `gameover()` function displays the final score and updates the high score if necessary.
6)Instructions: A clear set of instructions is provided in the `instructions()` function, explaining the controls and rules of the game.
7)Animated Title: An introductory animation plays when the game starts, enhancing the user experience.
8)Level Progression: The game increases in level every 5 successful pipe passes, subtly indicating progress.
9)Power-Up : The code includes variables (`powerUpActive`, `powerUpX`, `powerUpY`) related to a potential power-up feature, although the functionality for the power-up itself is not implemented in the provided code.

 3. Code Structure and Explanation=====>


* `#include<iostream>`: Provides input/output functionalities like `cout` (for printing to the console) and `cin` (though not heavily used in the main game loop).
* `#include<conio.h>`: Offers console-related functions like `getch()` (for non-buffered character input) and `getche()` (similar to `getch()` but echoes the character). **Meaning:** These are used for immediate user input without requiring the Enter key. **Usage:** Primarily in menus and for game controls.
* `#include<stdlib.h>`: Includes general utility functions, such as `rand()` (for generating random numbers) and `srand()` (for seeding the random number generator, though not explicitly used in this code, `rand()` still relies on a default seed). **Meaning:** `rand()` is crucial for the random generation of pipe gaps.
* `#include<string.h>`: Provides functions for manipulating C-style strings, like `memcpy()` (for copying memory blocks). **Meaning:** `memcpy()` is used to copy the selected bird skin into the `currentBird` array.
* `#include<windows.h>`: Contains Windows-specific functions for console manipulation, such as `GetStdHandle()`, `SetConsoleCursorPosition()`, `SetConsoleCursorInfo()`, and `SetConsoleTextAttribute()`. **Meaning:** These functions allow precise control over the console's cursor position, visibility, and text color. **Usage:** Used extensively for drawing the game elements at specific locations on the console.
* `#include<time.h>`: Provides functions for working with time and dates (though not directly used in the core game logic of this code snippet).
* `#include<fstream>`: Enables file input/output operations, used here for reading and writing the high score to a file. **Meaning:** Allows the game to persist the high score across different runs. **Usage:** In `loadHighScore()` and the high score update section of `gameover()`.

 Macros (`#define`)

* `#define SCREEN_WIDTH 90`: Defines the total width of the console screen used for the game. **Meaning:** Sets the boundary for the game display.
* `#define SCREEN_HEIGHT 26`: Defines the total height of the console screen used for the game. **Meaning:** Sets the vertical boundary for the game display.
* `#define WIN_WIDTH 70`: Defines the width of the main game window within the console screen. **Meaning:** The area where the bird and pipes are drawn.
* `#define MENU_WIDTH 50`: Defines the width used for displaying the game menu. **Meaning:** Controls the horizontal size of the menu interface.
* `#define GAP_SIZE 7`: Defines the vertical size of the gap between the upper and lower parts of a pipe. **Meaning:** Determines the space the bird needs to fly through.
* `#define PIPE_DIF 45`: Defines the horizontal distance at which the second pipe starts appearing relative to the first. **Meaning:** Controls the spacing between consecutive pipes.
* `#define MAX_LEADERBOARD 5`: This macro is declared but not used in the provided code snippet. It likely intended to limit the number of entries in a leaderboard feature.

### Namespaces

* `using namespace std;`: Brings the standard C++ namespace into scope, allowing the use of elements like `cout` and `endl` without the `std::` prefix.

### Windows API Functions

These functions from `<windows.h>` are crucial for console manipulation:

* `HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);`: Retrieves a handle to the standard output device (the console screen). **Meaning:** Provides a way to interact with the console.
* `COORD CursorPosition;`: A structure that defines the coordinates of the cursor on the console screen (x and y). **Meaning:** Used to position the cursor for drawing elements at specific locations.
* `void gotoxy(int x, int y)`: A custom function that sets the cursor position to the specified `x` (column) and `y` (row) coordinates using `SetConsoleCursorPosition()`. **Meaning:** Enables precise drawing at any point on the console.
* `void setcursor(bool visible, DWORD size)`: A custom function to control the visibility and size of the console cursor using `SetConsoleCursorInfo()`. **Meaning:** Often used to hide the cursor during gameplay for a cleaner look.
* `void setColor(int color)`: A custom function that sets the text color for subsequent console output using `SetConsoleTextAttribute()`. **Meaning:** Adds visual distinction to different game elements.

### Game Variables

These variables store the state of the game:

* `int pipePos[3]`: An array to store the horizontal positions of the pipes. Three elements are declared, but only two are actively used in the main game loop for the currently visible and the next approaching pipe. **Meaning:** Tracks how far each pipe has moved across the screen.
* `int gapPos[3]`: An array to store the vertical position of the gap in each pipe. Similar to `pipePos`, three elements are declared but typically two are used. **Meaning:** Determines where the opening in each pipe is located.
* `int pipeFlag[3]`: An array of flags (0 or 1) to indicate whether a pipe is currently active (being drawn and moving). **Meaning:** Controls the visibility and movement of each pipe.
* `int birdPos = 6`: Stores the current vertical position of the bird on the screen. **Meaning:** Determines the bird's altitude.
* `int score = 0, highScore = 0`: `score` tracks the current game's score, and `highScore` stores the best score achieved.
* `int gameSpeed = 100`: Controls the speed of the game (in milliseconds for the `Sleep()` function). Lower values mean faster gameplay.
* `int difficulty = 1`: Stores the current difficulty level selected by the player.
* `int skinChoice = 0`: Stores the index of the currently selected bird skin.
* `bool powerUpActive = false`: A boolean flag to indicate if a power-up is currently active (not implemented in this version).
* `int powerUpX = -1, powerUpY = -1`: Stores the coordinates of a power-up item (not implemented).
* `int level = 1`: Tracks the current game level, increasing at certain score milestones.

 Bird Skins (`birdSkins`)======>

* `char birdSkins[3][2][6]`: A 3-dimensional character array that stores the different visual representations (skins) of the bird.
    * The first dimension (size 3) represents the number of available skins.
    * The second dimension (size 2) represents the two lines used to draw each bird skin.
    * The third dimension (size 6) represents the characters that make up each line of the bird skin.
* `char currentBird[2][6]`: A 2-dimensional character array that holds the currently selected bird skin, copied from `birdSkins` based on `skinChoice`. **Meaning:** This array is used by the `drawBird()` function to display the bird with the chosen appearance.

 Game Functions=====>

* `void gotoxy(int x, int y)`: Explained in the [Windows API Functions](#windows-api-functions) section.
* `void setcursor(bool visible, DWORD size)`: Explained in the [Windows API Functions](#windows-api-functions) section.
* `void setColor(int color)`: Explained in the [Windows API Functions](#windows-api-functions) section.
* `void drawBorder()`: Draws the boundary of the game window and the information panel on the right side using `=` and `|` characters and sets the color using `setColor()`.
* `void genPipe(int ind)`: Generates a random vertical position for the gap (`gapPos[ind]`) within a pipe. The gap's position is between 3 and 16 (3 + 13) on the y-axis.
* `void drawPipe(int ind)`: Draws a pipe at the horizontal position `WIN_WIDTH - pipePos[ind]`. It draws '*' characters for the upper and lower parts of the pipe, leaving a gap of `GAP_SIZE`. The `pipeFlag[ind]` ensures that only active pipes are drawn.
* `void erasePipe(int ind)`: Erases a pipe by drawing spaces (" ") at the same locations where the pipe was drawn. This creates the illusion of movement.
* `void drawBird()`: Draws the bird using the characters stored in the `currentBird` array at the current `birdPos`. A "▒" character is also drawn for a wing effect.
* `void eraseBird()`: Erases the bird by drawing spaces at its current position.
* `int collision()`: Checks for collision between the bird and the pipes. It checks if the horizontal position of the first pipe overlaps with the bird's horizontal position and if the bird's vertical position is outside the gap of that pipe. Returns 1 if a collision occurs, 0 otherwise.
* `void gameover()`: Called when a collision occurs. Clears the screen, displays the "Game Over" message and the final score. It also updates the `highScore` if the current score is higher and saves it to `highscore.txt`.
* `void updateScore()`: Updates the displayed score and level on the right side of the game window using `gotoxy()` and `cout`. It also indicates whether the power-up is active (though the power-up logic is not implemented).
* `void selectSkin()`: Clears the screen and presents a menu for the player to choose a bird skin. It reads the user's input using `getche()` and updates the `skinChoice` and `currentBird` accordingly.
* `void loadHighScore()`: Reads the high score from the `highscore.txt` file at the beginning of the game. If the file doesn't exist or cannot be opened, it initializes `highScore` to 0.
* `void instructions()`: Clears the screen and displays the game's instructions and controls. It waits for a key press using `getch()` before returning to the menu.
* `void selectDifficulty()`: Clears the screen and presents a menu for the player to choose the difficulty level. It reads the input and sets the `gameSpeed` and `difficulty` accordingly.
* `void animatedTitle()`: Displays an animated title sequence at the start of the game by repeatedly clearing the screen and printing the title with a short delay using `Sleep()`.
* `void play()`: Contains the main game loop. It initializes game variables, draws the initial game state, and then continuously:
    * Checks for user input (`kbhit()` and `getch()`) to control the bird (spacebar for jump, ESC for exit, 'p'/'P' for pause).
    * Draws and erases the bird and pipes to create movement.
    * Checks for collisions using `collision()`.
    * Updates the score and level.
    * Manages the generation and movement of pipes.
    * Uses `Sleep(gameSpeed)` to control the game's pace.
    * Handles the pause functionality.

### Main Function (`main()`)

The entry point of the program. It:

1.  Calls `animatedTitle()` to display the initial animation.
2.  Calls `loadHighScore()` to load the previously saved high score.
3.  Calls `selectSkin()` to allow the player to choose a bird skin.
4.  Enters a `while(1)` loop to display the main menu:
    * Clears the screen and displays the menu options.
    * Reads the user's choice using `getche()`.
    * Calls the appropriate function based on the user's input (e.g., `play()`, `selectDifficulty()`, `instructions()`).
    * Exits the loop and the program if the user chooses option 5.

## 4. Data Structures====>

The primary data structures used in this code are:

a)Arrays:
    * `pipePos[3]`: Integer array to store the horizontal positions of the pipes. **Why?** Arrays provide a fixed-size, contiguous memory location to easily manage the positions of multiple pipes. Three elements are used to handle the current and the next pipe smoothly.
    * `gapPos[3]`: Integer array to store the vertical gap positions of the pipes. **Why?** Similar to `pipePos`, it allows easy management of the gap locations for each pipe.
    * `pipeFlag[3]`: Integer array used as boolean flags to indicate if a pipe is active. **Why?** Efficient way to track the state (active or not) of each pipe.
    * `birdSkins[3][2][6]`: A 3D character array to store the different bird skins. **Why?** A multi-dimensional array is suitable for storing structured character data representing the visual appearance of each skin. The dimensions clearly separate the skin choices, the lines of each skin, and the characters in each line.
    * `currentBird[2][6]`: A 2D character array to hold the currently selected bird skin. **Why?** Provides a direct way to access and use the characters for drawing the bird.

b)Structures from windows:
    * `COORD CursorPosition`: Used to store the x and y coordinates for setting the cursor position on the console. **Why?** Necessary for interacting with the Windows console API to precisely position output.
