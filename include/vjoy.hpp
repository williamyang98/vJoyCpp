#pragma once
#include <stdint.h>

// For 2.2.1 of vjoy API
namespace vjoy 
{

using Device_ID = uint32_t;

// DOC: docs/vjoy_manual.odt
// vjoy uses a subset of winerror.h error codes
enum class Error: uint32_t {
    SUCCESS             = 0x0, 
    INVALID_DATA        = 0xD,
    INVALID_PARAMETER   = 0x57,
};

enum class Device_Status: uint32_t {
    OWN  = 0,    // The vJoy Device is owned by this application.
    FREE = 1,    // The vJoy Device is NOT owned by any application (including this one).
    BUSY = 2,    // The vJoy Device is owned by another application. It cannot be acquired by this application.
    MISS = 3,    // The vJoy Device is missing. It either does not exist or the driver is down.
    UNKN = 4    // Unknown
}; 

enum class Axis: uint32_t {
    X           = 0x30,
    Y           = 0x31,
    Z           = 0x32,
    RX          = 0x33,
    RY          = 0x34,
    RZ          = 0x35,
    SLIDER      = 0x36,
    DIAL        = 0x37,
    WHEEL       = 0x38,
    // POV         = 0x39,
    ACCELERATOR = 0xC4,
    BRAKE       = 0xC5,
    CLUTCH      = 0xC6,
    STEERING    = 0xC8,
    AILERON     = 0xB0,
    RUDDER      = 0xBA,
    THROTTLE    = 0xBB,
};

struct Joystick_Position_V1 {
    uint8_t  bDevice;     // Index of device. 1-based.
    int32_t  wThrottle;
    int32_t  wRudder;
    int32_t  wAileron;
    int32_t  wAxisX;
    int32_t  wAxisY;
    int32_t  wAxisZ;
    int32_t  wAxisXRot;
    int32_t  wAxisYRot;
    int32_t  wAxisZRot;
    int32_t  wSlider;
    int32_t  wDial;
    int32_t  wWheel;
    int32_t  wAxisVX;
    int32_t  wAxisVY;
    int32_t  wAxisVZ;
    int32_t  wAxisVBRX;
    int32_t  wAxisVBRY;
    int32_t  wAxisVBRZ;
    uint32_t lButtons;    // 32 buttons: 0x00000001 means button1 is pressed, 0x80000000 -> button32 is pressed
    uint32_t bHats;       // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    uint32_t bHatsEx1;    // 16-bit of continuous HAT switch
    uint32_t bHatsEx2;    // 16-bit of continuous HAT switch
    uint32_t bHatsEx3;    // 16-bit of continuous HAT switch
};

struct Joystick_Position_V2 {
    uint8_t  bDevice;       // Index of device. 1-based.
    int32_t  wThrottle;
    int32_t  wRudder;
    int32_t  wAileron;
    int32_t  wAxisX;
    int32_t  wAxisY;
    int32_t  wAxisZ;
    int32_t  wAxisXRot;
    int32_t  wAxisYRot;
    int32_t  wAxisZRot;
    int32_t  wSlider;
    int32_t  wDial;
    int32_t  wWheel;
    int32_t  wAxisVX;
    int32_t  wAxisVY;
    int32_t  wAxisVZ;
    int32_t  wAxisVBRX;
    int32_t  wAxisVBRY;
    int32_t  wAxisVBRZ;
    uint32_t lButtons;      // 32 buttons: 0x00000001 means button1 is pressed, 0x80000000 -> button32 is pressed
    uint32_t bHats;         // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    uint32_t bHatsEx1;      // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    uint32_t bHatsEx2;      // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    uint32_t bHatsEx3;      // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    // JOYSTICK_POSITION_V2 Extensions
    uint32_t lButtonsEx1;   // Buttons 33-64
    uint32_t lButtonsEx2;   // Buttons 65-96
    uint32_t lButtonsEx3;   // Buttons 97-128
};

struct Joystick_Position_V3 {
    uint8_t  bDevice;       // Index of device. 1-based.
    int32_t  wThrottle;
    int32_t  wRudder;
    int32_t  wAileron;
    int32_t  wAxisX;
    int32_t  wAxisY;
    int32_t  wAxisZ;
    int32_t  wAxisXRot;
    int32_t  wAxisYRot;
    int32_t  wAxisZRot;
    int32_t  wSlider;
    int32_t  wDial;
    int32_t  wWheel;
    int32_t  wAccelerator;
    int32_t  wBrake;
    int32_t  wClutch;
    int32_t  wSteering;
    int32_t  wAxisVX;
    int32_t  wAxisVY;
    uint32_t lButtons;      // 32 buttons: 0x00000001 means button1 is pressed, 0x80000000 -> button32 is pressed
    uint32_t bHats;         // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    uint32_t bHatsEx1;      // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    uint32_t bHatsEx2;      // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    uint32_t bHatsEx3;      // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    // JOYSTICK_POSITION_V2 Extensions
    uint32_t lButtonsEx1;   // Buttons 33-64
    uint32_t lButtonsEx2;   // Buttons 65-96
    uint32_t lButtonsEx3;   // Buttons 97-128
    // JOYSTICK_POSITION_V3 Extensions: Replacing old slots and moving them to the tail
    int32_t  wAxisVZ;
    int32_t  wAxisVBRX;
    int32_t  wAxisVBRY;
    int32_t  wAxisVBRZ;
};

// Device Axis/POVs/Buttons
struct Device_Info {
    bool AxisX;
    bool AxisY;
    bool AxisZ;
    bool AxisXRot;
    bool AxisYRot;
    bool AxisZRot;
    bool Slider;
    bool Dial;
    bool Wheel;
    bool Accelerator;
    bool Brake;
    bool Clutch;
    bool Steering;
    bool Rudder;
    bool Aileron;
    bool Throttle;
    int  nButtons;    
    int  nDiscHats;
    int  nContHats;
};

// FFB Effect Type
enum class FFB_Effect_Type: uint32_t {
    NONE  = 0,              // No Force
    CONST = 1,              // Constant Force
    RAMP  = 2,              // Ramp
    SQR   = 3,              // Square
    SINE  = 4,              // Sine
    TRNGL = 5,              // Triangle
    STUP  = 6,              // Sawtooth Up
    STDN  = 7,              // Sawtooth Down
    SPRNG = 8,              // Spring
    DMPR  = 9,              // Damper
    INRT  = 10,             // Inertia
    FRCTN = 11,             // Friction
    CSTM  = 12,             // Custom Force Data
};

enum class FFB_Effect: uint32_t {
    CONST    = 0x26,        // Usage ET Constant Force
    RAMP     = 0x27,        // Usage ET Ramp
    SQUR     = 0x30,        // Usage ET Square
    SINE     = 0x31,        // Usage ET Sine
    TRNG     = 0x32,        // Usage ET Triangle
    STUP     = 0x33,        // Usage ET Sawtooth Up
    STDN     = 0x34,        // Usage ET Sawtooth Down
    SPRNG    = 0x40,        // Usage ET Spring
    DMPR     = 0x41,        // Usage ET Damper
    INRT     = 0x42,        // Usage ET Inertia
    FRIC     = 0x43,        // Usage ET Friction
    CUSTOM   = 0x28,        // Usage ET Custom Force Data
    RESERVED = 0x28,        // Usage ET Reserved
};

// FFB Packet Type
enum class FFB_Packet_Type: uint32_t {
    EFFREP      = 0x01,     // Usage Set Effect Report
    ENVREP      = 0x02,     // Usage Set Envelope Report
    CONDREP     = 0x03,     // Usage Set Condition Report
    PRIDREP     = 0x04,     // Usage Set Periodic Report
    CONSTREP    = 0x05,     // Usage Set Constant Force Report
    RAMPREP     = 0x06,     // Usage Set Ramp Force Report
    CSTMREP     = 0x07,     // Usage Custom Force Data Report
    SMPLREP     = 0x08,     // Usage Download Force Sample
    EFOPREP     = 0x0A,     // Usage Effect Operation Report
    BLKFRREP    = 0x0B,     // Usage PID Block Free Report
    CTRLREP     = 0x0C,     // Usage PID Device Control
    GAINREP     = 0x0D,     // Usage Device Gain Report
    SETCREP     = 0x0E,     // Usage Set Custom Force Report
    NEWEFREP    = 0x11,     // Usage Create New Effect Report
    BLKLDREP    = 0x12,     // Usage Block Load Report
    POOLREP     = 0x13,     // Usage PID Pool Report
    STATEREP    = 0x14,     // Usage PID State Report
};

enum class FFB_Operation: uint32_t {
    START = 1,              // EFFECT START
    SOLO  = 2,              // EFFECT SOLO START
    STOP  = 3,              // EFFECT STOP
};

enum class FFB_Control: uint32_t {
    ENACT    = 1,           // Enable all device actuators.
    DISACT   = 2,           // Disable all the device actuators.
    STOPALL  = 3,           // Stop All Effects Issues a stop on every running effect.
    DEVRST   = 4,           // Device Reset Clears any device paused condition, enables all actuators and clears all effects from memory.
    DEVPAUSE = 5,           // Device Pause The all effects on the device are paused at the current time step.
    DEVCONT  = 6,           // Device Continue The all effects that running when the device was paused are restarted from their last time step.
};

struct FFB_Data {
    uint32_t size;
    uint32_t cmd;
    uint8_t* data;
};

struct FFB_Effect_Constant { 
    uint8_t EffectBlockIndex; 
    int32_t Magnitude;              // Constant force magnitude:     -10000 - 10000
};

struct FFB_Effect_Ramp {
    uint8_t EffectBlockIndex;
    int32_t Start;                  // The Normalized magnitude at the start of the effect (-10000 - 10000)
    int32_t End;                    // The Normalized magnitude at the end of the effect    (-10000 - 10000)
};

struct FFB_Effect_Report {
    uint8_t EffectBlockIndex;
    FFB_Effect_Type EffectType;
    uint16_t Duration;              // Value in milliseconds. 0xFFFF means infinite
    uint16_t TrigerRpt;
    uint16_t SamplePrd;
    uint8_t Gain;
    uint8_t TrigerBtn;
    bool Polar;                     // How to interpret force direction Polar (0-360�) or Cartesian (X,Y)
    union
    {
        uint8_t Direction;          // Polar direction: (0x00-0xFF correspond to 0-360�)
        uint8_t DirX;               // X direction: Positive values are To the right of the center (X); Negative are Two's complement
    };
    uint8_t DirY;                   // Y direction: Positive values are below the center (Y); Negative are Two's complement
};

struct FFB_Effect_Operation {
    uint8_t EffectBlockIndex;
    FFB_Operation EffectOp;
    uint8_t LoopCount;
};

struct FFB_Effect_Period {
    uint8_t  EffectBlockIndex;
    uint32_t Magnitude;             // Range: 0...10000
    int32_t  Offset;                // Range: -10000...+10000
    uint32_t Phase;                 // Range: 0...35999
    uint32_t Period;                // Range: 0...32767
};

struct FFB_Effect_Condition {
    uint8_t  EffectBlockIndex;
    bool     isY;
    int32_t  CenterPointOffset;     // CP Offset:  Range -10000...+10000
    int32_t  PosCoeff;              // Positive Coefficient: Range -10000...+10000
    int32_t  NegCoeff;              // Negative Coefficient: Range -10000...+10000
    uint32_t PosSatur;              // Positive Saturation: Range 0...10000
    uint32_t NegSatur;              // Negative Saturation: Range 0...10000
    int32_t  DeadBand;              // Dead Band: : Range 0...1000
};

struct FFB_Effect_Envelope {
    uint8_t  EffectBlockIndex;
    uint32_t AttackLevel;           // The Normalized magnitude of the stating point: 0...10000
    uint32_t FadeLevel;             // The Normalized magnitude of the stopping point: 0...10000
    uint32_t AttackTime;            // Time of the attack: 0...4294967295
    uint32_t FadeTime;              // Time of the fading: 0...4294967295
};

// NOTE: This depends on the version of the api
using Joystick_Position = Joystick_Position_V3;
typedef void (*FFB_Generate_Callback)(FFB_Data*, void*);                        // Second parameter is a void* to user defined data of any type
typedef void (*Device_Remove_Callback)(bool, bool, void*);                      // Second parameter is a void* to user defined data of any type

// General driver data
bool api_is_enabled(void);
uint16_t api_get_version(void);
const char16_t* api_get_product_string(void);
const char16_t* api_get_manufacturer_string(void);
const char16_t* api_get_serial_number_string(void);
bool api_is_driver_match(uint16_t* DllVer, uint16_t* DrvVer);
void api_register_remove_callback(Device_Remove_Callback cb, void* user_data);
bool api_is_force_feedback_available(bool* Supported);                                  // Is this version of vJoy capable of FFB?
bool api_get_max_total_devices(int* n);                                                 // What is the maximum possible number of vJoy devices
bool api_get_total_existing_devices(int* n);                                            // What is the number of vJoy devices currently enabled
void api_reset_all_devices(void);                                                       // Reset all controls to predefined values in all VDJ
// vJoy Device properties
enum Device_Status device_get_status(Device_ID rID);                                    // Get the status of the specified vJoy Device.
int device_get_total_buttons        (Device_ID rID);                                    // Get the number of buttons defined in the specified VDJ
int device_get_total_discrete_POVs  (Device_ID rID);                                    // Get the number of descrete-type POV hats defined in the specified VDJ
int device_get_total_continuous_POVs(Device_ID rID);                                    // Get the number of descrete-type POV hats defined in the specified VDJ
bool device_get_axis_exists         (Device_ID rID, Axis Axis);                         // Test if given axis defined in the specified VDJ
bool device_get_axis_max            (Device_ID rID, Axis Axis, int32_t* Max);           // Get logical Maximum value for a given axis defined in the specified VDJ
bool device_get_axis_min            (Device_ID rID, Axis Axis, int32_t* Min);           // Get logical Minimum value for a given axis defined in the specified VDJ
bool device_is_exists               (Device_ID rID);                                    // TRUE if the specified vJoy Device exists                                                                            
int device_get_owner_pid            (Device_ID rID);                                    // Reurn owner's Process ID if the specified vJoy Device exists
bool device_acquire                 (Device_ID rID);                                    // Acquire the specified vJoy Device.
void device_release                 (Device_ID rID);                                    // Relinquish the specified vJoy Device.
bool device_update                  (Device_ID rID, Joystick_Position* pData);          // Update the position data of the specified vJoy Device.
bool device_reset                   (Device_ID rID);                                    // Reset all controls to predefined values in the specified VDJ
bool device_reset_buttons           (Device_ID rID);                                    // Reset all buttons (To 0) in the specified VDJ
bool device_reset_POVs              (Device_ID rID);                                    // Reset all POV Switches (To -1) in the specified VDJ
bool device_set_axis                (Device_ID rID, Axis Axis, int32_t Value);          // Write Value to a given axis defined in the specified VDJ 
bool device_set_button              (Device_ID rID, uint8_t nBtn, bool Value);          // Write Value to a given button defined in the specified VDJ 
bool device_set_discrete_POV        (Device_ID rID, uint8_t nPov, int Value);           // Write Value to a given descrete POV defined in the specified VDJ 
bool device_set_continuous_POV      (Device_ID rID, uint8_t nPov, uint32_t Value);      // Write Value to a given continuous POV defined in the specified VDJ 
bool device_ffb_start               (Device_ID rID);
void device_ffb_stop                (Device_ID rID);
bool device_is_ffb                  (Device_ID rID);
bool device_is_ffb_effect           (Device_ID rID, FFB_Effect Effect);
// Force Feedback (FFB) functions
FFB_Effect_Type ffb_get_effect(void);                                                   // Returns effect serial number if active, 0 if inactive
void ffb_register_generate_callback(FFB_Generate_Callback cb, void* user_data);            
Error ffb_get_device_id         (const FFB_Data* Packet, uint32_t* DeviceID);
Error ffb_get_packet_type       (const FFB_Data* Packet, FFB_Packet_Type* Type);
Error ffb_get_packet            (const FFB_Data* Packet, uint16_t* Type, uint32_t* DataSize, uint8_t* Data[]);
Error ffb_get_effect_block_index(const FFB_Data* Packet, uint32_t* Index);
Error ffb_get_effect_report     (const FFB_Data* Packet, FFB_Effect_Report* Effect);
Error ffb_get_effect_ramp       (const FFB_Data* Packet, FFB_Effect_Ramp* RampEffect);
Error ffb_get_effect_operation  (const FFB_Data* Packet, FFB_Effect_Operation* Operation);
Error ffb_get_effect_period     (const FFB_Data* Packet, FFB_Effect_Period* Effect);
Error ffb_get_effect_condition  (const FFB_Data* Packet, FFB_Effect_Condition* Condition);
Error ffb_get_effect_envelope   (const FFB_Data* Packet, FFB_Effect_Envelope* Envelope);
Error ffb_get_effect_type       (const FFB_Data* Packet, FFB_Effect_Type* Effect);
Error ffb_get_effect_constant   (const FFB_Data* Packet, FFB_Effect_Constant* ConstantEffect);
Error ffb_get_device_control    (const FFB_Data* Packet, FFB_Control* Control);
Error ffb_get_device_gain       (const FFB_Data* Packet, uint8_t* Gain);

Device_Info device_get_info(Device_ID rID);

};