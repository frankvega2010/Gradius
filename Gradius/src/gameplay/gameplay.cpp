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
		static Texture2D fondo;
		static Texture2D botonPausa;
		static Texture2D controles;
		Music musicaFondo;

		static float timer = 0.0f;

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
			controles = LoadTexture("res/assets/controles gradius.png");
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
			UnloadTexture(controles);
			desinicializarAsteroides();
			desinicializarFondo();
			desinicializarDisparos();
			timer = 0;
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

		static void actualizarTiempo()
		{
			timer += GetFrameTime();
		}

		void actualizarGP()
		{
			actualizarTiempo();
#ifdef AUDIO
				if (haySonido)
				{
					UpdateMusicStream(musicaFondo);
				}
#endif
			if (timer > 3)
			{
				chequearColisionConAsteroide();
				chequearColisionConBordes();
				moverAsteroides();
				actualizarDisparos();
				moverDisparos();
				actualizarFondo();
				if (asteroidesDestruidos==cantAsteroidesG)
				{
					gano = true;
					gameOver = true;
				}

				if (gameOver)
				{
					estado = gameover;
				}
			}
		}

		void dibujarBotonPausa()
		{
			DrawTexture(botonPausa, screenWidth/45, screenHeight/30, WHITE);
		}

		void dibujarGameplay()
		{
			if (timer <= 3)
			{
				DrawTexture(controles, 0, 0, WHITE);
			}
			else
			{
				dibujarFondo();
				dibujarDisparos();
				dibujarNave();
				dibujarAsteroides();
			}
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