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

		void inicializarFondo()
		{
			for (int i = 0; i < cantAF; i++)
			{
				asteroidesFondo[i].sprite = LoadTexture("res/asteroide.png");
				asteroidesFondo[i].pos.x = GetRandomValue(screenWidth / 2, screenWidth);
				asteroidesFondo[i].pos.y = GetRandomValue(0, screenHeight);
				asteroidesFondo[i].activo = true;
				asteroidesFondo[i].rotacionCuerpo = 0.0f;
				asteroidesFondo[i].vel = (float)GetRandomValue(500,600);
				asteroidesFondo[i].radio = 30;
			}
		}

		void desinicializarFondo()
		{
			for (int i = 0; i < cantAF; i++)
			{
				UnloadTexture(asteroidesFondo[i].sprite);
			}
		}

		void chequearLimite()
		{
			for (int i = 0; i < cantAF; i++)
			{
				if (asteroidesFondo[i].pos.x <= -asteroidesFondo[i].radio)
				{
					asteroidesFondo[i].pos.x = screenWidth + asteroidesFondo[i].radio;
					asteroidesFondo[i].vel = (float)GetRandomValue(500, 600);
					asteroidesFondo[i].pos.y = GetRandomValue(0, screenHeight);
				}
			}
		}

		void actualizarFondo()
		{
			chequearLimite();
			for (int i = 0; i < cantAF; i++)
			{
				asteroidesFondo[i].rotacionCuerpo -= 400 * GetFrameTime();
				asteroidesFondo[i].pos.x -= asteroidesFondo[i].vel*GetFrameTime();
			}
		}

		void dibujarFondo()
		{
			for (int i = 0; i < cantAF; i++)
			{
				DrawTexturePro(asteroidesFondo[i].sprite, { 0.0f,0.0f,(float)asteroidesFondo[i].sprite.width,(float)asteroidesFondo[i].sprite.height },
					{ asteroidesFondo[i].pos.x,asteroidesFondo[i].pos.y,(float)asteroidesFondo[i].sprite.width/15,(float)asteroidesFondo[i].sprite.height/15 },
					{ (float)asteroidesFondo[i].sprite.width / 30, (float)asteroidesFondo[i].sprite.height / 30 }, asteroidesFondo[i].rotacionCuerpo, WHITE);

			}
		}
	}
}