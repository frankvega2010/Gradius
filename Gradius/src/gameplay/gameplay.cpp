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
			desinicializarEnemigos();
			desinicializarFondo();
			desinicializarDisparos();
			timer = 0;
		}

		void chequearInputGP()
		{
			if (timer > 3)
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
			if (timer > 3)
			{
				chequearColisionConAsteroide();
				chequearColisionConEnemigos();
				chequearColisionConBordes();
				moverAsteroides();
				moverEnemigos();
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

		static void dibujarBotonPausa()
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
				dibujarEnemigos();
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