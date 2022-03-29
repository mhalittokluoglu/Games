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
    std::array<float, 12> m_Data;
    VertexBuffer m_Vbo;
    VertexArray m_Vao;
    ElementBuffer m_Ebo;
    static std::array<uint32_t, 6> s_Indices;
    ShaderProgram *m_ShaderProgram;

};
#endif