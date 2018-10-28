#ifndef BOTONES_H
#define BOTONES_H

#include "raylib.h"

namespace Juego
{
	bool chequearBoton(Texture2D& boton, Texture2D botonNA,
		Texture2D botonA, int xMin, int xMax, int yMin, int yMax);

	bool chequearBoton(Texture2D& boton, int xMin, int xMax, int yMin, int yMax);
}

#endif BOTONES_H