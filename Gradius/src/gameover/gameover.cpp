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
		static Texture2D volverAJP;
		static Texture2D volverAM;
		static Texture2D volverAMP;
		static Texture2D jugarB;
		static Texture2D volverMB;

		static void chequearMouse();

		void inicializarGO()
		{
			fondo = LoadTexture("res/assets/fondo portada.png");
			felicidades = LoadTexture("res/assets/gameover/felicidades.png");
			perdiste = LoadTexture("res/assets/gameover/perdiste0.png");
			volverAJ = LoadTexture("res/assets/gameover/volver a jugar.png");
			volverAJP = LoadTexture("res/assets/gameover/volver a jugarP.png");
			volverAM = LoadTexture("res/assets/pausa/volver al menu.png");
			volverAMP = LoadTexture("res/assets/pausa/volver al menuP.png");
			jugarB = volverAJ;
			volverMB = volverAM;
			resultado = perdiste;
		}

		void desinicializarGO()
		{
			UnloadTexture(fondo);
			UnloadTexture(felicidades);
			UnloadTexture(perdiste);
			UnloadTexture(volverAJ);
			UnloadTexture(volverAJP);
			UnloadTexture(volverAM);
			UnloadTexture(volverAMP);
			UnloadTexture(jugarB);
			UnloadTexture(volverMB);
			UnloadTexture(resultado);
		}

		void chequearMouse()
		{
			if (chequearBoton(jugarB, volverAJ, volverAJP,
				(screenWidth - jugarB.width) / 2, (screenWidth - jugarB.width) / 2 + jugarB.width,
				screenHeight - (jugarB.height * 2 + jugarB.height),
				(screenHeight - (jugarB.height * 2 + jugarB.height)) + jugarB.height))
			{
				estado = juego;
			}

			if (chequearBoton(volverMB, volverAM, volverAMP,
				(screenWidth - volverMB.width) / 2, (screenWidth - volverMB.width) / 2 + volverMB.width,
				screenHeight - (jugarB.height * 2 + jugarB.height),
				(screenHeight - (jugarB.height * 2 + jugarB.height)) + jugarB.height))
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
			DrawTexture(resultado, (screenWidth - resultado.width) / 2, resultado.height * 2, WHITE);
			DrawTexture(jugarB, (screenWidth - jugarB.width) / 2, screenHeight - (jugarB.height * 2 + jugarB.height), WHITE);
			DrawTexture(volverMB, (screenWidth - volverMB.width) / 2, screenHeight - (volverMB.height + volverMB.height / 2), WHITE);
		}
	}
}