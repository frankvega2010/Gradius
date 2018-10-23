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
			Nave nave;

			Vector2 vDireccion;  //vector que va de la nave a la pos del mouse, sirve para calcular la rotacion
			Vector2 vNormalizador;

			Rectangle sourceRec;

			void establecerSR()
			{
				sourceRec.x = nave.sprite.width/2;
				sourceRec.y = 0;
				sourceRec.width = nave.sprite.width/2;
				sourceRec.height = nave.sprite.height;
			}

			void iniciarNave()
			{
				nave.base = screenWidth/30;
				nave.altura = (nave.base / 2) / tanf(25 * DEG2RAD);
				nave.rotacion = 90;
				nave.pos = { (float)screenWidth / nave.altura*2,(float)screenHeight / 2 };
				nave.colision = { nave.pos.x + sin(nave.rotacion*DEG2RAD),
					nave.pos.y - cos(nave.rotacion*DEG2RAD) };
				nave.radioColision = nave.altura * 2 / 3 + 10;
				nave.sprite = LoadTexture("res/navespacial.png");
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

				bool seMovio = false;
				
				if (!pausa)
				{
					if(IsKeyDown(KEY_UP))
					{
						seMovio = true;
						nave.pos.y-=500*GetFrameTime();
					}
					if (IsKeyDown(KEY_DOWN))
					{
						seMovio = true;
						nave.pos.y+=500*GetFrameTime();
					}
					if (seMovio)
					{
						sourceRec.x = 0.0f;
					}
					else
					{
						sourceRec.x = nave.sprite.width/2;
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
					{ nave.pos.x , nave.pos.y, (float)nave.sprite.width / 8 , (float)nave.sprite.height / 4 },
					{ (float)nave.sprite.width / 16,(float)nave.sprite.height / 8 }, nave.rotacion, WHITE);
			}
	}
}