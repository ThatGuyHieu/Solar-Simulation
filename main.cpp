/*Copyright 2023 Brandon Nguyen*/
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Universe.hpp"
#include "Solar.hpp"

int main(int argc, const char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Solar System");

    double timealloc = std::stod(argv[1]);
    double steps = std::stod(argv[2]);
    double finaltime = 0;
    window.setFramerateLimit(60);

    Universe universe;
    std::cin >> universe;

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpg")) {
        std::cerr << "Failed to load background image." << std::endl;
        return 1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || finaltime > timealloc) {
                window.close();
            }
        }

        window.clear();

        window.draw(backgroundSprite);

        for (int i = 0; i < universe.getNumBodies(); i++) {
            const std::shared_ptr<CelestialBody>& body = universe.getPlanet(i);
            window.draw(*body);
        }

        window.display();
        universe.step(steps);
    }

    return 0;
}
