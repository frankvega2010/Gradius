#include "gameover.h"

#include "raylib.h"
#include "botones/botones.h"
#include "gameplay/gameplay.h"
#include "juego.h"

namespace Juego
{
	namespace Gameover
	{
		static Texture2D fondo;
		static Texture2D resultado;
		static Texture2D felicidades;
		static Texture2D perdiste;
		static Texture2D volverAJ;
		static Texture2D volverAM;
		static Texture2D asteroideP;
		static Texture2D asteroideB;
		static Texture2D jugarB;
		static Texture2D volverMB;

		static void chequearMouse();

		void inicializarGO()
		{
			fondo = LoadTexture("res/assets/sprites/gameover/gameover.png");
			felicidades = LoadTexture("res/assets/sprites/gameover/felicidades.png");
			perdiste = LoadTexture("res/assets/sprites/gameover/perdiste.png");
			volverAJ = LoadTexture("res/assets/sprites/gameover/volver a jugar.png");
			volverAM = LoadTexture("res/assets/sprites/gameover/volver al menu.png");
			asteroideB = LoadTexture("res/assets/sprites/gameover/asteroideB.png");
			asteroideP = LoadTexture("res/assets/sprites/gameover/asteroideP.png");
			jugarB = asteroideB;
			volverMB = asteroideB;
			resultado = perdiste;
		}

		void desinicializarGO()
		{
			UnloadTexture(fondo);
			UnloadTexture(felicidades);
			UnloadTexture(perdiste);
			UnloadTexture(volverAJ);
			UnloadTexture(volverAM);
			UnloadTexture(jugarB);
			UnloadTexture(volverMB);
			UnloadTexture(resultado);
			UnloadTexture(asteroideB);
			UnloadTexture(asteroideP);
		}

		static void chequearMouse()
		{
			if (chequearBoton(jugarB, asteroideB, asteroideP, jugarB.width * 2,
				jugarB.width * 3, jugarB.height * 3.5, jugarB.height * 4.5))
			{
				estado = juego;
			}
			
			if (chequearBoton(volverMB, asteroideB, asteroideP, volverMB.width * 2,
				volverMB.width * 3, volverMB.height * 5.5, volverMB.height * 6.5))
			{
				estado = menu;
			}

			if (Gameplay::gano)
			{
				resultado = felicidades;
			}
			else
			{
				resultado = perdiste;
			}
		}

		void chequearInputGO()
		{
			chequearMouse();
		}

		void dibujarGO()
		{
			DrawTexture(fondo, screenWidth / 2 - fondo.width / 2, screenHeight / 2 - fondo.height / 2, WHITE);
			DrawTexture(resultado, (screenWidth - resultado.width) / 2, resultado.height * 3/4, WHITE);
			DrawTexture(jugarB, jugarB.width * 2, jugarB.height * 3.5, WHITE);
			DrawTexture(volverMB, volverMB.width * 2, volverMB.height * 5.5, WHITE);
			DrawTexture(volverAJ, jugarB.width * 4, jugarB.height*3.5, WHITE);
			DrawTexture(volverAM, volverMB.width * 4, volverMB.height*5.5, WHITE);
		}
	}
}