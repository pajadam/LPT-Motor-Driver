#ifndef GUI_HPP
#define GUI_HPP

#include "../../driver/driver.hpp"
#include "../ui.hpp"

#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <iostream>

#define TITLE     "LPT Motor Driver"
#define EXIT      "Exit"
#define MOTOR1    "  Engine #1"
#define MOTOR2    "  Engine #2"
#define SPEED     "Speed"
#define STATE_ON  "ON"
#define STATE_OFF "OFF"
#define CAP_LEFT  "Left"
#define CAP_RIGHT "Right"

#define DIRECTION_HEIGHT 70
#define STATE_HEIGHT 30
#define ENGINE_HEIGHT 10
#define SPEED_HEIGHT 110

#define MAX_SPEED 499

using namespace nana;

class graphic_ui : public ui
{
public:
    graphic_ui( Driver *_driver );

private:
    void loop();
    form ui;

    button state1,
           state2,
           direction1,
           direction2,
           sless1,
           sless2,
           smore1,
           smore2;
    label  state,
           dir,
           speed,
           engine1,
           engine2,
           speed1,
           speed2;
    slider slid1,
           slid2;

};

#endif // GUI_HPP
