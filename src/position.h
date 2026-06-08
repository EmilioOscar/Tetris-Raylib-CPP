#pragma once

class Position
{ // Class definition for Position, representing a position in the grid
public:
    Position(int row, int column); // Constructor that takes row and column as parameters to initialize the position
    int row;
    int column;
};