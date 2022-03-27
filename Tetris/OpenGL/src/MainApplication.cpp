#include "GLRelated/Screen/Screen.hpp"
#include "Logger.hpp"
#include "GLRelated/Screen/Shapes/Rectangle.hpp"

int main()
{
    Logger::InitLogger("127.0.0.1", 30000);
    ShapePosition recPos;
    recPos.X = -0.2f;
    recPos.Y = 0.6f;

    ShapeSize recSize;
    recSize.Width = 0.05f; 
    recSize.Height = 0.1f;

    Vect3 recColor;
    recColor.v1 = 0.0f; 
    recColor.v2 = 1.0f; 
    recColor.v3 = 0.0f; 

    Screen screen(800, 600);
    
    Shapes::Rectangle *rectangle = new Shapes::Rectangle(recPos, recSize, recColor);
    recPos.X = 0.3;
    recPos.Y = 1.0;
    recColor.v1 = 0.3;
    recColor.v2 = 0.6;
    recColor.v3 = 0.9;
    Shapes::Rectangle *rectangle2 = new Shapes::Rectangle(recPos, recSize, recColor);

    rectangle->SetBuffers();
    rectangle2->SetBuffers();
    screen.AddShape(rectangle);
    screen.AddShape(rectangle2);
    screen.ProcessScreen();
}