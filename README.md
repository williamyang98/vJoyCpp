# Introduction
vJoy C++ wrapper using vJoy v2.2.1 from [here](https://github.com/njz3/vJoy).

Functions are placed in a namespace and renamed for convenience.

Sample application in src/main.cpp is provided as a usage reference.

## Files
- Sources for files in <code>vendor/vjoy</code>

| Filename | Description | Version | Source |
| --- | --- | --- | --- |
| install/vJoySetup.exe     | Install vJoy on Windows       | 2.2.1 | [link](https://github.com/njz3/vJoy/releases/tag/v2.2.1.1) |
| bin/.../vJoyInterface.dll | dll for interfacing with vJoy | 2.2.1 | [link](https://github.com/njz3/vJoy/tree/28bede0a486dd0a303157c1365d4f18464e7034d/SDK/lib) |

## Usage
Refer to CMakeLists.txt for example application usage.

## Running example
### Step 1. Configure vjoy
1. Run <code>install/vJoySetup.exe</code>
2. Run vJoyConf.exe (which is now installed through setup) and configure device 1
3. Open 'Setup USB Game Controllers' from Windows start menu
4. Select vjoy device and click properties to inspect current state of vjoy device

### Step 2. Build and run
Building requires the following:
- C++ compiler with at least C++14 support
- cmake
- Ninja or msbuild (instructions use Ninja)

1. <code>cmake . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release</code>
2. <code>ninja -C build</code>
3. <code>build/main.exe</code>


