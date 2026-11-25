#pragma once
#include "Sprite.h"
#include <cstdlib>

class Aliona : public Sprite
{
public:
	Aliona(int x, int y) : Sprite(x, y, 80, 80, 4, 4) {
		velocidad = rand() % 8 + 3;
		dy = 1;
		dx = 1;
		if (rand() % 2 == 0) dx = -1;
		if (rand() % 2 == 0) dy = -1;
	}

	void mover(Direccion tecla, int limiteAncho, int limiteAlto) override {

		x += dx * velocidad;
		y += dy * velocidad;

		if (x < 0) {
			x = 0;
			dx = 1;
		}

		if (y < 0) {
			y = 0;
			dy = 1;
		}

		if (x > limiteAncho - ancho) {
			x = limiteAncho - ancho;
			dx = -1;
		}

		if (y > limiteAlto - alto) {
			y = limiteAlto - alto;
			dy = -1;
		}

		if (dy == 1) indiceY = 2;
		else indiceY = 1;
		indiceX++;
		if (indiceX > 3) indiceX = 0;
	}
};