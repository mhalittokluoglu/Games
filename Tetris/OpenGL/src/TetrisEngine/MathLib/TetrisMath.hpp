#ifndef _TETRISMATH_HPP
#define _TETRISMATH_HPP
#include <inttypes.h>

namespace TetrisMath
{
    struct Globals
    {
        static float GameWidth;
        static float BorderSizeX;
        static float BorderSizeY;
        static int32_t s_RowCount;
        static int32_t s_ColumnCount;
    };
    void SetScreenValues(float xBorderSize, float yBorderSize, 
        int32_t rowCount, int32_t columnCount, float gameWidth);

    struct GLPosition
    {
        float X;
        float Y;
        static float s_Height;
        static float s_Width;
        GLPosition();
        static void SetScreenValues(float sliceHeight, float sliceWidth);
    private:
    };

    struct IntPosition
    {
    public:
        int32_t X;
        int32_t Y;
        IntPosition();
        GLPosition ConvertToGLPosition();
        static void SetScreenValues(float xBorderSize, float yBorderSize, 
        int32_t rowCount, int32_t columnCount, float sliceHeight,
        float sliceWidth);
    private:
        static int32_t s_RowCount;
        static int32_t s_ColumnCount;
        static float s_XBorderSize;
        static float s_YBorderSize;
        static float s_SliceHeight;
        static float s_SliceWidth;
    };

    struct Color
    {
        float R;
        float G;
        float B;
        float A;
        Color();
    };

    struct Vec3
    {
        float v1;
        float v2;
        float v3;
        Vec3();
    };

}
#endif