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
	void crearCirculos(sf::RenderWindow * window, int i, int ancho, int alto, sf::Font fuente);
	void crearLineas(sf::RenderWindow * window, int i, int ancho, int alto, sf::Font fuente);
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
void  metodos::crearCirculos(sf::RenderWindow * window, int i, int ancho, int alto, sf::Font fuente) {
	sf::Text numero;
	sf::String cadenaNum;


	sf::CircleShape Circleshape(30);
	Circleshape.setFillColor(sf::Color::White);
	//CREAMOS EL CIRUCULO
	Circleshape.setPosition(ancho, alto);
	window->draw(Circleshape);
	ancho = ancho + 100;
	//AGREGAMOS LOS NUMEROS
	std::string num = std::to_string(i);
	// Damos un valor a la cadena
	cadenaNum = num;
	// Asignamos la cadena al texto
	numero.setString(cadenaNum);
	// Asignamos la fuente que hemos cargado al texto
	numero.setFont(fuente);
	// Tamaño de la fuente
	numero.setCharacterSize(20);
	// Color al texto
	numero.setFillColor(sf::Color::Black);
	// Posicion del texto
	numero.setPosition(ancho - 75, alto + 18);
	//MANDAS A LA VENTANA EL NUMERO
	window->draw(numero);
}
void crearLinea(sf::RenderWindow * window, int i, int ancho, int alto) {
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(10, 10)),
		sf::Vertex(sf::Vector2f(150, 150))
	};

	window->draw(line, 2, sf::Lines);
}

#endif