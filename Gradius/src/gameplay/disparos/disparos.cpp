#include "disparos.h"

#include <cmath>
#include "raylib.h"
#include "juego.h"
#include "gameplay/nave/nave.h"

namespace Juego
{
	namespace Gameplay
	{
		static int balaADisp = 0;
		static Texture2D dSprite;

		Disparo disparos[cantDisparos];

		void inicializarDisparos()
		{
			dSprite = LoadTexture("res/assets/sprites/gameplay/disparo.png");
			for (int i = 0; i < cantDisparos; i++)
			{
				disparos[i].radio = (float)screenHeight*screenWidth/135000;
				disparos[i].activo = false;
				disparos[i].velocidad = nave.velocidad * 3 / 2;
				disparos[i].sprite = dSprite;
				disparos[i].rotacionSprite = 0.0f;
			}
		}

		void desinicializarDisparos()
		{
			UnloadTexture(dSprite);
			for (int i = 0; i < cantDisparos; i++)
			{
				UnloadTexture(disparos[i].sprite);
			}
		}

		void activarDisparos()
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				disparos[balaADisp].activo = true;
				balaADisp++;
			}
		}

		void moverDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				if (disparos[i].activo)
				{
					disparos[i].pos.x += disparos[i].velocidad*GetFrameTime();
					if (disparos[i].pos.x > screenWidth)
					{
						disparos[i].activo = false;
					}
				}
			}
		}

		void actualizarDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				if (!disparos[i].activo)
				{
					disparos[i].pos = nave.pos;
				}
				
				disparos[i].rotacionSprite += 400.0f*GetFrameTime();
			}

			if (balaADisp == cantDisparos - 1) //reinicia los disparos
			{
				balaADisp = 0;
			}	
		}

		void dibujarDisparos()
		{
			for (int i = 0; i < cantDisparos; i++)
			{
				if (disparos[i].activo)
				{
					DrawTexturePro(disparos[i].sprite,
						{0.0f,0.0f, (float)disparos[i].sprite.width, (float)disparos[i].sprite.height },
						{ disparos[i].pos.x,disparos[i].pos.y,(float)disparos[i].sprite.width,(float)disparos[i].sprite.height },
						{ (float)disparos[i].sprite.width / 2,(float)disparos[i].sprite.height / 2 }, disparos[i].rotacionSprite,
						WHITE);
				}
			}
		}
	}
}