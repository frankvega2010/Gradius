#include "menu.h"

#include "raylib.h"
#include "juego.h"
#include "botones/botones.h"

namespace Juego
{
	namespace Menu
	{
		Texture2D titulo;
		Texture2D botonJugar;
		Texture2D botonCreditos;
		Texture2D botonJugarP;
		Texture2D botonCreditosP;
		Texture2D jugarB;
		Texture2D creditosB;
		Texture2D botonSalir;
		Texture2D botonSalirP;
		Texture2D salirB;
		bool salir;

		static void chequearMouse();

		void inicializarMenu()
		{
			titulo = LoadTexture("res/assets/menu/titulo gradius.png");
			botonJugar = LoadTexture("res/assets/menu/boton jugar.png");
			botonCreditos = LoadTexture("res/assets/menu/boton creditos.png");
			botonJugarP = LoadTexture("res/assets/menu/boton jugarP.png");
			botonCreditosP = LoadTexture("res/assets/menu/boton creditosP.png");
			botonSalir = LoadTexture("res/assets/menu/boton salir.png");
			botonSalirP = LoadTexture("res/assets/menu/boton salirP.png");
			jugarB = botonJugar;
			creditosB = botonCreditos;
			salirB = botonSalir;
			salir = false;
		}

		void desinicializarMenu()
		{
			UnloadTexture(titulo);
			UnloadTexture(botonCreditosP);
			UnloadTexture(botonCreditos);
			UnloadTexture(botonJugar);
			UnloadTexture(botonJugarP);
			UnloadTexture(botonSalir);
			UnloadTexture(botonSalirP);
		}

		void chequearMouse()
		{
			if (ubicarBoton(jugarB, botonJugar, botonJugarP,
				(screenWidth - jugarB.width) / 2, (screenWidth - jugarB.width) / 2 + jugarB.width,
				screenHeight / 6 * 4 - jugarB.height / 3, screenHeight / 6 * 4 - jugarB.height / 3 + jugarB.height))
			{
				estado = juego;
			}

			if (ubicarBoton(creditosB, botonCreditos, botonCreditosP,
						    (screenWidth - creditosB.width) / 2, (screenWidth - creditosB.width) / 2 + creditosB.width,
					        screenHeight / 6 * 5 - creditosB.height / 4,
							screenHeight / 6 * 5 - creditosB.height / 4 + creditosB.height))
			{
				estado = creditos;
			}

			if(ubicarBoton(salirB, botonSalir, botonSalirP,
						   screenWidth / 30, screenWidth / 30 + botonSalir.width,
						   screenHeight / 20, screenHeight / 20 + botonSalir.height))
			{
				salir = true;
			}

		}
		
		void chequearInputMenu()
		{
			chequearMouse();
		}

		void dibujarMenu()
		{
			DrawTexture(titulo,0,0, WHITE);
			DrawTexture(jugarB, (screenWidth-jugarB.width)/2, screenHeight / 6*4-jugarB.height/3, WHITE);
			DrawTexture(creditosB, (screenWidth - creditosB.width) / 2, screenHeight / 6 * 5 - creditosB.height / 4, WHITE);
			DrawTexture(salirB, screenWidth/30, screenHeight/20, WHITE);
		}
	}
}