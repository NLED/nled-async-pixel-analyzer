# nled-async-pixel-analyzer

Based on the Saleae Analyzer: https://github.com/saleae/async-rgb-led-analyzer

Compatible with Saleae Logic 2 app

Modified to add addional async addressable pixel chipsets and added RGBW/GRBW support. Project made in Visual Studio 2022.

I am unfamiliar with this language and IDE so I can't say the code changes are perfect. But the result works well and is very useful for working with all types of addressable pixels.

**Chipsets Supported:**
 WS2811, WS2812, WS2812B, WS2812-V4, WS2812-2020, WS2813, WS2814, WS2815, WS2818A, WS2818B, UCS1903, UCS2903, UCS2904B, SM16703, SM16704, PD9823, APA106, SK6822, APA104, SK6805MINI, 
LC8806B-2020, SK6805, SK6812, SK6812RGBW, SK6812RGBP8 , SK6812HV-4P, SK6805-EC15, SK6812RGBWP8, SK9816, SK6813, LPD1886, TM1803, TM1804, TM1829(hi speed)

Color ordering such as GRB or GRBW is automatically applied.

# To Install On Windows

Move the dll file found at nled-async-pixel-analyzer/out/install/x64-Release/Analyzers/nled_async_pixel_analyzer.dll

To the Logic Analyzers folder, default path: C:\Program Files\Logic\resources\windows-x64\Analyzers

# Saleae Async RGB LED Analyzer

Saleae Async RGB LED Analyzer

## Getting Started

The following documentation describes getting this analyzer building locally. For more detailed information about the Analyzer SDK, debugging, CI build, and more, checkout the readme from the Sample Analyzer repository:

https://github.com/saleae/SampleAnalyzer

### MacOS

Dependencies:

- XCode with command line tools
- CMake 3.13+
- git

Installing command line tools after XCode is installed:

```
xcode-select --install
```

Then open XCode, open Preferences from the main menu, go to locations, and select the only option under 'Command line tools'.

Installing CMake on MacOS:

1. Download the binary distribution for MacOS, `cmake-*-Darwin-x86_64.dmg`
2. Install the usual way by dragging into applications.
3. Open a terminal and run the following:

```
/Applications/CMake.app/Contents/bin/cmake-gui --install
```

_Note: Errors may occur if older versions of CMake are installed._

Building the analyzer:

```
mkdir build
cd build
cmake ..
cmake --build .
```

### Ubuntu 18.04+

Dependencies:

- CMake 3.13+
- gcc 4.8+
- git

Misc dependencies:

```
sudo apt-get install build-essential
```

Building the analyzer:

```
mkdir build
cd build
cmake ..
cmake --build .
```

### Windows

Dependencies:

- Visual Studio 2019
- CMake 3.13+
- git

**Visual Studio 2019**

_Note - newer and older versions of Visual Studio are likely to work._

Setup options:

- Workloads > Desktop & Mobile > "Desktop development with C++"

Note - if CMake has any problems with the MSVC compiler, it's likely a component is missing.

**CMake**

Download and install the latest CMake release here.
https://cmake.org/download/

**git**

Download and install git here.
https://git-scm.com/

Building the analyzer:

```
mkdir build
cd build
cmake .. -A x64
```

Then, open the newly created solution file located here: `build\async_rgb_led_analyzer.sln`

The built analyzer DLLs will be located here:

`build\Analyzers\Debug`

`build\Analyzers\Release`

For debug and release builds, respectively.


## Output Frame Format
  
### Frame Type: `"pixel"`

| Property | Type | Description |
| :--- | :--- | :--- |
| `index` | int | The index along the LED strip. Index 0 is the first LED |
| `red` | int | The red channel, [0-255] |
| `green` | int | The green channel, [0-255] |
| `blue` | int | The blue channel, [0-255] |

Represents a single RGB pixel value

