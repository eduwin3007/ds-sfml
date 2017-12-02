#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>


#ifndef __METODOS_H__
#define __METODOS_H__

class metodos {
public:
	void titulo(sf::RenderWindow * window, int width, sf::Font fuente);
	void curso(sf::RenderWindow * window, int width, sf::Font fuente);
};

void  metodos::titulo(sf::RenderWindow * window, int width, sf::Font fuente) {
	// Creamos un objeto texto
	sf::Text texto;

	// Creamos un objeto String
	sf::String cadena;

	// Damos un valor a la cadena
	cadena = "UNION FIND - DISTJOIN";

	// Asignamos la cadena al texto
	texto.setString(cadena);

	// Asignamos la fuente que hemos cargado al texto
	texto.setFont(fuente);

	// Tamaño de la fuente
	texto.setCharacterSize(40);

	// Posición del texto
	texto.setPosition((width / 2) - 170, 0);

	// Cambiando color 
	texto.setFillColor(sf::Color::Black);

	window->draw(texto);

}
void  metodos::curso(sf::RenderWindow * window, int width, sf::Font fuente) {
	// Creamos un objeto texto
	sf::Text texto;

	// Creamos un objeto String
	sf::String cadena;

	// Damos un valor a la cadena
	cadena = "BIENVENIDO PROFESOR WALTER PRESIONE ESPACIO...";

	// Asignamos la cadena al texto
	texto.setString(cadena);

	// Asignamos la fuente que hemos cargado al texto
	texto.setFont(fuente);

	// Tamaño de la fuente
	texto.setCharacterSize(30);

	// Posición del texto
	texto.setPosition((width / 2) - 200, 300);

	// Cambiando color 
	texto.setFillColor(sf::Color::Black);

	window->draw(texto);

}


#endif