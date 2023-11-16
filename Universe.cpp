/*Copyright 2023 Brandon Nguyen*/
#include <iomanip>
#include <string>
#include <cmath>
#include "Universe.hpp"
#include "Solar.hpp"

Universe::Universe() : numBodies(0), radiusU(0.0) {
}

int Universe::getNumBodies() const {
    return numBodies;
}

double Universe::getRadiusU() const {
    return radiusU;
}

std::shared_ptr<CelestialBody> readCelestialBodyFromStream(std::istream& istream, double radiusU) {
    double xPosition, yPosition, xVelocity, yVelocity, mass;
    std::string planetName;

    istream >> xPosition >> yPosition >> xVelocity >> yVelocity >> mass >> planetName;

    std::shared_ptr<CelestialBody> celest = std::make_shared<CelestialBody>(radiusU,
    xPosition, yPosition, xVelocity, yVelocity, mass, planetName);
    celest->setRadius(radiusU);

    return celest;
}

std::istream& operator>>(std::istream& istream, Universe &uni) {
    istream >> uni.numBodies;
    istream >> uni.radiusU;

    for (int i = 0; i < uni.numBodies; i++) {
        std::shared_ptr<CelestialBody> celest = readCelestialBodyFromStream(istream,
        uni.radiusU);
        uni.addCelestialBody(celest);
    }

    return istream;
}

std::ostream& operator<<(std::ostream& out, const Universe& uni) {
    out << uni.getNumBodies() << std::endl;
    out << uni.getRadiusU() << std::endl;
    uni.printCelestialBodies(out);
    return out;
}

double Universe::getXLength(CelestialBody &plan, CelestialBody &other) {
    return (other.getXPosition() - plan.getXPosition());
}

double Universe::getYLength(CelestialBody &plan, CelestialBody &other) {
    return (other.getYPosition() - plan.getYPosition());
}

double Universe::getRLength(CelestialBody &plan, CelestialBody &other) {
    double xDist, yDist, rDist;
    xDist = getXLength(plan, other);
    yDist = getYLength(plan, other);
    rDist = sqrt((xDist * xDist) + (yDist * yDist));
    return rDist;
}


double Universe::Force(CelestialBody &plan, CelestialBody &other) {
    double rDist = getRLength(plan, other);
    double force = ((6.674e-11 * ((plan.getMass() * other.getMass())) / (rDist * rDist)));
    return force;
}

void Universe::step(double seconds) {
    for (int i = 0; i < getNumBodies(); i++) {
        double accelX = 0, accelY = 0;
        const CelestialBody& currentBody = *getPlanet(i);

        for (int j = 0; j < getNumBodies(); j++) {
            if (j != i) {
                double force = Force(*getPlanet(i), *getPlanet(j));
                double xDist = getXLength(*getPlanet(i), *getPlanet(j));
                double yDist = getYLength(*getPlanet(i), *getPlanet(j));
                double rDist = getRLength(*getPlanet(i), *getPlanet(j));
                accelX += force * (xDist / rDist) / currentBody.getMass();
                accelY += force * (yDist / rDist) / currentBody.getMass();
            }
        }
        double newVeloX = currentBody.getXVelocity() + accelX * seconds;
        double newVeloY = currentBody.getYVelocity() + accelY * seconds;
        getPlanet(i)->setVelocities(newVeloX, newVeloY);
    }

    for (int k = 0; k < getNumBodies(); k++) {
        CelestialBody& body = *getPlanet(k);
        double newXV = body.getXPosition() + (seconds * body.getXVelocity());
        double newYV = body.getYPosition() + (seconds * body.getYVelocity());
        body.setPosition(newXV, newYV);
    }
}
