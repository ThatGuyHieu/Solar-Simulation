CC = g++
CFLAGS = -Wall -Wextra -std=c++17
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
BOOST_FLAGS = -lboost_unit_test_framework
OBJECTS = CelestialBody.o Universe.o main.o
TEST_OBJECTS = CelestialBody.o Universe.o test.o

all: NBody NBody.a

NBody: $(OBJECTS)
	$(CC) $(CFLAGS) -o NBody $(OBJECTS) $(SFML_FLAGS)

NBody.a: CelestialBody.o Universe.o main.o
	ar rcs NBody.a CelestialBody.o Universe.o main.o

CelestialBody.o: CelestialBody.cpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c CelestialBody.cpp

Universe.o: Universe.cpp Universe.hpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c Universe.cpp

main.o: main.cpp Universe.hpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c main.cpp

lint:
	cpplint --filter=-build/include_what_you_use *.cpp *.hpp

clean:
	rm NBody *.o *.a
