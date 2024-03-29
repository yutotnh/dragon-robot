#include "Digital_PWM_TB6643.h"
#include "mbed.h"
#include "Motor.h"

DP_TB6643::DP_TB6643(PinName IN1, PinName IN2)
    : _IN1(IN1), _IN2(IN2)
{
    _IN2.period(0.0001);

    _duty_cycle = 0.0f;
    _state = State::Brake;
    set();
}

int DP_TB6643::set()
{
    switch (get_state())
    {
    case State::Free:
        _IN1 = 0, _IN2 = 0;
        break;
    case State::CW:
        _IN1 = 1, _IN2 = 0;
        break;
    case State::CCW:
        _IN1 = 0, _IN2 = get_duty_cycle();
        break;
    case State::Brake:
        _IN1 = 1, _IN2 = 1.0f;
        break;
    default:
        break;
    }

    return 1;
}
