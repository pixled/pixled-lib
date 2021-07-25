# Gets googletest from GitHub
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/96f4ce02a3a78d63981c67acbd368945d11d7d70.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


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
