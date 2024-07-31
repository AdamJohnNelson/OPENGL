#pragma once 
#include <iostream>
#include <glfw3.h>

class Controller {

public:

	struct Vec2D
	{
		float x;
		float y;
	};
	
	struct Vec3D
	{
		float x;
		float y;
		float z;
	};

	bool WKeyState = false;
	bool SKeyState = false;
	bool AKeyState = false;
	bool DKeyState = false;
	bool EKeyState = false;
	bool QKeyState = false;

	Vec2D DirectionVector = { 0.0f, 0.0f };
	Vec2D ScaleVector = { 0.0f, 0.0f };

	double CursorX = 0;
	double CursorY = 0;

	void SetDirectionVector();
	void SetScaleVector();
};
