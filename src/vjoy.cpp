#include "vjoy.hpp"

// Provide the C to C++ wrapping

// vJoyInterface.dll
// SOURCE: https://github.com/njz3/vJoy/blob/master/SDK/inc/vjoyinterface.h
// DOC: docs/vjoy_manual.odt
extern "C" 
{
// General driver data
bool vJoyEnabled(void);
uint16_t GetvJoyVersion(void);
const char16_t* GetvJoyProductString(void);
const char16_t* GetvJoyManufacturerString(void);
const char16_t* GetvJoySerialNumberString(void);
bool DriverMatch(uint16_t* DllVer, uint16_t* DrvVer);
void RegisterRemovalCB(vjoy::Device_Remove_Callback cb, void* user_data);
bool vJoyFfbCap(bool* Supported);                                                   // Is this version of vJoy capable of FFB?
bool GetvJoyMaxDevices(int* n);                                                     // What is the maximum possible number of vJoy devices
bool GetNumberExistingVJD(int* n);                                                  // What is the number of vJoy devices currently enabled
// vJoy Device properties
int GetVJDButtonNumber(vjoy::Device_ID rID);                                        // Get the number of buttons defined in the specified VDJ
int GetVJDDiscPovNumber(vjoy::Device_ID rID);                                       // Get the number of descrete-type POV hats defined in the specified VDJ
int GetVJDContPovNumber(vjoy::Device_ID rID);                                       // Get the number of descrete-type POV hats defined in the specified VDJ
bool GetVJDAxisExist(vjoy::Device_ID rID, vjoy::Axis Axis);                         // Test if given axis defined in the specified VDJ
bool GetVJDAxisMax(vjoy::Device_ID rID, vjoy::Axis Axis, int32_t* Max);             // Get logical Maximum value for a given axis defined in the specified VDJ
bool GetVJDAxisMin(vjoy::Device_ID rID, vjoy::Axis Axis, int32_t* Min);             // Get logical Minimum value for a given axis defined in the specified VDJ
enum vjoy::Device_Status GetVJDStatus(vjoy::Device_ID rID);                         // Get the status of the specified vJoy Device.
bool isVJDExists(vjoy::Device_ID rID);                                              // TRUE if the specified vJoy Device exists                                                                            
int GetOwnerPid(vjoy::Device_ID rID);                                               // Reurn owner's Process ID if the specified vJoy Device exists
// Write access to vJoy Device - Basic
bool AcquireVJD(vjoy::Device_ID rID);                                               // Acquire the specified vJoy Device.
void RelinquishVJD(vjoy::Device_ID rID);                                            // Relinquish the specified vJoy Device.
bool UpdateVJD(vjoy::Device_ID rID, vjoy::Joystick_Position* pData);                // Update the position data of the specified vJoy Device.
// Reset functions
bool ResetVJD(vjoy::Device_ID rID);                                                 // Reset all controls to predefined values in the specified VDJ
void ResetAll(void);                                                                // Reset all controls to predefined values in all VDJ
bool ResetButtons(vjoy::Device_ID rID);                                             // Reset all buttons (To 0) in the specified VDJ
bool ResetPovs(vjoy::Device_ID rID);                                                // Reset all POV Switches (To -1) in the specified VDJ
// Write data
bool SetAxis(int32_t Value, vjoy::Device_ID rID, vjoy::Axis Axis);                  // Write Value to a given axis defined in the specified VDJ 
bool SetBtn(bool Value, vjoy::Device_ID rID, uint8_t nBtn);                         // Write Value to a given button defined in the specified VDJ 
bool SetDiscPov(int Value, vjoy::Device_ID rID, uint8_t nPov);                      // Write Value to a given descrete POV defined in the specified VDJ 
bool SetContPov(uint32_t Value, vjoy::Device_ID rID, uint8_t nPov);                 // Write Value to a given continuous POV defined in the specified VDJ 
// Force Feedback (FFB) functions
vjoy::FFB_Effect_Type FfbGetEffect(void);                                           // Returns effect serial number if active, 0 if inactive
void FfbRegisterGenCB(vjoy::FFB_Generate_Callback cb, void* user_data);            
bool FfbStart(vjoy::Device_ID);                                                     // NOTE: Deprecated
void FfbStop(vjoy::Device_ID);                                                      // NOTE: Deprecated
bool IsDeviceFfb(vjoy::Device_ID rID);
bool IsDeviceFfbEffect(vjoy::Device_ID rID, vjoy::FFB_Effect Effect);
//  Force Feedback (FFB) helper functions
vjoy::Error Ffb_h_DeviceID(const vjoy::FFB_Data* Packet, uint32_t* DeviceID);
vjoy::Error Ffb_h_Type(const vjoy::FFB_Data* Packet, vjoy::FFB_Packet_Type* Type);
vjoy::Error Ffb_h_Packet(const vjoy::FFB_Data* Packet, uint16_t* Type, uint32_t* DataSize, uint8_t* Data[]);
vjoy::Error Ffb_h_EffectBlockIndex(const vjoy::FFB_Data* Packet, uint32_t* Index);
vjoy::Error Ffb_h_Eff_Report(const vjoy::FFB_Data* Packet, vjoy::FFB_Effect_Report*  Effect);
vjoy::Error Ffb_h_Eff_Ramp(const vjoy::FFB_Data* Packet, vjoy::FFB_Effect_Ramp*  RampEffect);
vjoy::Error Ffb_h_EffOp(const vjoy::FFB_Data* Packet, vjoy::FFB_Effect_Operation*  Operation);
vjoy::Error Ffb_h_DevCtrl(const vjoy::FFB_Data* Packet, vjoy::FFB_Control* Control);
vjoy::Error Ffb_h_Eff_Period(const vjoy::FFB_Data* Packet, vjoy::FFB_Effect_Period*  Effect);
vjoy::Error Ffb_h_Eff_Cond(const vjoy::FFB_Data* Packet, vjoy::FFB_Effect_Condition*  Condition);
vjoy::Error Ffb_h_DevGain(const vjoy::FFB_Data* Packet, uint8_t* Gain);
vjoy::Error Ffb_h_Eff_Envlp(const vjoy::FFB_Data* Packet, vjoy::FFB_Effect_Envelope*  Envelope);
vjoy::Error Ffb_h_EffNew(const vjoy::FFB_Data* Packet, vjoy::FFB_Effect_Type* Effect);
vjoy::Error Ffb_h_Eff_Constant(const vjoy::FFB_Data* Packet, vjoy::FFB_Effect_Constant* ConstantEffect);
};

// Wrap C functions in C++ namespace
namespace vjoy 
{
// General driver data
bool api_is_enabled(void)                                                     { return ::vJoyEnabled(); }
uint16_t api_get_version(void)                                                { return ::GetvJoyVersion(); }
const char16_t* api_get_product_string(void)                                  { return ::GetvJoyProductString(); }
const char16_t* api_get_manufacturer_string(void)                             { return ::GetvJoyManufacturerString(); }
const char16_t* api_get_serial_number_string(void)                            { return ::GetvJoySerialNumberString(); }
bool api_is_driver_match(uint16_t* DllVer, uint16_t* DrvVer)                  { return ::DriverMatch(DllVer, DrvVer); }
void api_register_remove_callback(Device_Remove_Callback cb, void* user_data) { return ::RegisterRemovalCB(cb, user_data); }
bool api_is_force_feedback_available(bool* Supported)                         { return ::vJoyFfbCap(Supported); }                                            
bool api_get_max_total_devices(int* n)                                        { return ::GetvJoyMaxDevices(n); }                                                 
bool api_get_total_existing_devices(int* n)                                   { return ::GetNumberExistingVJD(n); }                                             
void api_reset_all_devices(void)                                              { return ::ResetAll(); }
// vJoy Device properties
int device_get_total_buttons        (Device_ID rID)                               { return ::GetVJDButtonNumber(rID); }
int device_get_total_discrete_POVs  (Device_ID rID)                               { return ::GetVJDDiscPovNumber(rID); }
int device_get_total_continuous_POVs(Device_ID rID)                               { return ::GetVJDContPovNumber(rID); };
bool device_get_axis_exists         (Device_ID rID, Axis Axis)                    { return ::GetVJDAxisExist(rID, Axis); }
bool device_get_axis_max            (Device_ID rID, Axis Axis, int32_t* Max)      { return ::GetVJDAxisMax(rID, Axis, Max); }
bool device_get_axis_min            (Device_ID rID, Axis Axis, int32_t* Min)      { return ::GetVJDAxisMin(rID, Axis, Min); }
enum Device_Status device_get_status(Device_ID rID)                               { return ::GetVJDStatus(rID); }
bool device_is_exists               (Device_ID rID)                               { return ::isVJDExists(rID); }
int device_get_owner_pid            (Device_ID rID)                               { return ::GetOwnerPid(rID); }
bool device_acquire                 (Device_ID rID)                               { return ::AcquireVJD(rID); }
void device_release                 (Device_ID rID)                               { return ::RelinquishVJD(rID); }
bool device_update                  (Device_ID rID, Joystick_Position* pData)     { return ::UpdateVJD(rID, pData); }
bool device_reset                   (Device_ID rID)                               { return ::ResetVJD(rID); }
bool device_reset_buttons           (Device_ID rID)                               { return ::ResetButtons(rID); }
bool device_reset_POVs              (Device_ID rID)                               { return ::ResetPovs(rID); }
bool device_set_axis                (Device_ID rID, Axis Axis, int32_t Value)     { return ::SetAxis(Value, rID, Axis); }
bool device_set_button              (Device_ID rID, uint8_t nBtn, bool Value)     { return ::SetBtn(Value, rID, nBtn); }
bool device_set_discrete_POV        (Device_ID rID, uint8_t nPov, int Value)      { return ::SetDiscPov(Value, rID, nPov); }
bool device_set_continuous_POV      (Device_ID rID, uint8_t nPov, uint32_t Value) { return ::SetContPov(Value, rID, nPov); }
bool device_ffb_start               (Device_ID rID)                               { return ::FfbStart(rID); }
void device_ffb_stop                (Device_ID rID)                               { return ::FfbStop(rID); }
bool device_is_ffb                  (Device_ID rID)                               { return ::IsDeviceFfb(rID); }
bool device_is_ffb_effect           (Device_ID rID, FFB_Effect Effect)            { return ::IsDeviceFfbEffect(rID, Effect); }
// Force Feedback (FFB) functions
FFB_Effect_Type ffb_get_effect(void)                                                                          { return ::FfbGetEffect(); }
void ffb_register_generate_callback(FFB_Generate_Callback cb, void* user_data)                                { return ::FfbRegisterGenCB(cb, user_data); }
Error ffb_get_device_id         (const FFB_Data* Packet, uint32_t* DeviceID)                                  { return ::Ffb_h_DeviceID(Packet, DeviceID); }
Error ffb_get_packet_type       (const FFB_Data* Packet, FFB_Packet_Type* Type)                               { return ::Ffb_h_Type(Packet, Type); }
Error ffb_get_packet            (const FFB_Data* Packet, uint16_t* Type, uint32_t* DataSize, uint8_t* Data[]) { return ::Ffb_h_Packet(Packet, Type, DataSize, Data); }
Error ffb_get_effect_block_index(const FFB_Data* Packet, uint32_t* Index)                                     { return ::Ffb_h_EffectBlockIndex(Packet, Index); }
Error ffb_get_effect_report     (const FFB_Data* Packet, FFB_Effect_Report* Effect)                           { return ::Ffb_h_Eff_Report(Packet, Effect); }
Error ffb_get_effect_ramp       (const FFB_Data* Packet, FFB_Effect_Ramp* RampEffect)                         { return ::Ffb_h_Eff_Ramp(Packet, RampEffect); }
Error ffb_get_effect_operation  (const FFB_Data* Packet, FFB_Effect_Operation* Operation)                     { return ::Ffb_h_EffOp(Packet, Operation); }
Error ffb_get_effect_period     (const FFB_Data* Packet, FFB_Effect_Period* Effect)                           { return ::Ffb_h_Eff_Period(Packet, Effect); }
Error ffb_get_effect_condition  (const FFB_Data* Packet, FFB_Effect_Condition* Condition)                     { return ::Ffb_h_Eff_Cond(Packet, Condition); }
Error ffb_get_effect_envelope   (const FFB_Data* Packet, FFB_Effect_Envelope* Envelope)                       { return ::Ffb_h_Eff_Envlp(Packet, Envelope); }
Error ffb_get_effect_type       (const FFB_Data* Packet, FFB_Effect_Type* Effect)                             { return ::Ffb_h_EffNew(Packet, Effect); }
Error ffb_get_effect_constant   (const FFB_Data* Packet, FFB_Effect_Constant* ConstantEffect)                 { return ::Ffb_h_Eff_Constant(Packet, ConstantEffect); }
Error ffb_get_device_control    (const FFB_Data* Packet, FFB_Control* Control)                                { return ::Ffb_h_DevCtrl(Packet, Control); }
Error ffb_get_device_gain       (const FFB_Data* Packet, uint8_t* Gain)                                       { return ::Ffb_h_DevGain(Packet, Gain); }
};

namespace vjoy 
{
Device_Info device_get_info(Device_ID rID) {
    Device_Info c;
    c.AxisX       = device_get_axis_exists(rID, Axis::X);
    c.AxisY       = device_get_axis_exists(rID, Axis::Y);
    c.AxisZ       = device_get_axis_exists(rID, Axis::Z);
    c.AxisXRot    = device_get_axis_exists(rID, Axis::RX);
    c.AxisYRot    = device_get_axis_exists(rID, Axis::RY);
    c.AxisZRot    = device_get_axis_exists(rID, Axis::RZ);
    c.Slider      = device_get_axis_exists(rID, Axis::SLIDER);
    c.Dial        = device_get_axis_exists(rID, Axis::DIAL);
    c.Wheel       = device_get_axis_exists(rID, Axis::WHEEL);
    c.Accelerator = device_get_axis_exists(rID, Axis::ACCELERATOR);
    c.Brake       = device_get_axis_exists(rID, Axis::BRAKE);
    c.Clutch      = device_get_axis_exists(rID, Axis::CLUTCH);
    c.Steering    = device_get_axis_exists(rID, Axis::STEERING);
    c.Rudder      = device_get_axis_exists(rID, Axis::RUDDER);
    c.Aileron     = device_get_axis_exists(rID, Axis::AILERON);
    c.Throttle    = device_get_axis_exists(rID, Axis::THROTTLE);
    c.nButtons    = device_get_total_buttons(rID);
    c.nDiscHats   = device_get_total_discrete_POVs(rID);
    c.nContHats   = device_get_total_continuous_POVs(rID);
    return c;
}
};