#pragma once
#include <raylib.h>
#include <vector>
// Define a Color struct to represent RGBA color values
extern const Color DarkGrey;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;
extern const Color LightBlue;
extern const Color DarkBlue;
std::vector<Color> GetCellcolors(); // Function to return a vector of colors for the Tetris grid and pieces
