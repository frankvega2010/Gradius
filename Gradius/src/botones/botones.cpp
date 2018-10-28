#include "botones.h"

#include "raylib.h"
#include "juego.h"

namespace Juego
{
	void ubicarBoton(Texture2D boton, Texture2D botonNA,Texture2D botonA, int xMin, int xMax, int yMin, int yMax, Estado estadoACambiar)
	{
		bool toco = false;
		if (GetMouseX() >= xMin && GetMouseX() <= xMax && GetMouseY() >= yMin && GetMouseY() <= yMax)
		{
			boton = botonA;
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				estado = estadoACambiar;
			}
		}
		else
		{
			boton = botonNA;
		}
	}
}