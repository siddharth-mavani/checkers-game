# checkers-game

# Requirements
    GCC compiler
    GNU make

# Set-Up Instructions 

    1. Clone the repository to your local system by  `git clone https://github.com/siddharth-mavani/checkers-game.git`
    2. CD into the cloned repository.
    3. run `make checkers` in the terminal to compile the code and generate the executable.
    4. run `./checkers` in the terminal to start playing the game.

# Game Instructions

    1. Enter 1 to start new game. 

        I. Enter the information about the players to start the game.
        II. Enter the following commands to use the provided functionalities according to the given syntax as instructions on the side of the board:
            
            A. MOVE, to move the tokens.
            B. UNDO, to undo the previous move with consensus of both the players.
            C. REVIEW, to launch the game review.
            D. SUGGEST, to help yourself with the moves suggested by the program.
            E. NEKTK, to get all possible moves in next `K` turns. 
            F. SAVE, to save the game you are playing.
            G. UPDATE, to update the game-file of the previously played game.
            H. SETTINGS, to access the in game settings.
            I. QUIT, to quit the game.

    2. Enter 2 to load a saved game, followed by the name of the game.
    3. Enter 3 to change the game settings. The following settings can be modified

        I. Auto Rotate
        II. Compulsory Capture
        
    4. Enter 4 to exit the game.