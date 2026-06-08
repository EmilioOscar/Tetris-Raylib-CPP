#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block // Class definition for Block, representing a block in the Tetris game
{
public:
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    int id;                                     // Unique identifier for the block type (e.g., 1-7 for different tetromino shapes)
    std::map<int, std::vector<Position>> cells; // Map of rotation states to their corresponding cell positions

private:
    int cellSize;               // Size of each cell in pixels
    int rotationState;          // Current rotation state of the block (0-3)
    std ::vector<Color> colors; // Color palette for the block, matching the colors used in Grid::GetCellcolors()
    int rowOffset;              // Row offset for the block's position on the grid
    int columnOffset;           // Column offset for the block's position on the grid
};
