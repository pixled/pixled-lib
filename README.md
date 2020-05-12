# Pixled Library :rainbow: :sheep:

Pixled is a C++ library designed to produce generic led strips animations for
1D or 2D shapes.

It can be used directly as an embedded Arduino library, or from any other
platform that handles C++ 11, for example to stream animations from a server.

## Arduino build

In order to use the library from Arduino, you first need to locate your Arduino
user repository.
- In the Arduino IDE : `File`->`Preferences`->`Sketchbook location`
- Using `arduino-cli` : check the `directories:	user:` parameter of your
	current configuration file

Next, in a terminal, run :
```
cd your_arduino_user_repository
mkdir libraries
cd libraries
git clone https://github.com/pixled/pixled-lib
```

You can now use the pixled library adding an `#include <pixled.h>` statement in
your Arduino sketches.

### Update
To update the library, go to the git cloned repository and run `git pull`.

## CMake build

You can use [CMake](https://cmake.org/) to build and install the Pixled library
on any other platform that support CMake.

### First method : local installation

1. Start installing CMake, depending on the current OS
2. In the directory of your choice, run `git clone https://github.com/pixled/pixled-lib`
3. To build the library, use the following commands :
```
cd pixled-lib
mkdir build
cd build
cmake ..
make
```
4. To install the library on the system, run `cmake --install`.

You should now be able to use `#include <pixled.h>` in any C++ project.

### Second method : CMake integration

You can use the provided CMakeLists.txt to build the Pixled library as a
"subdirectory" of your CMake project. To do so :
1. Go to the root of your project
2. Run `git clone https://github.com/pixled/pixled-lib`
3. Add the following statement to your current CMakeLists.txt :
```
add_subdirectory(pixled-lib)
```
4. Link the library to the target that require `pixled.h`
```
add_executable(example example_main.cpp)
target_link_libraries(example pixled)
```
