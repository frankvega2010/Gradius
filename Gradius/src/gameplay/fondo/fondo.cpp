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
		const int cantPiezasFondo = 3;
		Asteroide asteroidesFondo[cantAF];
		static int framesCounter = 0;

		struct Fondo
		{
			Texture2D sprite;
			Vector2 pos;
			float vel;
		};

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

		Fondo fondo[cantPiezasFondo];
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
			for (int i = 0; i < cantPiezasFondo; i++)
			{
				fondo[i].sprite = LoadTexture("res/assets/espacio.png");
				fondo[i].vel = 100.0f;
			}
			
			fondo[0].pos = { 0.0f,0.0f };
			fondo[1].pos = { fondo[0].pos.x + fondo[0].sprite.width,fondo[0].pos.y };
			fondo[2].pos = { fondo[1].pos.x + fondo[1].sprite.width,fondo[1].pos.y };

			for (int i = 0; i < cantAF; i++)
			{
				asteroidesFondo[i].sprite = LoadTexture("res/assets/asteroide_fondo.png");
				asteroidesFondo[i].pos.x = GetRandomValue(screenWidth / 2, screenWidth);
				asteroidesFondo[i].pos.y = GetRandomValue(0, screenHeight);
				asteroidesFondo[i].activo = true;
				asteroidesFondo[i].rotacionCuerpo = 0.0f;
				asteroidesFondo[i].vel = (float)GetRandomValue(150,200);
				asteroidesFondo[i].radio = 30;
				asteroidesFondo[i].angulo = GetRandomValue(-360, 360);
				asteroidesFondo[i].sourceRec.x = 0;
				asteroidesFondo[i].sourceRec.y = 0;
				asteroidesFondo[i].sourceRec.height = asteroidesFondo[i].sprite.height;
				asteroidesFondo[i].sourceRec.width = asteroidesFondo[i].sprite.width / 2;
			}

			inicializarLimites();

			planeta.sprite = LoadTexture("res/assets/planetas_constelaciones.png");
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

			UnloadTexture(planeta.sprite);

			for (int i = 0; i < cantPiezasFondo; i++)
			{
				UnloadTexture(fondo[i].sprite);
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

			if (fondo[0].pos.x + fondo[0].sprite.width <= 0)
			{
				fondo[0].pos.x = fondo[2].pos.x + fondo[2].sprite.width;
			}
			for (int i = 1; i < cantPiezasFondo; i++)
			{
				if (fondo[i].pos.x + fondo[i].sprite.width <= 0)
				{
					fondo[i].pos.x = fondo[i-1].pos.x + fondo[i-1].sprite.width;
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

			for (int i = 0; i < cantPiezasFondo; i++)
			{
				fondo[i].pos.x -= fondo[i].vel*GetFrameTime();
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

			for (int i = 0; i < cantAF;i++)
			{
				if (framesCounter < 500)
				{
					asteroidesFondo[i].sourceRec.x = 0;
				}
				else
				{
					asteroidesFondo[i].sourceRec.x = asteroidesFondo[0].sprite.width / 2;
				}
			}
		}

		void dibujarFondo()
		{
			for (int i = 0; i < cantPiezasFondo; i++)
			{
				DrawTexture(fondo[i].sprite, fondo[i].pos.x, fondo[i].pos.y, WHITE);
			}

			if ((planeta.numero >=6 && planeta.numero <= 8)||planeta.numero>10)
			{
				if (planeta.numero > 10)
				{
					planeta.vel = 100.0f;
				}
				else
				{
					planeta.brillo = GRAY;
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
				DrawTexturePro(asteroidesFondo[i].sprite, asteroidesFondo[i].sourceRec,
					{ asteroidesFondo[i].pos.x,asteroidesFondo[i].pos.y,(float)asteroidesFondo[i].sprite.width / 7.5f,(float)asteroidesFondo[i].sprite.height / 3.25f },
					{ (float)asteroidesFondo[i].sprite.width / 15, (float)asteroidesFondo[i].sprite.height / 7.5f }, asteroidesFondo[i].rotacionCuerpo, BROWN);
			}
		}
	}
}