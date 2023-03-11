## Running example
### Step 1. Configure vjoy
1. Run <code>install/vJoySetup-2.2.1-signed.exe</code>
2. Run vJoyConf.exe (which is now installed through setup) and configure device 1
3. Run 'Monitor vJoy' which was installed after setup (look in up in start menu search)

### Step 2. Build and run
Building requires the following:
- C++ compiler with at least C++14 support
- cmake
- Ninja or msbuild (instructions use Ninja)

1. <code>cd examples</code>
1. <code>cmake . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release</code>
2. <code>ninja -C build</code>
3. <code>build/main.exe</code>