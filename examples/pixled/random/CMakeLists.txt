find_package(pixled-gif REQUIRED)

add_executable(uniform uniform.cpp)
target_link_libraries(uniform pixled pixled-gif)
