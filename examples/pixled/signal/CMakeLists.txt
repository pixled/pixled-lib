find_package(pixled-gif REQUIRED)

add_executable(sine sine.cpp)
target_link_libraries(sine pixled pixled-gif)
