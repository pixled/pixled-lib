add_subdirectory(gtest)

include_directories(${CMAKE_SOURCE_DIR}/src)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test
	src/pixled/api/functionnal.cpp
	src/pixled/animation.cpp
	src/pixled/functionnal.cpp
	src/pixled/mapping.cpp
	main.cpp
	)
target_link_libraries(test gtest_main gmock_main pixled)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
