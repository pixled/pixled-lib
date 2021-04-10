add_subdirectory(gtest)

include_directories(${CMAKE_SOURCE_DIR}/src)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test
	pixled/function.cpp
	pixled/geometry.cpp
	pixled/animation/animation.cpp
	pixled/arithmetic/arithmetic.cpp
	pixled/random/random.cpp
	pixled/geometry/geometry.cpp
	pixled/conditional/conditional.cpp
	pixled/signal/signal.cpp
	pixled/mapping/mapping.cpp
	main.cpp
	)
target_link_libraries(test gtest_main gmock_main pixled)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
