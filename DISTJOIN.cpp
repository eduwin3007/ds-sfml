#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <windows.h> 
#include <string>
#include <iostream>
#include <vector>
#include "Nodo.h"
#include "Textos.h"
#pragma comment(lib, "user32.lib")

struct Contexto {
	UFDS* us;
	std::queue<Move*> * movimientos;
	std::vector<Nodo*> * nodos;
	int width, height;
};

//función recursiva para crear el "árbol"
void dibujarPosicion(int padre, float x, float y, float ancho, Contexto cx) {
	vector <int> nodos;
	if (padre == -1) {
		nodos = cx.us->getPadres();
	}
	else {
		nodos = cx.us->getHijos(padre);
	}
	int anchoBloque = ancho / nodos.size();
	for (int i = 0; i < nodos.size(); i++) {
		if (padre != -1) {
			cx.nodos->at(padre)->hijos.push_back(cx.nodos->at(nodos[i]));
		}
		//Dibujar en cada bloque un nodo
		int xInicio = x + (anchoBloque * i);
		int altoNodo = (*cx.nodos)[nodos[i]]->alto;
		int nodoX = xInicio + (anchoBloque / 2) - (altoNodo/ 2);
		cx.movimientos->push(new Move(nodoX, y,0.5,0.5,cx.nodos->at(nodos[i])));
		//Dibujas hijos
		dibujarPosicion(nodos[i], xInicio , y + altoNodo + 100, anchoBloque, cx);
	}
}
/*
void actualizarGrafo(Contexto cx) {
	for (int i = 0; i < cx.us->p.size(); i++) {

	}
}*/

void mi_algoritmo(Contexto cx) {
	dibujarPosicion(-1, 0, 100, cx.width, cx);
}
int main() {
	//Creando un objeto para realizar el algoritmo
	UFDS us;
	metodos met = metodos();
	int width, height;
	bool asd;
	int x = NULL;
	int y = NULL;
	//Creando los nodos y seteando los valores necesarios
	us.makeSet(9);

	/*us.unionSet(1, 2);
	us.unionSet(3, 5);
	us.unionSet(5, 2);
	us.unionSet(8, 0);
	us.unionSet(7, 3);
	us.unionSet(4, 6);*/
	cout << us.numDisjointSets() << endl;

	asd = us.isSameSet(5, 1);

	//Largo y ancho de la pantalla

	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	sf::RenderWindow window(sf::VideoMode(width, height), "Proyecto Mainframe: Union Find - DS");

	//CREAMOS UN OBJETO FUENTE
	sf::Font fuente;
	sf::Color color = sf::Color::White;
	// Intentamos cargarla
	if (!fuente.loadFromFile("orangejuice.ttf"))
	{
		return EXIT_FAILURE;
	}

	std::vector<Nodo*> nodos;
	std::queue<Move*> movimientos;
	sf::Clock clock;

	for (int i = 0; i < us.p.size(); i++) {
		Nodo* nodo = new Nodo(50, 0, i * 50, std::to_string(us.nNodo[i]), fuente, color);
		nodos.push_back(nodo);
	}
	Contexto cxt;
	cxt.us = &us;
	cxt.movimientos = &movimientos;
	cxt.nodos = &nodos;
	cxt.height = height;
	cxt.width = width;
	std::thread moving(mover, &movimientos);
	std::thread run_algoritmo(mi_algoritmo, cxt);
	while (window.isOpen())
	{	
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				int  xMouse = sf::Mouse::getPosition(window).x - window.getPosition().x;
				int  yMouse = sf::Mouse::getPosition(window).y - window.getPosition().y;
				for (int i = 0; i < nodos.size(); i++)
				{
					int xNodoIni = nodos[i]->x;
					int yNodoIni = nodos[i]->y;
					int xNodoFin = nodos[i]->x + 25;
					int yNodoFin = nodos[i]->y +25;
					if (xNodoIni < xMouse && xNodoFin > xMouse && yNodoIni < yMouse && yNodoFin > yMouse) {
						sf::Color colorRed = sf::Color::Red;
						sf::Color colorAzul = sf::Color::Blue;

						nodos[i]->color = colorAzul;
						int padre = us.findSet(atoi((nodos[i]->num).c_str()));
						nodos[padre]->color = colorRed;
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				sf::Color colorRed = sf::Color::Red;
				int  xMouse = sf::Mouse::getPosition(window).x - window.getPosition().x;
				int  yMouse = sf::Mouse::getPosition(window).y - window.getPosition().y;
				for (int i = 0; i < nodos.size(); i++)
				{
					int xNodoIni = nodos[i]->x;
					int yNodoIni = nodos[i]->y;
					int xNodoFin = nodos[i]->x + 50;
					int yNodoFin = nodos[i]->y + 50;
					if (xNodoIni < xMouse && xNodoFin > xMouse && yNodoIni < yMouse && yNodoFin > yMouse) {
						if (x == NULL){
							x = atoi((nodos[i]->num).c_str());
							cout << x << endl;
						}
						else if (x != NULL && y == NULL) {
							//std::thread moving(mover, &movimientos);
							std::thread run_algoritmo(mi_algoritmo, cxt);
							y = atoi((nodos[i]->num).c_str());
							us.unionSet(x, y);
							//moving.detach();
							run_algoritmo.detach();
							//moving.detach();
							x = NULL;
							y = NULL;

							
						}
					}
				}
			}

		}

		window.clear(sf::Color(133, 193, 233));

		for (int i = 0; i < nodos.size(); i++) {
			nodos[i]->paint(&window);
		}
		met.titulo(&window, width, fuente );
		window.display();

	}
	moving.detach();
	run_algoritmo.detach();

	return 0;
}
