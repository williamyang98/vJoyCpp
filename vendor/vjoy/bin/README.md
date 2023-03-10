# Introduction
dll was copied from [vJoy SDK](https://github.com/njz3/vJoy/releases/tag/v2.2.1.1).

# Instructions for generating .lib if not present
## Step 1. Generating .def file
### Method 1. Mingw64
1. <code>gendef vJoyInterface.dll</code>

### Method 2. VC++
1. <code>dumpbin /EXPORTS vJoyInteface.dll > vJoyInterface.def</code>
2. Keep the function names in vJoyInterface.def
3. Add the following text to the top of vJoyInterface.def 
```
LIBRARY "vJoyInterface.dll"
EXPORTS
```

## Step 2. Generating .lib file using VC++
1. <code>lib /def:vJoyInterface.def /machine:x64 /out:vJoyInterface.lib</code>