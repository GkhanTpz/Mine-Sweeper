#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TABLE_SIZE 8 // Defines the size of the game board as 8x8.
#define MINE_SIZE 7 // Defines the maximum number of mines.
#define WIN 1 // Indicates the player has won the game.
#define LOSE -1 // Indicates the player has lost the game.
#define CONTINUE 0 // Indicates the game is still ongoing.

// Global Variables
int mine, result, count = 0, dCount = 0; // Variables for mine count, game result, flag count, and flags marked by player.
int subTable[TABLE_SIZE + 2][TABLE_SIZE + 2]; // Sub table to store the actual game data including mines and counts.
char table[TABLE_SIZE + 2][TABLE_SIZE + 2]; // Main table to display to the player.

// Function Declarations
void CreateSubTable(); // Creates the sub table with mines and numbers.
void InitializerTable(); // Initializes the main display table.
void PrintSubTable(); // Prints the sub table to the console (for debugging).
void PrintTable(); // Prints the main table to the console.
void PlaceMines(); // Places mines randomly on the game board.
int CheckGame(); // Checks the status of the game.
void Explorer(int row, int column); // Explores the cells recursively.
int Digger(int row, int column); // Handles digging action.
void TryPlay(); // Handles the prompt to replay the game.

int main()
{
    int row, column;
    char action; // Action can be "c" (check), "d" (dig), "e" (explore).

    printf("%s","Welcome to Mine Sweeper\n\n");

    CreateSubTable(); // Initialize the game data.
    InitializerTable(); // Initialize the display table.

    while(true)
    {
        PrintTable(); // Display the current state of the game.
        printf("\n");
        printf("%s",
               "Please enter values of coordinate (c,row,column or d, row, column or e, row, column):" );
        scanf(" %c,%d,%d", &action, &row, &column);
        printf("\n");

        if(action == 'c') // Check action.
            result = Digger(row, column);
        else if(action == 'd') // Dig action.
        {
            if(mine > dCount)
            {
                dCount++;
                table[row][column] = 'D';
                result = CheckGame();
            }
        }
        else if(action == 'e') // Explore action.
        {
            if(dCount > 0)
                dCount--;

            table[row][column] = '#';
            result = Digger(row, column);
        }

        if(result == LOSE) // If player hits a mine.
        {
            printf("%s","Game Over!\n");
            PrintSubTable();
            TryPlay();
        }

        if(result == WIN) // If player wins the game.
        {
            printf("%s","Congratulations!");
            PrintSubTable();
            TryPlay();
        }
    }

    return 0;
}

void CreateSubTable()
{
    // Initialize the sub table with zeros and set boundaries.
    for(int i = 0; i <= TABLE_SIZE + 1; i++)
        for(int j = 0 ; j <= TABLE_SIZE + 1; j++)
        {
            subTable[i][j] = 0;
        }

    for(int i = 0; i <= TABLE_SIZE + 1; i++)
    {
        subTable[i][0] = 1;
        subTable[i][TABLE_SIZE + 1] = 1;
    }

    for(int j = 0 ; j <= TABLE_SIZE; j++)
    {
        subTable[0][j] = 1;
        subTable[TABLE_SIZE + 1][j] = 1;
    }

    mine = MINE_SIZE;
    PlaceMines(); // Place the mines randomly.
}

void InitializerTable()
{
    // Initialize the main table with '#' and set boundaries.
    for(int i = 0; i <= TABLE_SIZE + 1; i++)
        for(int j = 0 ; j <= TABLE_SIZE + 1; j++)
        {
            table[i][j] = '#';
        }

    for(int i = 0; i <= TABLE_SIZE + 1; i++)
    {
        table[i][0] = '*';
        table[i][TABLE_SIZE + 1] = '*';
    }

    for(int j = 0 ; j <= TABLE_SIZE; j++)
    {
        table[0][j] = '*';
        table[TABLE_SIZE + 1][j] = '*';
    }
}

void PrintTable()
{
    // Print the main table to the console.
    printf("   ");
    for(int i = 1; i <= TABLE_SIZE; i++)
        printf("%3d",i);

    printf("\n   ");

    for(int i = 1; i <= TABLE_SIZE + 1; i++)
        printf("---");

    printf("\n");

    for(int i = 1; i <= TABLE_SIZE; i++)
    {
        printf("%3d|", i);
        for(int j = 1; j <= TABLE_SIZE; j++)
            printf("%3c",table[i][j]);

        printf(" |%d\n",i);
    }

    printf("   ");
    for(int i = 1; i <= TABLE_SIZE + 1; i++)
        printf("---");

     printf("\n");
}

void PrintSubTable()
{
    // Print the sub table (with mines and numbers) to the console.
    printf("   ");
    for(int i = 1; i <= TABLE_SIZE; i++)
        printf("%3d", i);

    printf("\n   ");

    for(int i = 1; i <= TABLE_SIZE + 1; i++)
        printf("---");

    printf("\n");

    for(int i = 1; i <= TABLE_SIZE; i++)
    {
        printf("%3d|", i);
        for(int j = 1; j <= TABLE_SIZE; j++)
        {
            if(subTable[i][j] == -1)
                printf("  *"); // Indicate mines.
            else
                printf("%3d", subTable[i][j]); // Print mine count.
        }
        printf(" |%d\n", i);
    }

    printf("   ");
    for(int i = 1; i <= TABLE_SIZE + 1; i++)
        printf("---");

    printf("\n");
}

void PlaceMines()
{
    int j, row, column;
    srand(time(NULL));
    mine = MINE_SIZE;

    // Place mines randomly on the board.
    for(int i = 0; i <= mine; i++)
    {
        row = 1 + rand() % TABLE_SIZE;
        column = 1 + rand() % TABLE_SIZE;

        if(subTable[row][column] == -1)
            i--; // If there's already a mine here, try again

        subTable[row][column] = -1;

        // Update the surrounding cells' mine counts.
        for(int x = -1; x <= 1; x++)
            for(int y = -1; y <= 1; y++)
            {
                if(subTable[row][column] == -1)
                {
                    if(subTable[row + x][column + y] != -1)
                        subTable[row + x][column + y]++;
                }
            }
    }
}

int Digger(int row, int column)
{
    int gameCheck = 0;

    if(subTable[row][column] == -1)
        gameCheck = LOSE; // Player hit a mine.
    else if(subTable[row][column] > 0)
    {
        table[row][column] = ('0' + subTable[row][column]);
        gameCheck = CheckGame(); // Check if game is won.
        gameCheck = CONTINUE;
    }
    else
    {
        Explorer(row, column); // Explore empty cells.
        gameCheck = CheckGame(); // Check if game is won.
    }

    return gameCheck;
}

void Explorer(int row, int column)
{
    if(row < 1 || row > TABLE_SIZE || column < 1 || column > TABLE_SIZE)
        return; // Out of bounds check.

    if(table[row][column] != '#')
        return; // Already explored check.

    table[row][column] = '0' + subTable[row][column];

    // Explore surrounding cells recursively.
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <= 1; j++)
        {
            if(subTable[row + i][column + j] > 0 && table[row + i][column + j] == '#')
            {
                table[row + i][column + j] = '0' + subTable[row + i][column + j];
            }
            else if(subTable[row + i][column + j] == 0 && table[row + i][column + j] == '#')
            {
                Explorer(row + i, column + j);
            }
        }
}

int CheckGame()
{
    int status;
    count = 0;

    // Count the number of mines.
    for(int i = 1; i <= TABLE_SIZE; i++)
        for(int j = 1; j <= TABLE_SIZE; j++)
            if(subTable[i][j] == -1)
                count++;

    // Check if all mines are flagged.
    if(count == MINE_SIZE)
        status = WIN;
    else
        status = CONTINUE;

    return status;
}

void TryPlay()
{
    int tryPlay;
    printf("%s","Try Retry? (1: Yes, 0: No)\n");
    scanf("%d", &tryPlay);

    switch(tryPlay)
    {
        case 0:
            printf("%s","Thank you to play.\n");
            exit(0);
            break;

        case 1:
            dCount = 0;
            result = CONTINUE;
            CreateSubTable();
            InitializerTable();
            exit(0);
            break;

        default:
            printf("%s","Invalid value");
            exit(0);
            break;
    }
}
