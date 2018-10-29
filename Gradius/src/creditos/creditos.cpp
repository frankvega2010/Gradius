#include "creditos.h"

#include "raylib.h"
#include "botones/botones.h"
#include "juego.h"

namespace Juego
{
	namespace Creditos
	{
		static Texture2D creditosT;
		static Texture2D atrasB;
		static Texture2D botonAtras;
		static Texture2D botonAtrasP;

		void inicializarCreditos()
		{
			creditosT = LoadTexture("res/assets/creditos/creditos.png");
			botonAtras = LoadTexture("res/assets/creditos/atras.png");
			botonAtrasP = LoadTexture("res/assets/creditos/atrasP.png");
			atrasB = botonAtras;
		}
		
		void desinicializarCreditos()
		{
			UnloadTexture(creditosT);
			UnloadTexture(botonAtras);
			UnloadTexture(botonAtrasP);
			UnloadTexture(atrasB);
		}

		void chequearInputCreditos()
		{
			if (chequearBoton(atrasB, botonAtras, botonAtrasP, screenWidth / 53, screenWidth / 53 + atrasB.width,
				screenHeight / 30, screenHeight / 30 + atrasB.height))
			{
				estado = menu;
			}

		}

		void dibujarCreditos()
		{
			DrawTexture(creditosT, 0, 0, WHITE);
			DrawTexture(atrasB, screenWidth / 53, screenHeight / 30, WHITE);
		}
	}
}