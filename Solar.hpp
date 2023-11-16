/*Copyright 2023 Brandon Nguyen*/
#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class CelestialBody : public sf::Drawable {
 public:
    CelestialBody();
    CelestialBody(double radius, double xPosition, double yPosition,
    double xVelocity, double yVelocity, double mass, const std::string& fileName);

    friend std::istream& operator>>(std::istream& istream, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& ostream, const CelestialBody& body);

    double getXPosition() const;
    double getYPosition() const;
    double getXVelocity() const;
    double getYVelocity() const;
    double getMass() const;
    double getRadius() const;

    void setXPosition(double xPosition);
    void setYPosition(double yPosition);
    std::string getFileName() const;
    void setRadius(double r);

    void setVelocities(double x, double y) {
            _xVelocity = x;
            _yVelocity = y;
    }

    void setPosition(double x, double y);

 private:
    static const sf::Vector2u winSize;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    double _radius;
    double _xPosition;
    double _yPosition;
    double _xVelocity;
    double _yVelocity;
    double _mass;
    std::string _fileName;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite Planet;

    bool loadTexture();
};
