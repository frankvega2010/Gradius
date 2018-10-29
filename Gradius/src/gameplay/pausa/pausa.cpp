#include "pausa.h"

#include "raylib.h"
#include "gameplay/gameplay.h"
#include "botones/botones.h"
#include "juego.h"

namespace Juego
{
	namespace Gameplay
	{
		bool pausa = false;

		//botones pausa
		static Texture2D botonDespausa;
		static Texture2D botonReiniciar;
		static Texture2D botonReiniciarP;
		static Texture2D botonMenu;
		static Texture2D botonMenuP;
		static Texture2D reiniciarB;
		static Texture2D menuB;
		//---------------------

		void iniciarComponentesPausa()
		{
			botonDespausa = LoadTexture("res/assets/pausa/boton despausa.png");
			botonMenu = LoadTexture("res/assets/pausa/volver al menu.png");
			botonMenuP = LoadTexture("res/assets/pausa/volver al menuP.png");
			botonReiniciar = LoadTexture("res/assets/pausa/reiniciar juego.png");
			botonReiniciarP = LoadTexture("res/assets/pausa/reiniciar juegoP.png");
			reiniciarB = botonReiniciar;
			menuB = botonMenu;
		}

		void desinicializarPausa()
		{
			UnloadTexture(botonDespausa);
			UnloadTexture(botonReiniciar);
			UnloadTexture(botonReiniciarP);
			UnloadTexture(botonMenu);
			UnloadTexture(botonMenuP);
			UnloadTexture(menuB);
			UnloadTexture(reiniciarB);
		}

		void cambiarPausa()
		{
			if (chequearBoton(botonDespausa, screenWidth / 37.5, screenWidth / 16, screenHeight / 26, screenHeight / 10.5))
			{
				pausa = !pausa;
				if (estado == juegoPausado)
				{
					estado = juego;
				}
				else
				{
					estado = juegoPausado;
				}
			}

		}

		void chequearInputPausa()
		{
			if (chequearBoton(reiniciarB, botonReiniciar, botonReiniciarP,
				(screenWidth - reiniciarB.width) / 2, (screenWidth - reiniciarB.width) / 2 + reiniciarB.width,
				reiniciarB.height, reiniciarB.height * 2))
			{
				desinicializarGP();
				iniciarComponentesGP();
				estado = juego;
			}

			if (chequearBoton(menuB, botonMenu, botonMenuP,
				(screenWidth - menuB.width) / 2, (screenWidth - menuB.width) / 2 + menuB.width,
				menuB.height * 4, menuB.height * 5))
			{
				estado = menu;
			}
		}

		void dibujarPausa()
		{
			DrawRectangleV({ 0.0f,0.0f }, { (float)screenWidth,(float)screenHeight },
				{ (unsigned char)0,(unsigned char)0,(unsigned char)0,(unsigned char)150 });


			DrawTexture(reiniciarB, (screenWidth - reiniciarB.width) / 2, reiniciarB.height, WHITE);
			DrawTexture(menuB, (screenWidth - menuB.width) / 2, reiniciarB.height * 4, WHITE);
			DrawTexture(botonDespausa, 30, 30, WHITE);
		}
	}
}