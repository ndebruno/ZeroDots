#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <random>
#include <memory>
#include <cmath>
#include "Dot.h"
int main()
{
	bool dotConnected = false;
	bool lastState = false;
	int x, y, num, level;
	num = 0;
	level = 0;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> xDist(1, 800);
	std::uniform_int_distribution<int> yDist(1, 600);


	std::vector<std::shared_ptr<Dot>> shapes;
	std::shared_ptr<Dot> curShape = nullptr;
	sf::RectangleShape line;
	line.setFillColor(sf::Color::Black);
	line.setSize(sf::Vector2f(1, 2));

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	for(int c = 0 ; c < 2 ; c++){
		x = xDist(generator);
		y = yDist(generator);
		auto shape = std::make_unique<Dot>(x, y);
    	shapes.push_back(std::move(shape));

	}
    // set the shape color to green

    window.setVerticalSyncEnabled(true);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        dotConnected = false;
        for( auto& c : shapes){
        	//check left screen side
        	if(c->shape.getPosition().x <= 0){
        		c->xVel *= -1;
        	}
        	//check right screen side
			if(c->shape.getPosition().x >= 800){
				c->xVel *= -1;
			}
			//check bottom screen side
			if(c->shape.getPosition().y <= 0){
				c->yVel *= -1;
			}
			//check top screen side
			if(c->shape.getPosition().y >= 600){
				c->yVel *= -1;
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && lastState == false){
				sf::Vector2i tmp = sf::Mouse::getPosition(window);
				sf::Vector2f diff = sf::Vector2f((float)tmp.x, (float)tmp.y) - c->shape.getPosition();
				if(hypot(diff.x, diff.y) < c->shape.getRadius() + c->shape.getOutlineThickness()){
					curShape = c;
				}

			}
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)&& lastState == true){
				sf::Vector2i tmp = sf::Mouse::getPosition(window);
				sf::Vector2f diff = sf::Vector2f((float)tmp.x, (float)tmp.y) - c->shape.getPosition();
				if(hypot(diff.x, diff.y) < c->shape.getRadius() + c->shape.getOutlineThickness()&&curShape != c){
					dotConnected = true;
				}

				curShape = nullptr;
			}
        	c->shape.move(c->xVel, c->yVel);
        	window.draw(c->shape);

        }
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)&& lastState == true){
        	if(dotConnected){
        		num+=level;
        		level++;
        		for(auto& c:shapes){
        			c->xVel++;
        			c->yVel++;
        		}

        	}else{
        		num--;
        		window.close();
        	}
        	std::cout << num << std::endl;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && lastState == false){
			lastState = true;
		}else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			lastState =  false;
			curShape = nullptr;
		}

        if (curShape != nullptr){
			line.setPosition(curShape->shape.getPosition());
			sf::Vector2i tmp = sf::Mouse::getPosition(window);
			sf::Vector2f diff = sf::Vector2f((float)tmp.x, (float)tmp.y) - curShape->shape.getPosition();
			line.setSize(sf::Vector2f(hypot(diff.x, diff.y),line.getSize().y));
			line.setRotation(atan2(diff.y, diff.x)*180.f/M_PI);
			window.draw(line);
		}
        window.display();
	}


}
