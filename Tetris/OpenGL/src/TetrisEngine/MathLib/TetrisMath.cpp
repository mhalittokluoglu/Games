#include "TetrisMath.hpp"

using namespace TetrisMath;


float Globals::GameWidth = 0.0f;
float Globals::BorderSizeX = 0.0f;
float Globals::BorderSizeY = 0.0f;
int32_t Globals::s_RowCount = 0;
int32_t Globals::s_ColumnCount = 0;

float GLPosition::s_Height  = 0.0f;
float GLPosition::s_Width   = 0.0f;

int32_t IntPosition::s_RowCount     = 0;
int32_t IntPosition::s_ColumnCount  = 0;
float IntPosition::s_XBorderSize    = 0.0f;
float IntPosition::s_YBorderSize    = 0.0f;
float IntPosition::s_SliceHeight    = 0.0f;
float IntPosition::s_SliceWidth     = 0.0f;

void TetrisMath::SetScreenValues(float xBorderSize, float yBorderSize, 
                        int32_t rowCount, int32_t columnCount, float gameWidth)
{
    Globals::GameWidth = gameWidth;
    Globals::BorderSizeX = xBorderSize;
    Globals::BorderSizeY = yBorderSize;
    Globals::s_RowCount = rowCount;
    Globals::s_ColumnCount = columnCount;
    float sliceHeight   = 2.0f / rowCount;
    float sliceWidth    = gameWidth / columnCount;

    IntPosition::SetScreenValues(xBorderSize, yBorderSize, 
                                    rowCount, columnCount, sliceHeight,
                                    sliceWidth);

    GLPosition::SetScreenValues(sliceHeight, sliceWidth);
}

GLPosition::GLPosition()
{
    X = 0.0f;
    Y = 0.0f;
}

void GLPosition::SetScreenValues(float sliceHeight, float sliceWidth)
{
    s_Height = sliceHeight;
    s_Width = sliceWidth;
}

IntPosition::IntPosition()
{
    X = 0;
    Y = 0;
}

void IntPosition::SetScreenValues(float xBorderSize, float yBorderSize, 
                                    int32_t rowCount, int32_t columnCount, float sliceHeight,
                                    float sliceWidth)
{
    s_XBorderSize   = xBorderSize;
    s_YBorderSize   = yBorderSize;
    s_RowCount      = rowCount;
    s_ColumnCount   = columnCount;
    s_SliceHeight   = sliceHeight;
    s_SliceWidth    = sliceWidth;
}

GLPosition IntPosition::ConvertToGLPosition()
{
    GLPosition pos;
    pos.X = s_XBorderSize + s_SliceWidth * X - 1.0f;
    pos.Y = s_YBorderSize + s_SliceHeight * (s_RowCount - Y - 1) - 1.0f;
    return pos;
}

Color::Color()
{
    R = 0.0f;
    G = 0.0f;
    B = 0.0f;
    A = 1.0f;
}

Vec3::Vec3()
{
    v1 = 0.0f;
    v2 = 0.0f;
    v3 = 0.0f;
}