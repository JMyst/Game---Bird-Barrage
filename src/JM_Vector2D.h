#ifndef vector2DFILE
#define vector2DFILE

#include <iostream>
#include <vector>
#include "SDL.h"

class JM_Vector2D
{
public:
	JM_Vector2D();
	~JM_Vector2D();
	JM_Vector2D(int x, int y);
	float X, Y;
};
#endif