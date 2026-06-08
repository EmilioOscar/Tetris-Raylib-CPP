#include "block.h"
#include "position.h"

class LBlock : public Block
{ // Class definition for the L-shaped block, inheriting from Block
public:
    LBlock()
    {
        id = 1;                                                                      // Unique identifier for the L-shaped block
        cells[0] = {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)}; // Rotation state 0
        cells[1] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)}; // Rotation state 1
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)}; // Rotation state 2
        cells[3] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1)}; // Rotation state 3
        Move(0, 3);                                                                  // Move the block to the starting position (top center of the grid)
    }
};

class JBlock : public Block
{ // Class definition for the J-shaped block, inheriting from Block
public:
    JBlock()
    {
        id = 2;                                                                      // Unique identifier for the J-shaped block
        cells[0] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)}; // Rotation state 0
        cells[1] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)}; // Rotation state 1
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)}; // Rotation state 2
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)}; // Rotation state 3
        Move(0, 3);
    }
};

class IBlock : public Block
{ // Class definition for the I-shaped block, inheriting from Block
public:
    IBlock()
    {
        id = 3;                                                                      // Unique identifier for the I-shaped block
        cells[0] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)}; // Rotation state 0
        cells[1] = {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)}; // Rotation state 1
        cells[2] = {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)}; // Rotation state 2
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)}; // Rotation state 3
        Move(-1, 3);
    }
};

class OBlock : public Block
{ // Class definition for the O-shaped block, inheriting from Block
public:
    OBlock()
    {
        id = 4;                                                                      // Unique identifier for the O-shaped block
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)}; // Rotation state 0 (same for all states)
        Move(0, 4);
    }
};

class SBlock : public Block
{
public:
    SBlock()
    {
        id = 5;                                                                      // Unique identifier for the S-shaped block
        cells[0] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)}; // Rotation state 0
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)}; // Rotation state 1
        cells[2] = {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)}; // Rotation state 2
        cells[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)}; // Rotation state 3
        Move(0, 3);
    }
};

class TBlock : public Block
{
public:
    TBlock()
    {
        id = 6;                                                                      // Unique identifier for the T-shaped block
        cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)}; // Rotation state 0
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)}; // Rotation state 1
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)}; // Rotation state 2
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)}; // Rotation state 3
        Move(0, 3);
    }
};

class ZBlock : public Block
{
public:
    ZBlock()
    {
        id = 7;                                                                      // Unique identifier for the Z-shaped block
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)}; // Rotation state 0
        cells[1] = {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)}; // Rotation state 1
        cells[2] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)}; // Rotation state 2
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)}; // Rotation state 3
        Move(0, 3);
    }
};