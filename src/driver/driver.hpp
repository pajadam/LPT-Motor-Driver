#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <windows.h>
#include <mutex>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#define port 0x378

#define FIRST 0
#define SECOND 1

#define LEFT 0
#define RIGHT 1

#define DEFAULT_DIRECTION RIGHT
#define DEFAULT_TIMESTEP 10
#define DEFAULT_STATE 0

using namespace std;

typedef short _stdcall (*inpfuncPtr)(short portaddr);
typedef void _stdcall (*oupfuncPtr)(short portaddr, short datum);

struct Motor
{
    sf::Time timestep;
    bool direction;
    bool turnedOn;
};

class Driver
{
public:
    Driver();
    ~Driver();

    void Loop(); // Driver Loop
                 // id = FIRST || SECOND
    void setMotor( bool id, Motor _motor );
    void Exit(); // Set Exit flag
    Motor getMotor( bool id );
private:
    void process();

    HINSTANCE hLib;
    inpfuncPtr in;
    oupfuncPtr out;

    int steps[16] = { 1, 3, 2, 6, 4, 12,  8,  9,
                     16,48,32,96,64,192,128,144 };
    int  driver_step[2] = { 0, 0 };
    bool update = false;
    bool exit = false;

    Motor motor[2];

    sf::Time timeSinceLastUpdate[2];
    sf::Clock clock;

    std::mutex driver_mutex;
};

#endif // DRIVER_HPP
