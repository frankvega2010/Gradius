#include "fondo.h"

#include "raylib.h"
#include "gameplay\asteroides\asteroides.h"
#include "juego.h"

namespace Juego
{
	namespace Gameplay
	{
		const int cantAF = 5;
		Asteroide asteroidesFondo[cantAF];

		void iniciarFondo()
		{
			for (int i = 0; i < cantAF; i++)
			{
				asteroidesFondo[i].sprite = LoadTexture("res/asteroide.png");
				asteroidesFondo[i].pos.x = GetRandomValue(screenWidth / 2, screenWidth);
				asteroidesFondo[i].pos.y = GetRandomValue(0, screenHeight);
			}
		}

		void desinicializarFondo()
		{
			for (int i = 0; i < cantAF; i++)
			{
				UnloadTexture(asteroidesFondo[i].sprite);
			}
		}

		void actualizarFondo()
		{

		}

		void dibujarFondo()
		{
			
		}
	}
}