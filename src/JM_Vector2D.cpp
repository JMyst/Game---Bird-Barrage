#include <iostream>
#include <vector>
#include "SDL.h"
#include "JM_Vector2D.h"

JM_Vector2D::JM_Vector2D()
{
	X = 0;
	Y = 0;
}

JM_Vector2D::JM_Vector2D(int x, int y)
{
	X = x;
	Y = y;
}

JM_Vector2D::~JM_Vector2D()
{

}