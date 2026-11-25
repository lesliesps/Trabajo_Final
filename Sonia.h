#include "Sprite.h"

class Sonia : public Sprite
{
private:
	Direccion direccion;

public:
	Sonia(int x, int y) : Sprite(x, y, 110, 110, 4, 4) {
		direccion = Derecha;
		velocidad = 12;
	}

	Direccion getDireccion() { return direccion; }

	void mover(Direccion tecla, int limiteAncho, int limiteAlto) override {
		if (tecla != Ninguno) {
			direccion = tecla;
			dx = 0;
			dy = 0;

			if (tecla == Arriba) dy = -1;
			if (tecla == Abajo) dy = 1;
			if (tecla == Izquierda) dx = -1;
			if (tecla == Derecha) dx = 1;

			x += dx * velocidad;;
			y += dy * velocidad;

			if (x < 0) x = 0;
			if (y < 0) y = 0;

			if (x > limiteAncho - ancho) x = limiteAncho - ancho;
			if (y > limiteAlto - alto) y = limiteAlto - alto;
		}
		if (direccion == Arriba) indiceY = 0;
		if (direccion == Abajo) indiceY = 1;
		if (direccion == Izquierda) indiceY = 2;
		if (direccion == Derecha) indiceY = 3;

		if (tecla != Ninguno) {
			indiceX++;
			if (indiceX > 3) indiceX = 0;
		}
		else {
			indiceX = 0;
		}
	}

};