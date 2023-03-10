#include "vjoy.hpp"
#include "Controller.hpp"
#include <stdio.h>
#include <stdint.h>
#include <thread>
#include <chrono>
#include <random>

void convert_utf16_to_ascii(const char16_t* src, char* dst, const int N) {
    constexpr char16_t ASCII_MASK = 0x007F;
    for (int i = 0; i < N; i++) {
        dst[i] = char(src[i] & ASCII_MASK);
        if (dst[i] == 0x00) break;
    }
    dst[N-1] = 0x00;
}

void vjoy_api_print_info(void);
void vjoy_device_print_info(const vjoy::Device_Info& info);
void test_controller(Controller& controller);

class ScopedDeviceRelease 
{
private:
    const vjoy::Device_ID rid;
public:
    ScopedDeviceRelease(const vjoy::Device_ID _rid): rid(_rid) {}
    ~ScopedDeviceRelease() {
        vjoy::device_release(rid);
    }
};

// This program just randomly changes the device controls
// Open vJoyConf.exe to setup device with appropriate settings 
int main(int argc, char** argv) {
    const vjoy::Device_ID rid = 1;

    if (!vjoy::api_is_enabled()) {
        printf("vjoy is not enabled\n");
        return 1;
    }
    vjoy_api_print_info();

    if (!vjoy::device_is_exists(rid)) {
        printf("Device %u doesn't exist\n", rid);
        return 1;
    }

    if (!vjoy::device_acquire(rid)) {
        const int pid = vjoy::device_get_owner_pid(rid);
        printf("Unable to acquire device %u since in use by pid=%d\n", rid, pid);
        return 1;
    }
    auto scoped_release = ScopedDeviceRelease(rid);

    const auto device_info = vjoy::device_get_info(rid);
    vjoy_device_print_info(device_info);

    std::srand(0);
    auto controller = Controller(rid);
    test_controller(controller);

    return 0;
}

void vjoy_api_print_info(void) {
    const uint16_t version_number = vjoy::api_get_version();
    const char16_t* product_str = vjoy::api_get_product_string();
    const char16_t* manufacturer_str = vjoy::api_get_manufacturer_string();
    const char16_t* serial_number_str = vjoy::api_get_serial_number_string();
    int total_existing_devices = 0;
    int max_total_devices = 0;
    vjoy::api_get_total_existing_devices(&total_existing_devices);
    vjoy::api_get_max_total_devices(&max_total_devices);

    // We need to convert utf16 to ascii
    constexpr int N = 64;
    char buf[N];

    printf("Version Number:  0x%04X\n", version_number);
    convert_utf16_to_ascii(product_str, buf, N);
    printf("Product ID:      '%s'\n", buf);
    convert_utf16_to_ascii(manufacturer_str, buf, N);
    printf("Manufacturer ID: '%s'\n", buf);
    convert_utf16_to_ascii(serial_number_str, buf, N);
    printf("Serial Number:   '%s'\n", buf);
    printf("Total devices:   %d/%d\n", total_existing_devices, max_total_devices);
}

void vjoy_device_print_info(const vjoy::Device_Info& info) {
    printf("AxisX           : %u\n", info.AxisX);
    printf("AxisY           : %u\n", info.AxisY);
    printf("AxisZ           : %u\n", info.AxisZ);
    printf("AxisXRot        : %u\n", info.AxisXRot);
    printf("AxisYRot        : %u\n", info.AxisYRot);
    printf("AxisZRot        : %u\n", info.AxisZRot);
    printf("Slider          : %u\n", info.Slider);
    printf("Dial            : %u\n", info.Dial);
    printf("Wheel           : %u\n", info.Wheel);
    printf("Accelerator     : %u\n", info.Accelerator);
    printf("Brake           : %u\n", info.Brake);
    printf("Clutch          : %u\n", info.Clutch);
    printf("Steering        : %u\n", info.Steering);
    printf("Aileron         : %u\n", info.Aileron);
    printf("Rudder          : %u\n", info.Rudder);
    printf("Throttle        : %u\n", info.Throttle);
    printf("Total Buttons   : %d\n", info.nButtons);
    printf("Discrete Hats   : %d\n", info.nDiscHats);
    printf("Continuous Hats : %d\n", info.nContHats);
}

void test_controller(Controller& controller) {
    const int32_t update_rate = 20;
    const int32_t axis_value_min = controller.axis_rx.min;
    const int32_t axis_value_max = controller.axis_rx.max;
    const int32_t axis_value_step = (axis_value_max-axis_value_min)/update_rate;
    int32_t axis_value = axis_value_min;
    int32_t axis_value_delta = axis_value_step;

    while (true) {
        const auto sleep_duration = std::chrono::milliseconds(1000/update_rate);
        std::this_thread::sleep_for(sleep_duration);

        // Spam buttons randomly
        for (int i = 0; i < controller.total_buttons; i++) {
            const bool is_pressed = (std::rand() % 2) == 0;
            controller.set_button(i, is_pressed);
        }

        // Slide the axes up and down
        controller.set_x(axis_value);
        controller.set_y(axis_value);
        controller.set_z(axis_value);
        controller.set_rx(axis_value);
        controller.set_ry(axis_value);
        controller.set_rz(axis_value);
        controller.set_slider(axis_value);
        controller.set_dial(axis_value);
        controller.set_wheel(axis_value);
        controller.set_accelerator(axis_value);
        controller.set_brake(axis_value);
        controller.set_clutch(axis_value);
        controller.set_steering(axis_value);
        controller.set_rudder(axis_value);
        controller.set_aileron(axis_value);
        controller.set_throttle(axis_value);
        controller.update();

        axis_value += axis_value_delta;
        if (axis_value > axis_value_max) {
            axis_value = axis_value_max;
            axis_value_delta = -axis_value_step;
        } else if (axis_value < axis_value_min) {
            axis_value = axis_value_min;
            axis_value_delta = +axis_value_step;
        }
    }

}