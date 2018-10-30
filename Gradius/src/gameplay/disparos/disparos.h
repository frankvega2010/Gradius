#ifndef DISPAROS_H
#define DISPAROS_H

#include "raylib.h"

namespace Juego
{
	namespace Gameplay
	{
		struct Disparo
		{
			Vector2 pos;
			float radio;
			bool activo;
			float velocidad;
			float velocidadY;
			Texture2D sprite;
			float rotacionSprite;
		};

		const int cantDisparos = 6;
		const int cantMisiles = 5;
		extern Disparo disparos[cantDisparos];
		extern Disparo mortero[cantMisiles];

		void inicializarDisparos();
		void desinicializarDisparos();
		void activarDisparos();
		void moverDisparos();
		void actualizarDisparos();
		void dibujarDisparos();
	}
}

#endif // !DISPAROS_H

