#ifndef _SHAPES_RECTANGLE_HPP_
#define _SHAPES_RECTANGLE_HPP_
#include "GLRelated/Vertex/VertexArray.hpp"
#include "GLRelated/Vertex/VertexBuffer.hpp"
#include "GLRelated/Vertex/ElementBuffer.hpp"
#include "IShape.hpp"

namespace Shapes
{
    class Rectangle : public IShape
    {
    public:
        Rectangle(ShapePosition position, ShapeSize size, Vect3 color);
        ~Rectangle();
        void Draw() override;
        Vect3 Color() override;
        bool IsMoving() override;
        void UpdateLocation() override;
        void SetBuffers();
        void SetPosition(ShapePosition position);
        void SetColor(Vect3 color);
        inline float *Data() { return m_Data; };
        inline uint32_t DataSize() { return sizeof(m_Data); }
        inline uint32_t *Indices() { return m_Indices; };
        inline uint32_t IndicesSize() { return sizeof(m_Indices); }

    private:
        Vect3 m_Color;
        ShapePosition m_Position;
        ShapeSize m_Size;
        float m_Data[12];
        uint32_t m_Indices[6];
        VertexArray m_VertexArray;
        VertexBuffer m_VertexBuffer;
        ElementBuffer m_ElementBuffer;
        bool m_IsMoving;
    };
}
#endif