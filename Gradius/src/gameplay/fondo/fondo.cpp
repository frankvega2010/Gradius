#include "fondo.h"

#include "raylib.h"
#include "gameplay\asteroides\asteroides.h"
#include "juego.h"

namespace Juego
{
	namespace Gameplay
	{
		const int cantAF = 5;
		const int cantEstrellas = 50;
		Asteroide asteroidesFondo[cantAF];

		struct Estrella
		{
			Vector2 pos;
			float vel;
		};

		Estrella estrellas[cantEstrellas];

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

			for (int i = 0; i < cantEstrellas; i++)
			{
				estrellas[i].pos.x = GetRandomValue(0, screenWidth);
				estrellas[i].pos.y = GetRandomValue(0, screenHeight);
				estrellas[i].vel = 40.0f;
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

			for (int i = 0; i < cantEstrellas; i++)
			{
				if (estrellas[i].pos.x < 0)
				{
					estrellas[i].pos.x = screenWidth + 30;
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
			for (int i = 0; i < cantEstrellas; i++)
			{
				estrellas[i].pos.x -= estrellas[i].vel*GetFrameTime();
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

			for (int i = 0; i < cantEstrellas; i++)
			{
				DrawPixel(estrellas[i].pos.x, estrellas[i].pos.y, WHITE);
			}
		}
	}
}