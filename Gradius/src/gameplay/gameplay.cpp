#include "gameplay.h"

#include "raylib.h"
#include "juego.h"
#include "nave/nave.h"
#include "asteroides/asteroides.h"
#include "disparos/disparos.h"
#include "pausa/pausa.h"
#include "fondo/fondo.h"
#include "enemigo\enemigo.h"

namespace Juego
{
	namespace Gameplay
	{	
		static Texture2D botonPausa;
		static Texture2D controles;
		Music musicaFondo;

		static float timer = 0.0f;

		bool gano;

		bool gameOver;

		static void dibujarBotonPausa();
		static void actualizarTiempo();

		void iniciarComponentesGP()
		{
			iniciarNave();
			iniciarAsteroides();
			iniciarEnemigos();
			inicializarDisparos();
			inicializarFondo();
			botonPausa = LoadTexture("res/assets/sprites/pausa/boton pausa.png");
			controles = LoadTexture("res/assets/sprites/gameplay/controles gradius.png");
#ifdef AUDIO
			musicaFondo = LoadMusicStream("res/assets/sonidos/stage.ogg");
			if (haySonido)
			{
				PlayMusicStream(musicaFondo);
			}
#endif
			cantEnemiesTarget = 50;
			gameOver = false;
			pausa = false;
			gano = false;
		}

		void desinicializarGP()
		{
#ifdef AUDIO
			StopMusicStream(musicaFondo);
			UnloadMusicStream(musicaFondo);
			UnloadSound(aColision); //problem here fix this crap
#endif
			UnloadTexture(nave.sprite);
			UnloadTexture(botonPausa);
			UnloadTexture(controles);
			desinicializarEnemigos();
			desinicializarAsteroides();
			desinicializarFondo();
			desinicializarDisparos();
			timer = 0;
		}

		void chequearInputGP()
		{
			if (timer > 5)
			{
				moverNave();

				if (!pausa)
				{
					activarDisparos();
				}
			}

			cambiarPausa();

			if (pausa)
			{
				chequearInputPausa();
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
			if (timer > 5)
			{
				chequearColisionConAsteroide();
				chequearColisionConEnemigos();
				chequearColisionConBordes();
				moverAsteroides();
				moverEnemigos();
				actualizarDisparos();
				moverDisparos();
				actualizarFondo();
				if (cantEnemiesTarget <= 0)
				{
					gano = true;
					gameOver = true;
					cantEnemiesTarget = 50;
				}

				if (gameOver)
				{
					estado = gameover;
				}
			}
		}

		static void dibujarBotonPausa()
		{
			DrawTexture(botonPausa, screenWidth/45, screenHeight/30, WHITE);
		}

		void dibujarGameplay()
		{
			if (timer <= 5)
			{
				DrawTexture(controles, 0, 0, WHITE);
			}
			else
			{
				dibujarFondo();
				dibujarNave();
				dibujarAsteroides();
				dibujarDisparos();
				dibujarEnemigos();

				DrawText(FormatText("Targets Left: %i", cantEnemiesTarget), 80, 20, 50, WHITE);
			}
			if (!pausa)
			{
				dibujarBotonPausa();
				DrawCircleV(GetMousePosition(), 3, RED); //sin esto el jugador no puede poner pausa
			}
			
			if (pausa)
			{
				dibujarPausa();
			}
		}
	}
}