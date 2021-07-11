find_package(pixled-gif REQUIRED)

add_executable(index index.cpp)
target_link_libraries(index pixled pixled-gif)
