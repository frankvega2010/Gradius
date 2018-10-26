#ifndef ASTEROIDES_H
#define ASTEROIDES_H

#include "raylib.h"
namespace Juego
{
	namespace Gameplay
	{
		struct Asteroide
		{
			Vector2 pos;
			float radio;
			float vel;
			float angulo;
			Color color;
			bool activo;
			Texture2D sprite;
			float rotacionCuerpo;
			Rectangle sourceRec; // solo para los del fondo
		};

		extern const int cantAsteroidesG;
		extern const int cantAsteroidesM;
		extern const int cantAsteroidesP;

		void iniciarAsteroides();
		void desinicializarAsteroides();
		void moverAsteroides();
		void chequearColisionConAsteroide();
		void dibujarAsteroides();
	}
}

#endif // !ASTEROIDES_
