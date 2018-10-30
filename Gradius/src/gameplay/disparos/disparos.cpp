#include "disparos.h"

#include "raylib.h"
#include "juego.h"
#include "gameplay/nave/nave.h"

namespace Juego
{
	namespace Gameplay
	{
		static int balaADisp = 0;
		static int misilADisp = 0;
		//static int speedDe
		static Texture2D dSprite;

		Disparo disparos[cantDisparos];
		Disparo mortero[cantMisiles];

		void inicializarDisparos()
		{
			dSprite = LoadTexture("res/assets/sprites/gameplay/disparo.png");

			for (int i = 0; i < cantDisparos; i++)
			{
				disparos[i].radio = (float)screenHeight*screenWidth/135000;
				disparos[i].activo = false;
				disparos[i].velocidad = nave.velocidad * 3 / 2;
				disparos[i].velocidadY = 0;
				disparos[i].sprite = dSprite;
				disparos[i].rotacionSprite = 0.0f;
			}

			for (int i = 0; i < cantMisiles; i++)
			{
				mortero[i].radio = (float)screenHeight*screenWidth / 135000;
				mortero[i].activo = false;
				mortero[i].velocidad = nave.velocidad * 1.5f;// / 2;
				mortero[i].velocidadY = nave.velocidad * 1.2f;// / 2;
				mortero[i].sprite = dSprite;
				mortero[i].rotacionSprite = 0.0f;
			}
		}

		void desinicializarDisparos()
		{
			UnloadTexture(dSprite);
			for (int i = 0; i < cantDisparos; i++) UnloadTexture(disparos[i].sprite);

			for (int i = 0; i < cantMisiles; i++) UnloadTexture(mortero[i].sprite);
		}

		void activarDisparos()
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				disparos[balaADisp].activo = true;
				balaADisp++;
			}

			if (IsKeyPressed(KEY_F))
			{
				mortero[misilADisp].activo = true;
				misilADisp++;
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

			for (int i = 0; i < cantMisiles; i++)
			{
				if (mortero[i].activo)
				{
					//if (mortero[i].pos.x >= mortero[i].pos.x + 5) mortero[i].pos.x += 0;
					if (mortero[i].velocidad <= 0) mortero[i].velocidad = 0;
					else mortero[i].velocidad--;
					//else if (mortero[i].pos.x >= nave.pos.x + 100) mortero[i].pos.x += 0;
					mortero[i].pos.x += mortero[i].velocidad*GetFrameTime();

					//if (mortero[i].pos.x <= nave.pos.x - 50) mortero[i].pos.x += 0;

					mortero[i].pos.y += mortero[i].velocidadY*GetFrameTime();
					if (mortero[i].pos.y > screenHeight)
					{
						mortero[i].activo = false;
						mortero[i].velocidad = nave.velocidad * 1.5f;
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

			for (int i = 0; i < cantMisiles; i++)
			{
				if (!mortero[i].activo)
				{
					mortero[i].pos = nave.pos;
				}

				mortero[i].rotacionSprite += 400.0f*GetFrameTime();
			}

			if (misilADisp == cantMisiles - 1) //reinicia los disparos
			{
				misilADisp = 0;
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

			for (int i = 0; i < cantMisiles; i++)
			{
				if (mortero[i].activo)
				{
					DrawTexturePro(mortero[i].sprite,
						{ 0.0f,0.0f, (float)mortero[i].sprite.width, (float)mortero[i].sprite.height },
						{ mortero[i].pos.x,mortero[i].pos.y,(float)mortero[i].sprite.width,(float)mortero[i].sprite.height },
						{ (float)mortero[i].sprite.width / 2,(float)mortero[i].sprite.height / 2 }, mortero[i].rotacionSprite,
						WHITE);
				}
			}
		}
	}
}