#include "juego.h"

#include "raylib.h"
#include "botones/botones.h"
#include "menu/menu.h"
#include "gameplay/gameplay.h"
#include "gameover/gameover.h"
#include "creditos/creditos.h"
#include "gameplay/pausa/pausa.h"

namespace Juego 
{
	int screenWidth = 900;
	int screenHeight = 600;

	Estado estado=menu;
	Estado estadoA=menu;
	static bool enjuego = true;
	Music musicaJuego;
	bool haySonido = true;
	static Texture2D unmute;
	static Texture2D mute;
	static Texture2D sonido;

	static void inicializarJuego();
	static void finalizarJuego();
	static void dibujarJuego();
	static void cambiarEstado();
	static void chequearInput();
	static void actualizarJuego();
	static void dibujarVersion();
	static void mutear();
	static void dibujarSonido();
	static void inicializarComponentesJuego();
	static void desinicializarComponentesjuego();

	static void mutear()
	{
		if (chequearBoton(sonido, screenWidth - screenWidth/8, screenWidth - screenWidth / 8 + sonido.width,
			screenHeight - screenHeight/6, screenHeight - screenHeight / 6 + sonido.height))
		{
			haySonido = !haySonido;
			if (haySonido)
			{
				sonido = unmute;
			}
			else
			{
				sonido = mute;
			}
		}
	}

	static void chequearInput()
	{
		switch (estado)
		{
		case menu:
			Menu::chequearInputMenu();
			break;
		case juego:
		case juegoPausado:
			Gameplay::chequearInputGP();
			break;
		case gameover:
			Gameover::chequearInputGO();
			break;
		case creditos:
			Creditos::chequearInputCreditos();
			break;
		}
		mutear();
	}

	static void actualizarJuego()
	{
		switch (estado)
		{
		case menu:
			if (estado != estadoA)
			{
				Menu::inicializarMenu();
				if (estadoA == creditos)
				{
					Creditos::desinicializarCreditos();
				}

				if (estadoA == juegoPausado)
				{
					Gameplay::desinicializarGP();
#ifdef AUDIO		
					if (haySonido)
					{
						ResumeMusicStream(musicaJuego);
					}
#endif
					ShowCursor();
				}
			}
#ifdef AUDIO
			if (haySonido)
			{
				UpdateMusicStream(musicaJuego);
			}
#endif
			break;
		case juego:
			if (estado != estadoA)
			{
				if (estadoA != juegoPausado)
				{
					Gameplay::iniciarComponentesGP();
#ifdef AUDIO
					if (haySonido)
					{
						PauseMusicStream(musicaJuego);
					}
#endif
				}
				if(estadoA==juegoPausado)
				{
					Gameplay::desinicializarPausa();
				}
				if (estadoA == menu)
				{
					Menu::desinicializarMenu();
				}
				else if (estadoA == gameover)
				{
					Gameover::desinicializarGO();
				}
				HideCursor();
			}
			Gameplay::actualizarGP();

			if (!Gameplay::gameOver)
			{
				break;
			}
		case gameover:
			if (estado != estadoA)
			{
				Gameover::inicializarGO();
				Gameplay::desinicializarGP();
				ShowCursor();
#ifdef AUDIO
				if (haySonido)
				{
					StopMusicStream(musicaJuego);
					PlayMusicStream(musicaJuego);
				}
#endif 
			}
#ifdef AUDIO
			if (haySonido)
			{
				UpdateMusicStream(musicaJuego);
			}
#endif
			break;
		case juegoPausado:
			if (estado != estadoA)
			{
				Gameplay::iniciarComponentesPausa();
				ShowCursor();
			}
#ifdef AUDIO
			if (haySonido)
			{
				UpdateMusicStream(Gameplay::musicaFondo);
			}
#endif
			break;
		case creditos:
			if (estado != estadoA)
			{
				Creditos::inicializarCreditos();
				Menu::desinicializarMenu();
			}
#ifdef AUDIO
			if (haySonido)
			{
				UpdateMusicStream(musicaJuego);
			}
#endif
			break;
		}
	}

	static void cambiarEstado()
	{
		if (estado != estadoA)
		{
			estadoA = estado;
		}
	}

	static void dibujarVersion()
	{
		DrawText("v1.1", screenWidth - screenWidth/10, screenHeight/15, screenHeight*screenWidth/27000, WHITE);
	}

	static void dibujarSonido()
	{
		DrawTexture(sonido,screenWidth - screenWidth/8, screenHeight - screenHeight/6, WHITE);
	}

	static void dibujarJuego()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		switch (estado)
		{
		case menu:
			Menu::dibujarMenu();
			dibujarVersion();
			break;
		case creditos:
			Creditos::dibujarCreditos();
			dibujarVersion();
			break;
		case juego:
			Gameplay::dibujarGameplay();
			break;
		case gameover:
			Gameover::dibujarGO();
			break;
		case juegoPausado:
			Gameplay::dibujarGameplay();
			break;
		}
		dibujarSonido();
		EndDrawing();
	}

	void ejecutarJuego()
	{
		inicializarJuego();
		while (enjuego)
		{
			cambiarEstado();

			//input
			chequearInput();
			//actualizacion
			actualizarJuego();
			//dibujo
			dibujarJuego();

			//-------------
			if (Menu::salir || WindowShouldClose())
			{
				enjuego=false;
			}
		}
		finalizarJuego();
	}

	static void inicializarComponentesJuego()
	{
#ifdef AUDIO
		musicaJuego = LoadMusicStream("res/assets/sonidos/menu.ogg");
		PlayMusicStream(musicaJuego);
#endif
		unmute = LoadTexture("res/assets/sprites/sonido.png");
		mute = LoadTexture("res/assets/sprites/mute.png");
		sonido = unmute;
	}

	static void inicializarJuego()
	{
		//init game
		InitWindow(screenWidth, screenHeight, "Asteroids");
#ifdef AUDIO
		InitAudioDevice();
#endif
		inicializarComponentesJuego();
		SetExitKey(0);
		Menu::inicializarMenu();
	}

	static void desinicializarComponentesjuego()
	{
#ifdef AUDIO
		UnloadMusicStream(musicaJuego);
#endif
		UnloadTexture(unmute);
		UnloadTexture(mute);
		UnloadTexture(sonido);
	}

	static void finalizarJuego()
	{
		//close game
		Menu::desinicializarMenu();
		desinicializarComponentesjuego();
#ifdef AUDIO
		CloseAudioDevice();
#endif
		CloseWindow();
	}
}