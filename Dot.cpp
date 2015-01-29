/*
 * Dot.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: nad
 */

#include "Dot.h"
Dot::Dot(unsigned int x, unsigned int y):xVel( 1 ) , yVel( 1 ) {
	// TODO Auto-generated constructor stub
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color(100, 250, 50));
	shape.setFillColor(sf::Color(150, 50, 250));
	shape.setPosition(x, y);
	shape.setRadius(10);
}

Dot::~Dot() {
	// TODO Auto-generated destructor stub



}

