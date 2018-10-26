#include "gameplay.h"

#include "raylib.h"
#include "juego.h"
#include "nave/nave.h"
#include "asteroides/asteroides.h"
#include "disparos/disparos.h"
#include "pausa/pausa.h"
#include "fondo/fondo.h"

namespace Juego
{
	namespace Gameplay
	{	
		Texture2D fondo;
		Texture2D botonPausa;
		Music musicaFondo;

		float bordes[4];

		bool gano;

		bool gameOver;

		static void iniciarBordes();
		static void dibujarBotonPausa();

		void iniciarBordes()
		{
			bordes[arriba] = nave.base;
			bordes[abajo] = screenHeight -nave.base;
		}

		void iniciarComponentesGP()
		{
			iniciarNave();
			iniciarBordes();
			iniciarAsteroides();
			inicializarDisparos();
			inicializarFondo();
			botonPausa = LoadTexture("res/assets/pausa/boton pausa.png");
			fondo = LoadTexture("res/assets/fondo.png");
#ifdef AUDIO
			musicaFondo = LoadMusicStream("res/assets/sonidos/musica espacio.ogg");
			if (haySonido)
			{
				PlayMusicStream(musicaFondo);
			}
#endif
			gameOver = false;
			pausa = false;
			gano = false;
		}

		void desinicializarGP()
		{
#ifdef AUDIO
			StopMusicStream(musicaFondo);
			UnloadMusicStream(musicaFondo);
#endif
			UnloadTexture(nave.sprite);
			UnloadTexture(botonPausa);
			UnloadTexture(fondo);
			desinicializarAsteroides();
			desinicializarFondo();
		}

		void chequearInputGP()
		{
			moverNave();
			
			cambiarPausa();

			if (pausa)
			{
				chequearInputPausa();
			}
			else
			{
				activarDisparos();
			}
		}

		void actualizarGP()
		{
#ifdef AUDIO
				if (haySonido)
				{
					UpdateMusicStream(musicaFondo);
				}
#endif
				//actualizarNave();
				chequearColisionConAsteroide();
				chequearColisionConBordes();
				moverAsteroides();
				actualizarDisparos();
				moverDisparos();
				actualizarFondo();
				if (gameOver)
				{
					estado = gameover;
				}
				if (nave.puntaje ==cantAsteroidesG*5)
				{
					gano = true;
					gameOver = true;
				}
			
		}

		void dibujarBotonPausa()
		{
			DrawTexture(botonPausa, screenWidth/45, screenHeight/30, WHITE);
		}

		void dibujarGameplay()
		{
			//DrawTexture(fondo, screenWidth / 2 - fondo.width / 2, screenHeight / 2 - fondo.height / 2, WHITE);
			dibujarFondo();
			dibujarDisparos();
			dibujarNave();
			dibujarAsteroides();
			
			DrawText(FormatText("%i", nave.puntaje),
								screenWidth - screenWidth / 10, screenHeight / 30,
								screenWidth*screenHeight / 10800, MAGENTA);
			if (!pausa)
			{
				dibujarBotonPausa();
				DrawCircleV(GetMousePosition(), 3, RED);
			}
			
			if (pausa)
			{
				dibujarPausa();
			}
		}
	}
}