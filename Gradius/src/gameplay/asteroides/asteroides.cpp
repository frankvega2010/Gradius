#include "asteroides.h"

#include <cmath>
#include "raylib.h"
#include "juego.h"
#include "gameplay/nave/nave.h"
#include "gameplay/gameplay.h"
#include "gameplay/disparos/disparos.h"

namespace Juego
{
	namespace Gameplay
	{
		const int cantAsteroidesG = 3;
		int asteroidesDestruidos = 0;
		static Asteroide asteroidesG[cantAsteroidesG];
		static Texture2D aSprite;
		static Sound aColision;

		void iniciarAsteroides()
		{
			aSprite = LoadTexture("res/assets/sprites/gameplay/asteroide enemigo.png");
#ifdef AUDIO
			aColision = LoadSound("res/assets/sonidos/colision_asteroide.wav");
#endif
			for (int i = 0; i < cantAsteroidesG; i++)
			{
				asteroidesG[i].radio = 60;

				asteroidesG[i].pos = { (float)screenWidth / asteroidesG[0].radio * 40,asteroidesG[i].radio*(i+1)*3};

				asteroidesG[i].angulo = -90.0f;

				asteroidesG[i].activo = true;

				asteroidesG[i].vel = 200.0f;

				asteroidesG[i].sprite = aSprite;

				asteroidesG[i].rotacionCuerpo = 0.0f;
			}
			asteroidesDestruidos = 0;
		}

		void desinicializarAsteroides()
		{
			UnloadTexture(aSprite);

			for (int i = 0; i < cantAsteroidesG; i++)
			{
				UnloadTexture(asteroidesG[i].sprite);
			}
#ifdef AUDIO
			UnloadSound(aColision);
#endif
		}

		void moverAsteroides()
		{
			for (int i = 0; i <cantAsteroidesG; i++)
			{
				if (asteroidesG[i].activo)
				{
					asteroidesG[i].pos.x += sinf(asteroidesG[i].angulo*DEG2RAD) * asteroidesG[i].vel * GetFrameTime();
					asteroidesG[i].pos.y -= cosf(asteroidesG[i].angulo*DEG2RAD) * asteroidesG[i].vel* GetFrameTime();

					if (asteroidesG[i].pos.x > screenWidth + asteroidesG[i].radio)
					{
						asteroidesG[i].pos.x = -asteroidesG[i].radio;
					}
					if (asteroidesG[i].pos.x < -asteroidesG[i].radio)
					{
						asteroidesG[i].pos.x = screenWidth + asteroidesG[i].radio;
					}
					if (asteroidesG[i].pos.y < -asteroidesG[i].radio)
					{
						asteroidesG[i].pos.y = screenHeight + asteroidesG[i].radio;
					}
					if (asteroidesG[i].pos.y > screenHeight + asteroidesG[i].radio)
					{
						asteroidesG[i].pos.y = -asteroidesG[i].radio;
					}

					if (asteroidesG[i].rotacionCuerpo > 0)
					{
						asteroidesG[i].rotacionCuerpo += 400 * GetFrameTime();
					}
					else
					{
						asteroidesG[i].rotacionCuerpo-= 400 * GetFrameTime();
					}
				}
			}
		}

		void chequearColisionConAsteroide()
		{
			bool colisiono=false;

			for (int i = 0; i <cantAsteroidesG; i++)
			{
				if (asteroidesG[i].activo)
				{
					if (CheckCollisionCircles({ nave.pos.x + sin(nave.rotacion*DEG2RAD),
						nave.pos.y - cos(nave.rotacion*DEG2RAD) },
						nave.radioColision, asteroidesG[i].pos, asteroidesG[i].radio))
					{
						gameOver = true;
					}


					for (int j = 0; j < cantDisparos; j++)
					{
						if (CheckCollisionCircles(disparos[j].pos, disparos[j].radio, asteroidesG[i].pos, asteroidesG[i].radio))
						{
							asteroidesG[i].activo = false;
							disparos[j].activo = false;
							colisiono = true;

							asteroidesDestruidos++;
						}
					}
				}

			}
#ifdef AUDIO
			if (colisiono && haySonido)
			{
				PlaySound(aColision);
			}
#endif
		}

		void dibujarAsteroides()
		{
			Rectangle sourceRec;
			sourceRec.height = (float)aSprite.height;
			sourceRec.width = (float)aSprite.width;
			sourceRec.x = 0.0f;
			sourceRec.y = 0.0f;

			for (int i = 0; i <cantAsteroidesG; i++)
			{
				if (asteroidesG[i].activo)
				{
					DrawTexturePro(asteroidesG[i].sprite,
									sourceRec,
									{ asteroidesG[i].pos.x,
									  asteroidesG[i].pos.y,
									  (float)asteroidesG[i].sprite.width/2, (float)asteroidesG[i].sprite.height/2 },
									{(float)asteroidesG[i].sprite.width/4,(float)asteroidesG[i].sprite.height/4},
									asteroidesG[i].rotacionCuerpo, WHITE);
					
				}
			}
		}
	}
}