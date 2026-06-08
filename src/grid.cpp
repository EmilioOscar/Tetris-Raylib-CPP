#include "grid.h"
#include <iostream>
#include "colors.h"
using namespace std;

Grid::Grid() // Constructor initializes grid dimensions and colors
{
    numCols = 10; // Standard Tetris grid size
    numRows = 20;
    cellSize = 30;

    Initialize();             // Reset grid to empty state
    colors = GetCellcolors(); // Load color palette
}

void Grid::Initialize()
{
    // Set all grid cells to empty (0)
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            grid[row][col] = 0;
        }
    }
}

void Grid::print()
{
    // Debug: print grid contents to console
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw()
{
    // Draw each cell using its value as a color index
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            int cellValue = grid[row][col];
            DrawRectangle(col * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int column)
{
    if (row >= 0 && row < numRows && column >= 0 && column < numCols)
    {
        return false; // Cell is within grid boundaries
    }
    return true; // Cell is outside grid boundaries
}

bool Grid::IsCellEmpty(int row, int column)
{
    if (grid[row][column] == 0)
    {
        return true; // Cell is empty
    }
    return false;
}

int Grid::ClearFullRows()
{
    int numRowsCleared = 0; // Counter for the number of rows cleared
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row)) // Check if the current row is full
        {
            ClearRow(row);    // Clear the full row
            numRowsCleared++; // Increment the counter for cleared rows
        }
        else if (numRowsCleared > 0)
        {
            MoveRowsDown(row, numRowsCleared); // Move rows down to fill the cleared space
        }
    }
    return numRowsCleared; // Return the total number of rows cleared
}

bool Grid::IsRowFull(int row)
{
    for (int column = 0; column < numCols; column++)
    {
        if (grid[row][column] == 0)
        {
            return false; // Found an empty cell, row is not full
        }
    }
    return true; // All cells in the row are filled, row is full
}

void Grid::ClearRow(int row)
{
    for (int column = 0; column < numCols; column++)
    {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowsDown(int Row, int numRowsToMove)
{
    for (int column = 0; column < numCols; column++)
    {
        grid[Row + numRowsToMove][column] = grid[Row][column]; // Move the row down by copying its values to the new position
        grid[Row][column] = 0;                                 // Clear the original row after moving
    }
}
