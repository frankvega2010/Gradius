#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "raylib.h"
namespace Juego
{
	namespace Gameplay
	{
		struct enemigo
		{
			Vector2 pos;
			Vector2 size;
			float vel;
			bool activo;
			Texture2D sprite;
		};

		extern enemigo enemigoAntiAereo;

		void iniciarEnemigos();
		void desinicializarEnemigos();
		void moverEnemigos();
		void chequearColisionConEnemigos();
		void dibujarEnemigos();
	}
}

#endif // ENEMIGO_H
