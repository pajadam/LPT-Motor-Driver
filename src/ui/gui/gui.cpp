#include "gui.hpp"

graphic_ui::graphic_ui( Driver *_driver )
:ui( API::make_center(300, 225), appearance(true,true,true,false,true,false,false )	 )
,state(ui,      nana::rectangle(20,   STATE_HEIGHT + 5, 60, 30))
,state1(ui,     nana::rectangle(80,   STATE_HEIGHT, 100, 30))
,state2(ui,     nana::rectangle(190,  STATE_HEIGHT, 100, 30))

,dir(ui,        nana::rectangle(20,   DIRECTION_HEIGHT + 5, 60, 30) )
,direction1(ui, nana::rectangle(80,   DIRECTION_HEIGHT, 100, 30))
,direction2(ui, nana::rectangle(190,  DIRECTION_HEIGHT, 100, 30))

,speed(ui,      nana::rectangle(20,   SPEED_HEIGHT + 5, 60, 30))
,speed1(ui,     nana::rectangle(115,  SPEED_HEIGHT + 40, 60, 30))
,speed2(ui,     nana::rectangle(205,  SPEED_HEIGHT + 40, 60, 30))

,slid1(ui,      nana::rectangle(80,   SPEED_HEIGHT, 30, 100))
,sless1(ui,     nana::rectangle(112,   SPEED_HEIGHT + 70, 30, 30))
,smore1(ui,     nana::rectangle(112,   SPEED_HEIGHT, 30, 30))

,slid2(ui,      nana::rectangle(255,  SPEED_HEIGHT, 30, 100))
,sless2(ui,     nana::rectangle(222,   SPEED_HEIGHT + 70, 30, 30))
,smore2(ui,     nana::rectangle(222,   SPEED_HEIGHT, 30, 30))

,engine1(ui,    nana::rectangle(90,   ENGINE_HEIGHT, 70, 20))
,engine2(ui,    nana::rectangle(200,  ENGINE_HEIGHT, 70, 20))
{
    driver = _driver;

    ui.caption( TITLE );

    paint::image icon("data/icon.ico");
    API::window_icon( ui, icon );


    state1.caption( STATE_OFF );
    state2.caption( STATE_OFF );
    direction1.caption( CAP_RIGHT );
    direction2.caption( CAP_RIGHT );

    sless1.caption( "-" );
    sless2.caption( "-" );
    smore1.caption( "+" );
    smore2.caption( "+" );

    dir.caption(   "Direction: " );
    speed.caption( "     Speed: " );
    state.caption( "     State: " );
    engine1.caption( MOTOR1 );
    engine2.caption( MOTOR2 );
    slid1.vmax( MAX_SPEED );
    slid2.vmax( MAX_SPEED );
    slid1.vertical( true );
    slid2.vertical( true );
    slid1.value( (MAX_SPEED + 1) - DEFAULT_TIMESTEP );
    slid2.value( (MAX_SPEED + 1) - DEFAULT_TIMESTEP );
    speed1.caption( to_string( DEFAULT_TIMESTEP ) + " [ms]" );
    speed2.caption( to_string( DEFAULT_TIMESTEP ) + " [ms]" );

    ui.events().key_press(
        [&]( const nana::arg_keyboard &keyboard )
        {
            if( keyboard.key == 65 )
            {
                motor[ FIRST ].turnedOn = true;
                state1.caption( STATE_ON );
                driver->setMotor( FIRST, motor[ FIRST ] );
            }else
            if( keyboard.key == 68 )
            {
                motor[ SECOND ].turnedOn = true;
                state2.caption( STATE_ON );
                driver->setMotor( SECOND, motor[ SECOND ] );
            }
        }
    );

    ui.events().key_release(
        [&]( const nana::arg_keyboard &keyboard )
        {
            std::cout << "KEY: "<< keyboard.key << std::endl;
            if( keyboard.key == 65 )
            {
                motor[ FIRST ].turnedOn = false;
                state1.caption( STATE_OFF );
                driver->setMotor( FIRST, motor[ FIRST ] );
            }else
            if( keyboard.key == 68 )
            {
                motor[ SECOND ].turnedOn = false;
                state2.caption( STATE_OFF );
                driver->setMotor( SECOND, motor[ SECOND ] );
            }
        }
    );

    /// MORE LESS #1
    smore1.events().click(
        [&]()
        {
            slid1.move_step( false );

            motor[ FIRST ].timestep = sf::milliseconds( (MAX_SPEED + 1) - slid1.value() );

            speed1.caption( to_string( (MAX_SPEED + 1) - slid1.value()) + " [ms]"  );

            driver->setMotor( FIRST, motor[ FIRST ] );
        }
    );
    sless1.events().click(
        [&]()
        {
            slid1.move_step( true );

            motor[ FIRST ].timestep = sf::milliseconds( (MAX_SPEED + 1) - slid1.value() );

            speed1.caption( to_string( (MAX_SPEED + 1) - slid1.value()) + " [ms]"  );

            driver->setMotor( FIRST, motor[ FIRST ] );
        }
    );
    smore2.events().click(
        [&]()
        {
            slid2.move_step( false );

            motor[ SECOND ].timestep = sf::milliseconds( (MAX_SPEED + 1) - slid2.value() );

            speed2.caption( to_string( (MAX_SPEED + 1) - slid2.value()) + " [ms]"  );

            driver->setMotor( SECOND, motor[ SECOND ] );
        }
    );
    sless2.events().click(
        [&]()
        {
            slid2.move_step( true );

            motor[ SECOND ].timestep = sf::milliseconds( (MAX_SPEED + 1) - slid2.value() );

            speed2.caption( to_string( (MAX_SPEED + 1) - slid2.value()) + " [ms]"  );

            driver->setMotor( SECOND, motor[ SECOND ] );
        }
    );
    ///
    /// STATE BUTTON #1
    state1.events().click(
        [&]()
        {
            motor[ FIRST ].turnedOn = !motor[ FIRST ].turnedOn;
            if( motor[ FIRST ].turnedOn == true )
                state1.caption( STATE_ON );
            else
                state1.caption( STATE_OFF );

            driver->setMotor( FIRST, motor[ FIRST ] );
        }
    );
    ///
    /// STATE BUTTON #2
    state2.events().click(
        [&]()
        {
            motor[ SECOND ].turnedOn = !motor[ SECOND ].turnedOn;
            if( motor[ SECOND ].turnedOn == true )
                state2.caption( STATE_ON );
            else
                state2.caption( STATE_OFF );

            driver->setMotor( SECOND, motor[ SECOND ] );
        }
    );
    ///
    /// DIRECTION BUTTON #1
    direction1.events().click(
        [&]()
        {
            motor[ FIRST ].direction = !motor[ FIRST ].direction;
            if( motor[ FIRST ].direction == LEFT )
                direction1.caption( CAP_LEFT );
            else
                direction1.caption( CAP_RIGHT );

            driver->setMotor( FIRST, motor[ FIRST ] );
        }
    );
    ///
    /// DIRECTION BUTTON #2
    direction2.events().click(
        [&]()
        {
            motor[ SECOND ].direction = !motor[ SECOND ].direction;
            if( motor[ SECOND ].direction == LEFT )
                direction2.caption( CAP_LEFT );
            else
                direction2.caption( CAP_RIGHT );

            driver->setMotor( SECOND, motor[ SECOND ] );
        }
    );
    ///
    /// SLIDER #1
    slid1.events().value_changed(
        [&](){
            motor[ FIRST ].timestep = sf::milliseconds( (MAX_SPEED + 1) - slid1.value() );

            speed1.caption( to_string( (MAX_SPEED + 1) - slid1.value()) + " [ms]"  );

            driver->setMotor( FIRST, motor[ FIRST ] );
        }
    );
    ///
    /// SLIDER #2
    slid2.events().value_changed(
        [&](){
            motor[ SECOND ].timestep = sf::milliseconds( (MAX_SPEED + 1) - slid2.value() );

            speed2.caption( to_string( (MAX_SPEED + 1) - slid2.value()) + " [ms]"  );

            driver->setMotor( SECOND, motor[ SECOND ] );
        }
    );
    ///
}

void graphic_ui::loop()
{
    ui.show();
    exec();
}
