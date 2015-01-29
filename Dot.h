/*
 * Dot.h
 *
 *  Created on: Jan 27, 2015
 *      Author: nad
 */

#ifndef ZERODOTS_DOT_H_
#define ZERODOTS_DOT_H_
#include <SFML/Graphics.hpp>
class Dot {
public:
	Dot(unsigned int x, unsigned int y);
	virtual ~Dot();
	sf::CircleShape shape;
	int xVel;
	int yVel;

};

#endif /* ZERODOTS_DOT_H_ */
