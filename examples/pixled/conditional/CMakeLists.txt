find_package(pixled-gif REQUIRED)

add_executable(conditional conditional.cpp)
target_link_libraries(conditional pixled pixled-gif)
