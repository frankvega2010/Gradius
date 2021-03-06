#include "disparos.h"

#include "raylib.h"
#include "juego.h"
#include "gameplay/nave/nave.h"
#include "gameplay/enemigo/enemigo.h"

namespace Juego
{
	namespace Gameplay
	{
		
		static int balaADisp = 0;
		static int misilADisp = 0;
		static bool updateLocation = true;
		static bool activarSonidoDisparo = false;
		static Texture2D dSprite;

		Disparo disparos[cantDisparos];
		Disparo mortero[cantMisiles];

		Disparo misilesEnemigos[cantMisilesEnemigos];

		static Sound shoot01;
		static Sound shoot02;
		static Sound shoot03;

		void inicializarDisparos()
		{
			updateLocation = true;
			dSprite = LoadTexture("res/assets/sprites/gameplay/disparo.png");

			shoot01 = LoadSound("res/assets/sonidos/shoot01.wav");
			shoot02 = LoadSound("res/assets/sonidos/shoot02.wav");
			shoot03 = LoadSound("res/assets/sonidos/shoot03.wav");

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
				mortero[i].velocidad = nave.velocidad * 1.5f;
				mortero[i].velocidadY = nave.velocidad * 1.2f;
				mortero[i].sprite = dSprite;
				mortero[i].rotacionSprite = 0.0f;
			}

			misilesEnemigos[0].pos = { enemigoAntiAereo.pos.x,enemigoAntiAereo.pos.y};
			misilesEnemigos[0].radio = (float)screenHeight*screenWidth / 165000;
			misilesEnemigos[0].activo = false;
			misilesEnemigos[0].velocidad = nave.velocidad * 2 / 2;
			misilesEnemigos[0].velocidadY = nave.velocidad * 2 / 2;
			misilesEnemigos[0].sprite = dSprite;
			misilesEnemigos[0].rotacionSprite = 0.0f;
		}

		void desinicializarDisparos()
		{
			UnloadTexture(dSprite);

			for (int i = 0; i < cantDisparos; i++) UnloadTexture(disparos[i].sprite);
			for (int i = 0; i < cantMisiles; i++) UnloadTexture(mortero[i].sprite);

			UnloadSound(shoot01);
			UnloadSound(shoot02);
			UnloadSound(shoot03);
		}

		void activarDisparos()
		{
			if (IsKeyPressed(KEY_F))
			{
				if (!disparos[balaADisp].activo)
				{
					PlaySound(shoot01);
					disparos[balaADisp].activo = true;
				}
				balaADisp++;
			}

			if (IsKeyPressed(KEY_SPACE))
			{
				if (!mortero[misilADisp].activo)
				{
					PlaySound(shoot02);
					mortero[misilADisp].activo = true;
				}
				misilADisp++;
			}

			if (enemigoAntiAereo.pos.x >= screenWidth / 1.5f) 
			{
				misilesEnemigos[0].activo = true;
			} 

			if (!activarSonidoDisparo) 
			{
				activarSonidoDisparo = true;
				PlaySound(shoot03);
			}
		}

		void moverDisparos()
		{
			if (misilesEnemigos[0].activo)
			{
				if (updateLocation)
				{
					misilesEnemigos[0].pos = { enemigoAntiAereo.pos.x,enemigoAntiAereo.pos.y };
					updateLocation = false;	
					activarSonidoDisparo = false;
				}
				misilesEnemigos[0].pos.x -= misilesEnemigos[0].velocidad*GetFrameTime();
				misilesEnemigos[0].pos.y -= misilesEnemigos[0].velocidadY*GetFrameTime();
				if ((misilesEnemigos[0].pos.y < 0 - misilesEnemigos[0].radio|| misilesEnemigos[0].pos.x < 0 - misilesEnemigos[0].radio ) && enemigoAntiAereo.pos.x <= screenWidth / 1.5f)
				{
					misilesEnemigos[0].activo = false;
					updateLocation = true;
				}
			}

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
					if (mortero[i].velocidad <= 0) mortero[i].velocidad = 0;
					else if (mortero[i].velocidad >= 1 && mortero[i].pos.x >= nave.pos.x + 100) mortero[i].velocidad = mortero[i].velocidad - 0.5f;

					if (mortero[i].pos.x >= nave.pos.x + 50) mortero[i].velocidadY = nave.velocidad * 2 / 2;

					if (mortero[i].pos.y >= screenHeight - disparos[0].radio)
					{
						mortero[i].velocidad = nave.velocidad * 1.5f;
						mortero[i].velocidadY = 0;
					}

					mortero[i].pos.y += mortero[i].velocidadY*GetFrameTime();
					mortero[i].pos.x += mortero[i].velocidad*GetFrameTime();
					
					if (mortero[i].pos.y > screenHeight || mortero[i].pos.x > screenWidth)
					{
						mortero[i].activo = false;
						mortero[i].velocidad = nave.velocidad * 1.5f;
						mortero[i].velocidadY = nave.velocidad * 1.2f;
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

			if (misilADisp == cantMisiles - 1) //reinicia los misiles
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

			if (misilesEnemigos[0].activo)
			{
				DrawTexturePro(misilesEnemigos[0].sprite,
					{ 0.0f,0.0f, (float)misilesEnemigos[0].sprite.width, (float)misilesEnemigos[0].sprite.height },
					{ misilesEnemigos[0].pos.x,misilesEnemigos[0].pos.y,(float)misilesEnemigos[0].sprite.width,(float)misilesEnemigos[0].sprite.height },
					{ (float)misilesEnemigos[0].sprite.width / 2,(float)misilesEnemigos[0].sprite.height / 2 }, mortero[0].rotacionSprite,
					GOLD);
			}
		}
	}
}