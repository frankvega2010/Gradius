#include "enemigo.h"

#include <cmath>
#include "juego.h"
#include "gameplay/nave/nave.h"
#include "gameplay/gameplay.h"
#include "gameplay/disparos/disparos.h"

namespace Juego
{
	namespace Gameplay
	{
		enemigo enemigoAntiAereo;

		static Texture2D aSprite;

		void iniciarEnemigos()
		{
			aSprite = LoadTexture("res/assets/sprites/gameplay/asteroide enemigo.png");

			enemigoAntiAereo.size = {50,50};
			enemigoAntiAereo.pos = { screenWidth - enemigoAntiAereo.size.x,screenHeight - enemigoAntiAereo.size.y };
			enemigoAntiAereo.sprite = aSprite;
			enemigoAntiAereo.vel = 200.0f;
			enemigoAntiAereo.activo = false;
		}

		void desinicializarEnemigos()
		{

//#ifdef AUDIO
//			UnloadSound(aColision);
//#endif
		}

		void moverEnemigos()
		{
			enemigoAntiAereo.pos.x -= enemigoAntiAereo.vel*GetFrameTime();

			if (enemigoAntiAereo.pos.x < 0 - enemigoAntiAereo.size.x * 2) enemigoAntiAereo.pos.x = screenWidth + enemigoAntiAereo.size.x;
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


				for (int j = 0; j < cantDisparos; j++)
				{
					if (CheckCollisionCircleRec(disparos[j].pos, disparos[j].radio, { enemigoAntiAereo.pos.x, enemigoAntiAereo.pos.y,enemigoAntiAereo.size.x,enemigoAntiAereo.size.y }))
					{
						enemigoAntiAereo.activo = false;
						disparos[j].activo = false;
						colisiono = true;

						//asteroidesDestruidos++;
					}
				}

				for (int k = 0; k < cantMisiles; k++)
				{
					if (CheckCollisionCircleRec(mortero[k].pos, mortero[k].radio, { enemigoAntiAereo.pos.x, enemigoAntiAereo.pos.y,enemigoAntiAereo.size.x,enemigoAntiAereo.size.y }))
					{
						enemigoAntiAereo.activo = false;
						mortero[k].activo = false;
						colisiono = true;

						//asteroidesDestruidos++;
					}
				}
			}

			if (!enemigoAntiAereo.activo)
			{
				enemigoAntiAereo.activo = true;
				enemigoAntiAereo.pos.x = screenWidth + enemigoAntiAereo.size.x;
			}
//#ifdef AUDIO
//			if (colisiono && haySonido)
//			{
//				PlaySound(aColision);
//			}
//#endif
		}

		void dibujarEnemigos()
		{
			DrawRectangleRec({ enemigoAntiAereo.pos.x,enemigoAntiAereo.pos.y,enemigoAntiAereo.size.x,enemigoAntiAereo.size.y }, WHITE);
		}
	}
}