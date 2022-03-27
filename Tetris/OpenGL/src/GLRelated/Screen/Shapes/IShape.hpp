#ifndef _SHAPES_ISHAPE_HPP_
#define _SHAPES_ISHAPE_HPP_
#include "GLRelated/MatData.hpp"
namespace Shapes
{
    class IShape
    {
    public:
        virtual void Draw() = 0;
        virtual Vect3 Color() = 0;
        virtual bool IsMoving() = 0;
        virtual void UpdateLocation() = 0;
    };
}
#endif