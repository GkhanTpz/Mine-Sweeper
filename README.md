---

# Mine Sweeper Game in C

This project is a simple implementation of the classic **Mine Sweeper** game written in **C**. It features an 8x8 grid where the player must locate hidden mines. The player wins by flagging all the mines or uncovering all safe cells. Conversely, the player loses by uncovering a mine.

## How the Game Works

- The game board consists of an 8x8 grid (modifiable via the `TABLE_SIZE` definition).
- **Mines** are placed randomly on the grid, with the number of mines set to `MINE_SIZE` (default: 7).
- The player can perform three types of actions on the grid:
  - **Check (`c`)**: Check a cell to see if it's a mine or a safe number.
  - **Dig (`d`)**: Place a flag on a cell that the player believes contains a mine.
  - **Explore (`e`)**: Remove a flag and explore the cell (similar to the "check" action).
- The game continues until the player either successfully flags all mines (victory) or uncovers a mine (loss).

### Key Features
1. **Dynamic Mine Placement**: Mines are placed randomly each time the game starts.
2. **Recursive Exploration**: If a player uncovers an empty (zero adjacent mines) cell, adjacent cells are recursively explored, similar to the original game.
3. **Victory and Loss Conditions**: The game checks for a win when all mines are flagged correctly, or a loss when the player digs up a mine.

## File Structure

The game is implemented in a single C file with the following key components:

### Global Variables
```c
int mine, result, count = 0, dCount = 0;
int subTable[TABLE_SIZE + 2][TABLE_SIZE + 2];
char table[TABLE_SIZE + 2][TABLE_SIZE + 2];
```
- **`mine`**: The total number of mines.
- **`result`**: The current status of the game (`WIN`, `LOSE`, `CONTINUE`).
- **`count` & `dCount`**: Track the player's progress with flagged mines and remaining unflagged mines.
- **`subTable`**: Stores the hidden game data (mines and adjacent mine counts).
- **`table`**: Stores the visible game board displayed to the player.

### Function Descriptions

- **`CreateSubTable()`**: Initializes the hidden game board, places mines randomly, and calculates adjacent mine counts.
  
- **`InitializerTable()`**: Initializes the visible table with `#` characters and sets boundaries around the game grid.
  
- **`PrintTable()`**: Displays the current state of the game board, showing flagged cells, explored numbers, and unvisited cells.
  
- **`PrintSubTable()`**: (For debugging) Prints the hidden game board, revealing mine positions and adjacent mine counts.
  
- **`PlaceMines()`**: Randomly places mines on the board and updates adjacent cell counts. Ensures no two mines are placed on the same spot.
  
- **`CheckGame()`**: Evaluates if the player has won by counting correctly flagged mines.
  
- **`Dig()`**: Handles the player's action of checking a cell. If the cell contains a mine, the game is lost. If it contains a number or empty space, it is revealed.
  
- **`Explorer()`**: Recursively explores adjacent cells when the player checks an empty cell (with zero adjacent mines).
  
- **`TryPlay()`**: After a game is won or lost, the player is asked if they want to play again.

### How to Play

1. Start the game by running the program. The board will be displayed with numbers representing rows and columns.
   
2. Enter your action using the format: 
   ```
   <action>,<row>,<column>
   ```
   - **`c`**: Check a cell at the specified coordinates.
   - **`d`**: Place a flag at the specified coordinates to mark a mine.
   - **`e`**: Remove a flag and explore the cell.
   
3. The game ends when:
   - The player wins by flagging all the mines, or
   - The player loses by uncovering a mine.

4. After the game ends, you can choose to play again or exit.

### Example Gameplay

```
Welcome to Mine Sweeper

   1  2  3  4  5  6  7  8
   -------------------------
 1| #  #  #  #  #  #  #  # |1
 2| #  #  #  #  #  #  #  # |2
 3| #  #  #  #  #  #  #  # |3
 4| #  #  #  #  #  #  #  # |4
 5| #  #  #  #  #  #  #  # |5
 6| #  #  #  #  #  #  #  # |6
 7| #  #  #  #  #  #  #  # |7
 8| #  #  #  #  #  #  #  # |8
   -------------------------
Please enter values of coordinate (c,row,column or d, row, column or e, row, column): c,3,4
```

In this example, the player is checking cell (3,4). Depending on whether this cell contains a mine or not, the game will proceed accordingly.

### Future Enhancements
Potential improvements for this project include:
- Adding different difficulty levels (varying grid size and mine count).
- Implementing a graphical user interface (GUI) for better user experience.
- Adding a timer to track how long it takes for players to finish the game.

---


## 📝 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
