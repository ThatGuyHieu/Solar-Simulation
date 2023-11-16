
/*Copyright 2023 Brandon Nguyen*/
#pragma once
#include <vector>
#include <iomanip>
#include <memory>
#include "Solar.hpp"
#include <SFML/Graphics.hpp>

class Universe{
 public:
    Universe();

    int getNumBodies() const;
    double getRadiusU() const;

    const std::shared_ptr<CelestialBody>& getPlanet(unsigned int index) const {
        return planet[index];
    }

    void addCelestialBody(std::shared_ptr<CelestialBody> celest) {
       planet.push_back(celest);
    }

    void step(double seconds);
    double Force(CelestialBody &plan, CelestialBody &other);
    double getXLength(CelestialBody &plan, CelestialBody &other);
    double getYLength(CelestialBody &plan, CelestialBody &other);
    double getRLength(CelestialBody &plan, CelestialBody &other);

    void printCelestialBodies(std::ostream& out) const {
        for (int i = 0; i < numBodies; i++) {
            const std::shared_ptr<CelestialBody>& temp = planet[i];
            const CelestialBody& celest = *temp;
            out << std::setw(15) << celest.getXPosition() << std::setw(15) << celest.getYPosition()
                << std::setw(15) << celest.getXVelocity() << std::setw(15) << celest.getYVelocity()
                << std::setw(15) << celest.getMass() <<
                std::setw(15) << celest.getFileName() << std::endl;
        }
    }

    friend std::istream& operator>>(std::istream& istream, Universe &uni);
    friend std::ostream& operator<<(std::ostream& ostream, const Universe &uni);

 private:
    int numBodies;
    double radiusU;
    std::vector<std::shared_ptr<CelestialBody>> planet;
};
