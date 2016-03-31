#include "driver.hpp"

Motor Driver::getMotor( bool id )
{
    driver_mutex.lock();
        Motor _motor = motor[id];
    driver_mutex.unlock();

    return _motor;
}

void Driver::setMotor( bool id, Motor _motor )
{
    driver_mutex.lock();
        motor[id] = _motor;
    driver_mutex.unlock();
}

void Driver::Exit()
{
    driver_mutex.lock();
    exit = true;
    driver_mutex.unlock();
}
