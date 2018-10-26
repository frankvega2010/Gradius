#include "fondo.h"

#include <cmath>
#include "raylib.h"
#include "gameplay\asteroides\asteroides.h"
#include "juego.h"
#include "gameplay/gameplay.h"

namespace Juego
{
	namespace Gameplay
	{
		float limitesAsteroidesFondo[4];
		const int cantAF = 5;
		const int cantEstrellas = 50;
		Asteroide asteroidesFondo[cantAF];
		static Rectangle sourceRec;
		static int framesCounter = 0;

		struct Planeta
		{
			bool activo;
			Rectangle sourceRec;
			Texture2D sprite;
			Vector2 pos;
			float vel;
			int numero;
			Color brillo;
		};

		struct Estrella
		{
			Vector2 pos;
			float vel;
		};

		Estrella estrellas[cantEstrellas];
		Planeta planeta;

		void inicializarLimites()
		{
			limitesAsteroidesFondo[arriba] = -asteroidesFondo[0].radio;
			limitesAsteroidesFondo[abajo] = screenHeight + asteroidesFondo[0].radio;
			limitesAsteroidesFondo[derecha] = screenWidth + asteroidesFondo[0].radio;
			limitesAsteroidesFondo[izquierda] = -asteroidesFondo[0].radio;
		}

		void inicializarFondo()
		{
			for (int i = 0; i < cantAF; i++)
			{
				asteroidesFondo[i].sprite = LoadTexture("res/asteroide fondo.png");
				asteroidesFondo[i].pos.x = GetRandomValue(screenWidth / 2, screenWidth);
				asteroidesFondo[i].pos.y = GetRandomValue(0, screenHeight);
				asteroidesFondo[i].activo = true;
				asteroidesFondo[i].rotacionCuerpo = 0.0f;
				asteroidesFondo[i].vel = (float)GetRandomValue(150,200);
				asteroidesFondo[i].radio = 30;
				asteroidesFondo[i].angulo = GetRandomValue(-360, 360);
			}

			sourceRec.x = 0;
			sourceRec.y = 0;
			sourceRec.height = asteroidesFondo[0].sprite.height;
			sourceRec.width = asteroidesFondo[0].sprite.width / 2;

			inicializarLimites();

			for (int i = 0; i < cantEstrellas; i++)
			{
				estrellas[i].pos.x = GetRandomValue(0, screenWidth);
				estrellas[i].pos.y = GetRandomValue(0, screenHeight);
				estrellas[i].vel = 100.0f;
			}

			planeta.sprite = LoadTexture("res/planetas_constelaciones.png");
			planeta.vel = 80.0f;
			planeta.sourceRec.x = 0;
			planeta.sourceRec.y = 0;
			planeta.sourceRec.height = planeta.sprite.height;
			planeta.sourceRec.width = planeta.sprite.width / 8;
			planeta.pos = { (float)screenWidth + planeta.sprite.width / 8,
							(float)GetRandomValue(planeta.sprite.height,screenHeight - planeta.sprite.height) };
			planeta.activo = false;
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
			bool tocoLimite = false;
			for (int i = 0; i < cantAF; i++)
			{
				if (asteroidesFondo[i].pos.x <= limitesAsteroidesFondo[izquierda])
				{
					asteroidesFondo[i].pos.x = limitesAsteroidesFondo[derecha];
					asteroidesFondo[i].pos.y = GetRandomValue(0, screenHeight);
					tocoLimite = true;
				}
				if (asteroidesFondo[i].pos.x >= limitesAsteroidesFondo[derecha])
				{
					asteroidesFondo[i].pos.x = limitesAsteroidesFondo[izquierda];
					asteroidesFondo[i].pos.y = GetRandomValue(0, screenHeight);
					tocoLimite = true;
				}
				if (asteroidesFondo[i].pos.y <= limitesAsteroidesFondo[arriba])
				{
					asteroidesFondo[i].pos.y = limitesAsteroidesFondo[abajo];
					asteroidesFondo[i].pos.x = GetRandomValue(0, screenHeight);
					tocoLimite = true;
				}
				if (asteroidesFondo[i].pos.y >= limitesAsteroidesFondo[abajo])
				{
					asteroidesFondo[i].pos.y = limitesAsteroidesFondo[arriba];
					asteroidesFondo[i].pos.x = GetRandomValue(0, screenHeight);
					tocoLimite = true;
				}

				if (tocoLimite)
				{
					asteroidesFondo[i].angulo = GetRandomValue(-360, 360);
					asteroidesFondo[i].vel = (float)GetRandomValue(150, 200);
					tocoLimite = false;
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
				asteroidesFondo[i].pos.x += sin(asteroidesFondo[i].angulo*DEG2RAD)*asteroidesFondo[i].vel*GetFrameTime();
				asteroidesFondo[i].pos.y -= cos(asteroidesFondo[i].angulo*DEG2RAD)*asteroidesFondo[i].vel*GetFrameTime();
			}

			framesCounter++;

			if (!planeta.activo)
			{
				planeta.numero = GetRandomValue(0, 100);
			}

			if (planeta.numero <= 20)
			{
				planeta.activo = true;
				if (planeta.numero <= 3)
				{
					planeta.sourceRec.x = 0;
				}
				else if (planeta.numero <= 5)
				{
					planeta.sourceRec.x = planeta.sprite.width / 8;
				}
				else if (planeta.numero <= 8)
				{
					planeta.sourceRec.x = planeta.sprite.width / 8*2;
				}
				else if (planeta.numero<=10)
				{
					planeta.sourceRec.x = planeta.sprite.width / 8*3;
				}
				else if (planeta.numero <= 13)
				{
					planeta.sourceRec.x = planeta.sprite.width / 8 * 4;
				}
				else if (planeta.numero <= 15)
				{
					planeta.sourceRec.x = planeta.sprite.width / 8 * 5;
				}
				else if (planeta.numero <= 18)
				{
					planeta.sourceRec.x = planeta.sprite.width / 8 * 6;
				}
				else
				{
					planeta.sourceRec.x = planeta.sprite.width / 8 * 7;
				}
			}

			if (planeta.activo)
			{
				planeta.pos.x -= planeta.vel*GetFrameTime();
			}

			if (planeta.pos.x < -planeta.sprite.width / 8)
			{
				planeta.pos.x = screenWidth + planeta.sprite.width / 8;
				planeta.pos.y = GetRandomValue(planeta.sprite.height, screenHeight - planeta.sprite.height);
				planeta.activo = false;
			}

			if (framesCounter > 1000)
			{
				framesCounter = 0;
			}

			if (framesCounter < 500)
			{
				sourceRec.x = 0;
			}
			else
			{
				sourceRec.x = asteroidesFondo[0].sprite.width / 2;
			}
			

			for (int i = 0; i < cantEstrellas; i++)
			{
				estrellas[i].pos.x -= estrellas[i].vel*GetFrameTime();
			}
		}

		void dibujarFondo()
		{
			
			for (int i = 0; i < cantEstrellas; i++)
			{
				DrawPixel(estrellas[i].pos.x, estrellas[i].pos.y, WHITE);
			}

			if ((planeta.numero >=6 && planeta.numero <= 8)||planeta.numero>10)
			{
				planeta.brillo = GRAY;
				if (planeta.numero > 10)
				{
					planeta.vel = 100.0f;
				}
				else
				{
					planeta.vel = 80.0f;
				}
			}
			else
			{
				planeta.brillo = WHITE;
				planeta.vel = 80.0f;
			}

			if (planeta.activo)
			{
				DrawTexturePro(planeta.sprite, planeta.sourceRec,
					{ planeta.pos.x,planeta.pos.y,(float)planeta.sprite.width / 8,(float)planeta.sprite.height }, 
					{ (float)planeta.sprite.width / 16,(float)planeta.sprite.height }, 0, planeta.brillo);
			}

			for (int i = 0; i < cantAF; i++)
			{
				DrawTexturePro(asteroidesFondo[i].sprite, sourceRec,
					{ asteroidesFondo[i].pos.x,asteroidesFondo[i].pos.y,(float)asteroidesFondo[i].sprite.width / 7.5f,(float)asteroidesFondo[i].sprite.height / 3.25f },
					{ (float)asteroidesFondo[i].sprite.width / 15, (float)asteroidesFondo[i].sprite.height / 7.5f }, asteroidesFondo[i].rotacionCuerpo, BROWN);
			}
		}
	}
}