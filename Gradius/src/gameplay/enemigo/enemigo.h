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
			//float radio;
			float vel;
			//float angulo;
			bool activo;
			Texture2D sprite;
			//float rotacionCuerpo;
			//Rectangle sourceRec; // solo para los del fondo
		};

		extern enemigo enemigoAntiAereo;

		//extern const int cantAsteroidesG;
		//extern int asteroidesDestruidos;

		void iniciarEnemigos();
		void desinicializarEnemigos();
		void moverEnemigos();
		void chequearColisionConEnemigos();
		void dibujarEnemigos();
	}
}

#endif // ENEMIGO_H
