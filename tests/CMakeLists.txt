add_subdirectory(gtest)

include_directories(${CMAKE_SOURCE_DIR}/src)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test
	src/pixled/api/functionnal.cpp
	src/pixled/animation.cpp
	src/pixled/functionnal/functionnal.cpp
	src/pixled/functionnal/arithmetic.cpp
	src/pixled/functionnal/random.cpp
	src/pixled/functionnal/geometry.cpp
	src/pixled/functionnal/comparisons.cpp
	src/pixled/functionnal/signals.cpp
	src/pixled/mapping.cpp
	main.cpp
	)
target_link_libraries(test gtest_main gmock_main pixled)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
