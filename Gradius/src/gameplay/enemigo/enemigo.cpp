#include "enemigo.h"

#include <cmath>
#include "juego.h"
#include "gameplay/nave/nave.h"
#include "gameplay/gameplay.h"
#include "gameplay/disparos/disparos.h"
#include "gameplay/asteroides/asteroides.h"

namespace Juego
{
	namespace Gameplay
	{
		enemigo enemigoAntiAereo;

		static Texture2D aSprite;

		void iniciarEnemigos()
		{
			aSprite = LoadTexture("res/assets/sprites/gameplay/cannon01.png");

			enemigoAntiAereo.size = {50,50};
			enemigoAntiAereo.pos.x = GetRandomValue((0 - enemigoAntiAereo.size.x), ((-((float)screenWidth*1.8f)) - enemigoAntiAereo.size.x));
			enemigoAntiAereo.pos.y = screenHeight - enemigoAntiAereo.size.y;
			enemigoAntiAereo.sprite = aSprite;
			enemigoAntiAereo.vel = GetRandomValue(250.0f, 350.0f);
			enemigoAntiAereo.activo = false;
		}

		void desinicializarEnemigos()
		{
			UnloadTexture(aSprite);
		}

		void moverEnemigos()
		{
			enemigoAntiAereo.pos.x += enemigoAntiAereo.vel*GetFrameTime();
			if (enemigoAntiAereo.pos.x > screenWidth + enemigoAntiAereo.size.x * 2)
			{
				enemigoAntiAereo.vel = GetRandomValue(250.0f, 350.0f);
				enemigoAntiAereo.pos.x = GetRandomValue((0 - enemigoAntiAereo.size.x), ((-((float)screenWidth*1.8f)) - enemigoAntiAereo.size.x));
			}
		}

		void chequearColisionConEnemigos()
		{
			bool colisiono = false;

			if (enemigoAntiAereo.activo)
			{
				if (CheckCollisionCircleRec({ nave.pos.x + sin(nave.rotacion*DEG2RAD),
					nave.pos.y - cos(nave.rotacion*DEG2RAD) },
					nave.radioColision, { enemigoAntiAereo.pos.x, enemigoAntiAereo.pos.y,enemigoAntiAereo.size.x,enemigoAntiAereo.size.y }))
				{
					gameOver = true;
				}

				if (misilesEnemigos[0].activo)
				{
					if (CheckCollisionCircles({ nave.pos.x + sin(nave.rotacion*DEG2RAD),
						nave.pos.y - cos(nave.rotacion*DEG2RAD) },
						nave.radioColision, misilesEnemigos[0].pos, misilesEnemigos[0].radio))
					{
						gameOver = true;
					}
				}


				for (int j = 0; j < cantDisparos; j++)
				{
					if (CheckCollisionCircleRec(disparos[j].pos, disparos[j].radio, { enemigoAntiAereo.pos.x, enemigoAntiAereo.pos.y,enemigoAntiAereo.size.x,enemigoAntiAereo.size.y }))
					{
						enemigoAntiAereo.activo = false;
						disparos[j].activo = false;
						colisiono = true;

						cantEnemiesTarget--;
					}
				}

				for (int k = 0; k < cantMisiles; k++)
				{
					if (CheckCollisionCircleRec(mortero[k].pos, mortero[k].radio, { enemigoAntiAereo.pos.x, enemigoAntiAereo.pos.y,enemigoAntiAereo.size.x,enemigoAntiAereo.size.y }))
					{
						enemigoAntiAereo.activo = false;
						mortero[k].activo = false;
						mortero[k].velocidad = nave.velocidad * 1.5f;
						mortero[k].velocidadY = nave.velocidad * 1.2f;
						colisiono = true;

						cantEnemiesTarget--;
					}
				}
			}

			if (!enemigoAntiAereo.activo)
			{
				enemigoAntiAereo.activo = true;
				enemigoAntiAereo.pos.x = GetRandomValue((0 - enemigoAntiAereo.size.x), ((-((float)screenWidth*1.8f)) - enemigoAntiAereo.size.x));
				enemigoAntiAereo.vel = GetRandomValue(250.0f, 350.0f);
			}
#ifdef AUDIO
			if (colisiono && haySonido)
			{
				PlaySound(aColision);
			}
#endif
		}

		void dibujarEnemigos()
		{
			Rectangle sourceRec;
			sourceRec.height = (float)aSprite.height;
			sourceRec.width = (float)aSprite.width;
			sourceRec.x = 0.0f;
			sourceRec.y = 0.0f;

			if (enemigoAntiAereo.activo)
			{
				DrawTexturePro(enemigoAntiAereo.sprite,
					sourceRec,
					{ enemigoAntiAereo.pos.x,
					enemigoAntiAereo.pos.y,
					90, 90 },
					{ 20,40 },
					0, WHITE);

			}
				
		}
	}
}