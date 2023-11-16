/*Copyright 2023 Brandon Nguyen*/

#include <iomanip>
#include "Solar.hpp"
#include "Universe.hpp"

const sf::Vector2u CelestialBody::winSize(400, 400);

CelestialBody::CelestialBody() : _radius(0.0), _xPosition(0.0), _yPosition(0.0), _xVelocity(0.0),
    _yVelocity(0.0), _mass(0.0), _fileName("") {
}

CelestialBody::CelestialBody(double radius, double xPosition,
double yPosition, double xVelocity, double yVelocity,
double mass, const std::string& fileName) :
    _radius(radius), _xPosition(xPosition), _yPosition(yPosition),
    _xVelocity(xVelocity), _yVelocity(yVelocity), _mass(mass),
    _fileName(fileName) {
    if (!loadTexture()) {
        std::cout << "Error, could not load file: " << fileName << std::endl;
    }
    float xOrigin = _xPosition * ((winSize.x / 2) / _radius) + (winSize.x / 2);
    float yOrigin = _yPosition * ((winSize.y / 2) / _radius) + (winSize.y / 2);
    Planet.setPosition(xOrigin, yOrigin);
}

bool CelestialBody::loadTexture() {
    if (image.loadFromFile(_fileName)) {
        texture.loadFromImage(image);
        Planet.setTexture(texture);

        Planet.setPosition(_xPosition, _yPosition);

        return true;
    }
    return false;
}

void CelestialBody::setXPosition(double xPosition) {
    _xPosition = xPosition;
}

void CelestialBody::setYPosition(double yPosition) {
    _yPosition = yPosition;
}

void CelestialBody::setRadius(double r) {
    _radius = r;
}

std::istream& operator>>(std::istream& istream, CelestialBody& body) {
    istream >> body._xPosition >> body._yPosition >>
    body._xVelocity >> body._yVelocity >> body._mass >> body._fileName;
    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const CelestialBody& body) {
    ostream << body.getXPosition() << " " << body.getYPosition() <<
     " " << body.getXVelocity() << " "
    << body.getYVelocity() << " " << body.getMass() << " " << body.getFileName() << std::endl;
    return ostream;
}

double CelestialBody::getXPosition() const {
    return _xPosition;
}

double CelestialBody::getYPosition() const {
    return _yPosition;
}

double CelestialBody::getXVelocity() const {
    return _xVelocity;
}

double CelestialBody::getYVelocity() const {
    return _yVelocity;
}

double CelestialBody::getMass() const {
    return _mass;
}

std::string CelestialBody::getFileName() const {
    return _fileName;
}

double CelestialBody::getRadius() const {
    return _radius;
}


void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(Planet, states);
}

void CelestialBody::setPosition(double x, double y) {
    _xPosition = x;
    _yPosition = y;
    double X = (x + _radius) / (2 * _radius) * 400;
    double Y = 400 - ((y + _radius) / (2 * _radius) * 400);
    Planet.setPosition(X, Y);
}
