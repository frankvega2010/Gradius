#include "botones.h"

#include "raylib.h"

namespace Juego
{
	bool ubicarBoton(Texture2D& boton, Texture2D botonNA,Texture2D botonA, int xMin, int xMax, int yMin, int yMax)
	{
		if (GetMouseX() >= xMin && GetMouseX() <= xMax && GetMouseY() >= yMin && GetMouseY() <= yMax)
		{
			boton = botonA;
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				return true;
			}
		}
		else
		{
			boton = botonNA;
		}
		return false;
	}
}