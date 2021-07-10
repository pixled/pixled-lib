find_package(pixled-gif REQUIRED)

add_executable(sine sine.cpp)
target_link_libraries(sine pixled pixled-gif)

add_executable(triangle triangle.cpp)
target_link_libraries(triangle pixled pixled-gif)

add_executable(square square.cpp)
target_link_libraries(square pixled pixled-gif)

add_executable(sawtooth sawtooth.cpp)
target_link_libraries(sawtooth pixled pixled-gif)
