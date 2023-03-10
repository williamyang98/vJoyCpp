#pragma once
#include "vjoy.hpp"

class Controller 
{
private:
    struct axis_bounds {
        int32_t min;
        int32_t max;
        int32_t center;
    };
public:
    const vjoy::Device_ID rid;
    const axis_bounds axis_x; 
    const axis_bounds axis_y; 
    const axis_bounds axis_z; 
    const axis_bounds axis_rx;
    const axis_bounds axis_ry;
    const axis_bounds axis_rz;
    const axis_bounds axis_slider;
    const axis_bounds axis_dial;
    const axis_bounds axis_wheel;
    const axis_bounds axis_accelerator;
    const axis_bounds axis_brake;
    const axis_bounds axis_clutch;
    const axis_bounds axis_steering;
    const axis_bounds axis_rudder;
    const axis_bounds axis_aileron;
    const axis_bounds axis_throttle;
    const int total_buttons;
private:
    vjoy::Joystick_Position state;
public:
    Controller(const vjoy::Device_ID _rid)
    :   rid(_rid),
        axis_x          (update_axis_bounds(vjoy::Axis::X)),
        axis_y          (update_axis_bounds(vjoy::Axis::Y)),
        axis_z          (update_axis_bounds(vjoy::Axis::Z)),
        axis_rx         (update_axis_bounds(vjoy::Axis::RX)),
        axis_ry         (update_axis_bounds(vjoy::Axis::RY)),
        axis_rz         (update_axis_bounds(vjoy::Axis::RZ)),
        axis_slider     (update_axis_bounds(vjoy::Axis::SLIDER)),
        axis_dial       (update_axis_bounds(vjoy::Axis::DIAL)),
        axis_wheel      (update_axis_bounds(vjoy::Axis::WHEEL)),
        axis_accelerator(update_axis_bounds(vjoy::Axis::ACCELERATOR)),
        axis_brake      (update_axis_bounds(vjoy::Axis::BRAKE)),
        axis_clutch     (update_axis_bounds(vjoy::Axis::CLUTCH)),
        axis_steering   (update_axis_bounds(vjoy::Axis::STEERING)),
        axis_rudder     (update_axis_bounds(vjoy::Axis::RUDDER)),
        axis_aileron    (update_axis_bounds(vjoy::Axis::AILERON)),
        axis_throttle   (update_axis_bounds(vjoy::Axis::THROTTLE)),
        total_buttons(vjoy::device_get_total_buttons(rid))
    {
        reset();
        update();
    }

    void reset() {
        state.bDevice = 0;
        state.wThrottle = axis_throttle.center;
        state.wRudder = axis_rudder.center;
        state.wAileron = axis_aileron.center;
        state.wAxisX = axis_x.center;
        state.wAxisY = axis_y.center;
        state.wAxisZ = axis_z.center;
        state.wAxisXRot = axis_rx.center;
        state.wAxisYRot = axis_ry.center;
        state.wAxisZRot = axis_rz.center;
        state.wSlider = axis_slider.center;
        state.wDial = axis_dial.center;
        state.wWheel = axis_wheel.center;
        state.wAccelerator = axis_accelerator.center;
        state.wBrake = axis_brake.center; 
        state.wClutch = axis_clutch.center;
        state.wSteering = axis_steering.center;
        state.wAxisVX = 0;
        state.wAxisVY = 0;
        state.lButtons = 0;
        state.bHats = 0;
        state.bHatsEx1 = 0;
        state.bHatsEx2 = 0;
        state.bHatsEx3 = 0;
        state.wAxisVZ = 0;
        state.wAxisVBRX = 0;
        state.wAxisVBRY = 0;
        state.wAxisVBRZ = 0;
    }

    void update() {
        vjoy::device_update(rid, &state);
    }

    void set_x(const int32_t v) { state.wAxisX = v; }
    void set_y(const int32_t v) { state.wAxisY = v; }
    void set_z(const int32_t v) { state.wAxisZ = v; }
    void set_rx(const int32_t v) { state.wAxisXRot = v; }
    void set_ry(const int32_t v) { state.wAxisYRot = v; }
    void set_rz(const int32_t v) { state.wAxisZRot = v; }
    void set_slider(const int32_t v) { state.wSlider = v; }
    void set_dial(const int32_t v) { state.wDial = v; }
    void set_wheel(const int32_t v) { state.wWheel = v; }
    void set_accelerator(const int32_t v) { state.wWheel = v; }
    void set_brake(const int32_t v) { state.wBrake = v; }
    void set_clutch(const int32_t v) { state.wClutch = v; }
    void set_steering(const int32_t v) { state.wSteering = v; }
    void set_rudder(const int32_t v) { state.wRudder = v; }
    void set_aileron(const int32_t v) { state.wAileron = v; }
    void set_throttle(const int32_t v) { state.wThrottle = v; }
    void set_button(const uint8_t index, const bool is_pressed) {
        if (index < 32)  return set_button_x(index,    is_pressed, state.lButtons);
        if (index < 64)  return set_button_x(index-32, is_pressed, state.lButtonsEx1);
        if (index < 96)  return set_button_x(index-64, is_pressed, state.lButtonsEx2);
        if (index < 128) return set_button_x(index-96, is_pressed, state.lButtonsEx3);
    }
private:
    axis_bounds update_axis_bounds(vjoy::Axis vjd_axis) {
        axis_bounds axis;
        vjoy::device_get_axis_min(rid, vjd_axis, &axis.min);
        vjoy::device_get_axis_max(rid, vjd_axis, &axis.max);
        axis.center = (axis.min + axis.max)/2;
        return axis;
    }
    void set_button_x(const uint8_t v, const bool is_pressed, uint32_t& reg) {
        const uint32_t mask = uint32_t(1) << v;
        if (is_pressed) {
            reg |=  mask;
        } else {
            reg &= ~mask;
        }
    }
};
