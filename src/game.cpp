#include "raylib.h"
#include "game.h"
#include <random>

Game::Game() // Constructor initializes the game state
{
    grid = Grid();                   // Initialize the game grid
    blocks = GetAllBlocks();         // Initialize the vector to hold blocks
    currentBlock = GetRandomBlock(); // Get the first random block to start the game
    nextBlock = GetRandomBlock();    // Get the next random block for preview
    gameOver = false;
    score = 0;         // Initialize game over state
    InitAudioDevice(); // Initialize audio device for sound effects (if needed)
    music = LoadMusicStream("Sounds/Background.mp3");
    SetMusicVolume(music, 0.2f); // Load background music
    PlayMusicStream(music);

    // Start playing background music
    rotateSound = LoadSound("Sounds/rotate.mp3");
    SetSoundVolume(rotateSound, 3.0f); // Load sound effect for block rotation

    clearSound = LoadSound("Sounds/clear.mp3");
    SetSoundVolume(clearSound, 3.0f); // Load sound effect for clearing rows
}

Game::~Game() // Destructor to clean up resources
{
    UnloadSound(rotateSound); // Unload sound effect for block rotation
    UnloadSound(clearSound);  // Unload sound effect for clearing rows
    UnloadMusicStream(music); // Unload background music
    CloseAudioDevice();       // Close audio device when the game is destroyed
}

Block Game::GetRandomBlock() // Function to get a random block from the blocks vector
{
    if (blocks.empty()) // Check if there are no blocks left to return
    {
        blocks = GetAllBlocks(); // Refill the blocks vector if it's empty
    }

    int randomIndex = rand() % blocks.size();   // Generate a random index based on the size of the blocks vector
    Block block = blocks[randomIndex];          // Get the block at the random index
    blocks.erase(blocks.begin() + randomIndex); // Clear the block's state to ensure it starts fresh
    return block;
}
std::vector<Block> Game::GetAllBlocks() // Define the static member variable to hold the blocks in the game
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw() // Function to draw the current game state
{
    grid.Draw(); // Draw the game grid

    currentBlock.Draw(11, 11); // Draw the current block on the grid
    switch (nextBlock.id)
    {
    case 3:                       // IBlock
        nextBlock.Draw(255, 290); // Draw the I-shaped block in the preview area
        break;
    case 4:                       // OBlock
        nextBlock.Draw(255, 290); // Draw the O-shaped block in the preview
        break;
    default:
        nextBlock.Draw(270, 270); // Draw other blocks in the preview area
        break;
    }
}

void Game::HandleInput()
{
    int KeyPressed = GetKeyPressed();
    if (gameOver && KeyPressed != 0) // Check if the game is over and any key is pressed to reset the game
    {
        gameOver = false; // Reset game over state if any key is pressed
        reset();
    }
    switch (KeyPressed)
    {
    case KEY_LEFT: //
    case KEY_A:
        MoveBlockLeft(); // Move the current block left when the left arrow key is pressed
        break;

    case KEY_RIGHT:
    case KEY_D:
        MoveBlockRight(); // Move the current block right when the right arrow key is pressed
        break;

    case KEY_DOWN:
    case KEY_S:
        MoveBlockDown();   // Move the current block down when the down arrow key is pressed
        UpdateScore(0, 1); // Add points for moving the block down (if applicable)
        break;
    case KEY_UP:
    case KEY_W:
        RotateBlock(); // Rotate the current block when the up arrow key is pressed
        break;
    }
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        {
            currentBlock.Move(0, -1); // Move the current block left by updating its column offset
            if (IsBlockOutside() || BlockFits() == false)
            {
                currentBlock.Move(0, 1); // Move the current block back to its original position
            }
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1); // Move the current block right by updating its column offset
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1); // Move the current block back to its original position
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0); // Move the current block down by updating its row offset
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0); // Move the current block back to its original position
            LockBlock();              // Lock the block in place on the grid
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions(); // Get the current cell positions of the block
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column)) // Check if any cell of the block is outside the grid boundaries
        {
            return true; // Return true if the block is outside the grid
        }
    }

    return false; // Return false if the block is within the grid boundaries
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation(); // Rotate the block back to its original orientation if the new orientation is outside the grid
        }
        else
        {
            PlaySound(rotateSound); // Play the rotation sound effect if the block was successfully rotated
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions(); // Get the current cell positions of the block
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id; // Set the grid cell to the block's ID to lock it in place
    }
    currentBlock = nextBlock;
    if (BlockFits() == false)
    {
        gameOver = true; // Set game over state if the next block does not fit in the starting position
    }
    nextBlock = GetRandomBlock();           // Get a new random block for the next block
    int rowsCleared = grid.ClearFullRows(); // Clear any full rows from the grid after locking the block
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);       // Play the clear sound effect if any rows were cleared
        UpdateScore(rowsCleared, 0); // Update the score based on the number of rows cleared
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions(); // Get the current cell positions of the block
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false) // Check if any cell of the block is not empty in the grid
        {
            return false; // Return false if the block does not fit in the current position
        }
    }
    return true; // Return true if the block fits in the current position
}

void Game::reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();         // Refill the blocks vector with all block types
    currentBlock = GetRandomBlock(); // Get a new random block to start the game
    nextBlock = GetRandomBlock();    // Get a new random block for the next block
    score = 0;                       // Reset the score to 0
}

void Game::UpdateScore(int rowsCleared, int moveDownPoints)
{
    switch (rowsCleared) // Update the score based on the number of rows cleared
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += moveDownPoints; // Add points for moving the block down (if applicable)
}
