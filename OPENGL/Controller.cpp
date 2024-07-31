#include "Controller.h"
 
void Controller::SetDirectionVector()
{
	if (WKeyState == true && SKeyState == false && AKeyState == false && DKeyState == false)
	{
		DirectionVector = { 0.0f, 0.0005f };
	}
	else if (WKeyState == false && SKeyState == true && AKeyState == false && DKeyState == false)
	{
		DirectionVector = { 0.0f, -0.0005f };
	}
	else if (WKeyState == false && SKeyState == false && AKeyState == true && DKeyState == false)
	{
		DirectionVector = { -0.0005f, 0.0f };
	}
	else if (WKeyState == false && SKeyState == false && AKeyState == false && DKeyState == true)
	{
		DirectionVector = { 0.0005f, 0.0f };
	}
	else DirectionVector = { 0.0f, 0.0f };
}

void Controller::SetScaleVector()
{
	if (EKeyState == true)
	{
		ScaleVector = { 0.005f, 0.005f };
	}
	else if (QKeyState == true)
	{
		ScaleVector = { -0.005f, -0.005f };
	}
	else
	{
		ScaleVector = { 0.0f, 0.0f };
	}
}
