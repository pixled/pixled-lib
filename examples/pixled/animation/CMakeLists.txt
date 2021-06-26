find_package(pixled-gif REQUIRED)

add_executable(blink blink.cpp)
target_link_libraries(blink pixled pixled-gif)

add_executable(blooming blooming.cpp)
target_link_libraries(blooming pixled pixled-gif)

add_executable(rainbow rainbow.cpp)
target_link_libraries(rainbow pixled pixled-gif)

add_executable(linear_unit_wave linear_unit_wave.cpp)
target_link_libraries(linear_unit_wave pixled pixled-gif)

add_executable(radial_unit_wave radial_unit_wave.cpp)
target_link_libraries(radial_unit_wave pixled pixled-gif)

add_executable(sequence sequence.cpp)
target_link_libraries(sequence pixled pixled-gif)
