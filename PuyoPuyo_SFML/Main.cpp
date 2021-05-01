#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //project window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(750, 1000), "HelloWorld");

    //shape example
    sf::RectangleShape* yolo = new sf::RectangleShape(sf::Vector2f(25, 25));

    //clock and delta time
	sf::Clock* DeltaClock = new sf::Clock();
	float DeltaTime;

    //loop
    while (window->isOpen())
	{
        //update deta time
		DeltaTime = DeltaClock->getElapsedTime().asSeconds();
		DeltaClock->restart();

        //event
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        //window update
        window->clear();

        window->draw(*yolo);

        window->display();
    }

    return 0;
}