add_subdirectory(gtest)

include_directories(${CMAKE_SOURCE_DIR}/src)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test
	src/pixled/strip.cpp
	src/pixled/animation.cpp
	src/pixled/output.cpp
	src/pixled/functionnal.cpp
	main.cpp
	)
target_link_libraries(test gtest_main gmock_main pixled)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
