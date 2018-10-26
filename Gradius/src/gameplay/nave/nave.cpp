#include "nave.h"

#include <cmath>
#include "raylib.h"
#include "juego.h"
#include "gameplay/gameplay.h"
#include "gameplay/pausa/pausa.h"

namespace Juego
{
	namespace Gameplay
	{		
			enum movNave
			{
				siArriba,
				siAbajo,
				quieta
			};
			Nave nave;

			static int framesCounter;

			Vector2 vDireccion;  //vector que va de la nave a la pos del mouse, sirve para calcular la rotacion
			Vector2 vNormalizador;

			static Rectangle sourceRec;

			static void actualizarSpriteNave();

			void establecerSR()
			{
				framesCounter = 0;
				sourceRec.x = 0;
				sourceRec.y = 0;
				sourceRec.width = nave.sprite.width/5;
				sourceRec.height = nave.sprite.height;
			}

			void iniciarNave()
			{
				nave.base = screenWidth/30;
				nave.altura = (nave.base / 2) / tanf(25 * DEG2RAD);
				nave.rotacion = 0;
				nave.pos = { (float)screenWidth / nave.altura*3,(float)screenHeight / 2 };
				nave.colision = { nave.pos.x + sin(nave.rotacion*DEG2RAD),
					nave.pos.y - cos(nave.rotacion*DEG2RAD) };
				nave.radioColision = nave.altura * 2 / 3 + 10;
				nave.sprite = LoadTexture("res/assets/nave (2).png");
				nave.velocidad = (float)screenWidth/3;
				nave.aceleracionBase = { 0.8f };
				nave.aceleracion = { 0.0f,0.0f };
				nave.anguloAceler = 0.0f;
				nave.detenida = true;
				nave.puntaje = 0;
				establecerSR();
			}

			

			void moverNave()
			{
				//calcularAnguloRotacion();
				//normalizarDireccion();

				movNave seMovio = quieta;
				
				if (!pausa)
				{
					if(IsKeyDown(KEY_UP))
					{
						seMovio = siArriba;
						nave.pos.y-=500*GetFrameTime();
					}
					else if (IsKeyDown(KEY_DOWN))
					{
						seMovio = siAbajo;
						nave.pos.y+=500*GetFrameTime();
					}
					else
					{
						seMovio = quieta;
					}

					if (seMovio==quieta)
					{
						actualizarSpriteNave();
					}
					if (seMovio==siArriba)
					{
						sourceRec.x = nave.sprite.width/5*4;
					}
					if (seMovio == siAbajo)
					{
						sourceRec.x = nave.sprite.width / 5*3;
					}
				}
				
			}

			void actualizarSpriteNave()
			{
				if (framesCounter > 2)
				{
					framesCounter = 0;
				}

				sourceRec.x = framesCounter * nave.sprite.width / 5;

				framesCounter++;
			}

			void chequearColisionConBordes()
			{
				if (nave.pos.y <= bordes[arriba])
				{
					nave.pos.y = bordes[arriba];
				}
				if (nave.pos.y >= bordes[abajo])
				{
					nave.pos.y = bordes[abajo];
				}
			}

			void dibujarNave()
			{
				DrawTexturePro(nave.sprite, sourceRec,
					{ nave.pos.x , nave.pos.y, (float)nave.sprite.width / 8 , (float)nave.sprite.height /1.6f },
					{ (float)nave.sprite.width / 16,(float)nave.sprite.height /3.2f }, nave.rotacion, WHITE);
			}
	}
}