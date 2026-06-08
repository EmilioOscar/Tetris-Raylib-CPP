#include "block.h"
#include <raylib.h>

Block::Block() // Constructor initializes block properties
{
    // id = 0; // Default block type (can be set to 1-7 for different tetromino shapes)
    cellSize = 30;            // Size of each cell in pixels
    rotationState = 0;        // Initial rotation state
    colors = GetCellcolors(); // Load color palette
    rowOffset = 0;            // Initial row offset for block position
    columnOffset = 0;         // Initial column offset to start near the middle of the grid
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions(); // Get current rotation state cell positions
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;       // Update row offset based on movement
    columnOffset += columns; // Update column offset based on movement
}
std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState]; // Get current rotation state cell positions
    std::vector<Position> movedTiles;                   // Vector to hold positions after applying offsets
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset); // Apply offsets to get new position
        movedTiles.push_back(newPos);                                                 // Add new position to the vector
    }
    return movedTiles; // Return the current cell positions of the block based on its rotation and offsets
}

void Block::Rotate()
{
    rotationState = (rotationState + 1) % cells.size();
}

void Block::UndoRotation()
{
    rotationState--;
    if (rotationState == -1)
    {
        rotationState = cells.size() - 1;
    }
}
