if(NOT ESP_PLATFORM)
project(pixled-lib)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

add_library(pixled
	src/pixled/pixel.cpp
	)

add_subdirectory(tests)

install(TARGETS pixled DESTINATION lib)
install(FILES 
	src/pixled.h
	DESTINATION include)

install(FILES
	src/pixled/api/animation.h
	src/pixled/api/pixel.h
	src/pixled/api/functionnal.h
	src/pixled/api/output.h
	src/pixled/api/utils.h
	DESTINATION include/pixled/api
	)

install(FILES
	src/pixled/animation.h
	src/pixled/pixel.h
	src/pixled/functionnal.h
	DESTINATION include/pixled
	)
else()
	idf_component_register(SRCS "src/pixled/led.cpp" INCLUDE_DIRS "src")
endif()
