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

			Vector2 vDireccion;  //vector que va de la nave a la pos del mouse, sirve para calcular la rotacion
			Vector2 vNormalizador;

			Rectangle sourceRec;

			void establecerSR()
			{
				sourceRec.x = 0;
				sourceRec.y = 0;
				sourceRec.width = nave.sprite.width/3;
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
				nave.sprite = LoadTexture("res/nave.png");
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
						sourceRec.x = 0.0f;
					}
					if (seMovio==siArriba)
					{
						sourceRec.x = nave.sprite.width/3*2;
					}
					if (seMovio == siAbajo)
					{
						sourceRec.x = nave.sprite.width / 3;
					}
				}
				
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
					{ nave.pos.x , nave.pos.y, (float)nave.sprite.width / 4 , (float)nave.sprite.height *2/3 },
					{ (float)nave.sprite.width / 8,(float)nave.sprite.height * 4/6 }, nave.rotacion, WHITE);
			}
	}
}