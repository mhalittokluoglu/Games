#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_
#include "TetrisEngine/MathLib/TetrisMath.hpp"
#include "GLRelated/Vertex/VertexBuffer.hpp"
#include "GLRelated/Vertex/VertexArray.hpp"
#include "GLRelated/Vertex/ElementBuffer.hpp"
#include "GLRelated/Shaders/ShaderProgram.hpp"
#include <inttypes.h>
#include <array>
class RectangleRenderer;
namespace TetrisShapes
{
    struct Rectangle
    {
    public:
        Rectangle();
        ~Rectangle();
        Rectangle(TetrisMath::GLPosition position, TetrisMath::Color color);
        TetrisMath::Color Color;
        TetrisMath::GLPosition Position;
        void Initialize(ShaderProgram *shaderProgram);
        void UpdateData();
        void CopyUpdatedData();
        void Draw();
        void SetBorderData(float offsetX, float offsetY);

    private:
        void UpdateData(float X, float Y, float xoff, float yoff);
        float m_Data[12];
        VertexBuffer m_Vbo;
        VertexArray m_Vao;
        ElementBuffer m_Ebo;
        static uint32_t s_Indices[6];
        ShaderProgram *m_ShaderProgram;
    };
}
#endif