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
			static void calcularAnguloRotacion();
			static void normalizarDireccion();

			void iniciarNave()
			{
				nave.base = screenWidth/30;
				nave.altura = (nave.base / 2) / tanf(25 * DEG2RAD);
				nave.rotacion = 90;
				nave.pos = { (float)screenWidth / nave.altura*2,(float)screenHeight / 2 };
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
			}

			void moverNave()
			{
				//calcularAnguloRotacion();
				//normalizarDireccion();
				
				if (!pausa)
				{
					if(IsKeyDown(KEY_UP))
					{
						nave.pos.y--;
					}
					if (IsKeyDown(KEY_DOWN))
					{
						nave.pos.y++;
					}
				}
				
			}

			void chequearColisionConBordes()
			{
				if (nave.pos.x < bordes[izquierda])
				{
					nave.pos.x = bordes[derecha];
				}
				if (nave.pos.x > bordes[derecha])
				{
					nave.pos.x = bordes[izquierda];
				}
				if (nave.pos.y < bordes[arriba])
				{
					nave.pos.y = bordes[abajo];
				}
				if (nave.pos.y > bordes[abajo])
				{
					nave.pos.y = bordes[arriba];
				}
			}

			void dibujarNave()
			{
				DrawTexturePro(nave.sprite, { 0.0f,0.0f,(float)nave.sprite.width,(float)nave.sprite.height },
					{ nave.pos.x , nave.pos.y, (float)nave.sprite.width / 8 , (float)nave.sprite.height / 8 },
					{ (float)nave.sprite.width / 16,(float)nave.sprite.height / 16 }, nave.rotacion, WHITE);
			}
	}
}