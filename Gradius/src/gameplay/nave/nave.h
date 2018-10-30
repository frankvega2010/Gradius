#ifndef NAVE_H
#define NAVE_H

#include "raylib.h"

namespace Juego
{
	namespace Gameplay
	{
		struct Nave
		{
			float rotacion;
			Vector2 colision;
			int radioColision;
			float altura;
			float base;
			Vector2 pos;
			Texture2D sprite;
			float velocidad;
			bool detenida;
		};

		extern Nave nave;

		void iniciarNave();
		void moverNave();
		void chequearColisionConBordes();
		void dibujarNave();
	}
}

#endif // !NAVE_H
