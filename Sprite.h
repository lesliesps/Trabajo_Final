#pragma once
using namespace System::Drawing;

enum Direccion { Arriba, Abajo, Izquierda, Derecha, Ninguno };

class Sprite
{
protected:
	int x, y;
	int dx, dy;
	int ancho, alto;
	int filas, columnas;
	int indiceX, indiceY;
	int velocidad;

public:
	Sprite(int x, int y, int ancho, int alto, int filas, int columnas) {
		this->x = x;
		this->y = y;
		this->ancho = ancho;
		this->alto = alto;
		this->filas = filas;
		this->columnas = columnas;

		dx = 0;
		dy = 0;
		indiceX = 0;
		indiceY = 0;
		velocidad = 0;
	}

	virtual ~Sprite() {}

	virtual void mover(Direccion tecla, int limiteAncho, int limiteAlto) = 0;

	void dibujar(Graphics^ g, Bitmap^ imagen) {

		int anchoCelda = imagen->Width / columnas;
		int altoCelda = imagen->Height / filas;

		Rectangle origen = Rectangle(indiceX * anchoCelda, indiceY * altoCelda, anchoCelda, altoCelda);
		Rectangle destino = Rectangle(x, y, ancho, alto);
		g->DrawImage(imagen, destino, origen, GraphicsUnit::Pixel);
	}

	Rectangle getRectangle() {
		return Rectangle(x + ancho / 5, y + alto / 5, ancho * 3 / 5, alto * 3 / 5);
	}

	void dibujarRectangulo(Graphics^ g) {
		g->DrawRectangle(Pens::Red, getRectangle());
	}


	int getX() { return x; }
	int getY() { return y; }
	int getIndiceX() { return indiceX; }

	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }

};



