project(pixled-lib)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(pixled
	src/pixled/led.cpp
	)

install(TARGETS pixled DESTINATION lib)
install(FILES 
	src/pixled.h
	DESTINATION include)

install(FILES
	src/pixled/api/animation.h
	src/pixled/api/led.h
	src/pixled/api/output.h
	src/pixled/api/functionnal.h
	src/pixled/api/utils.h
	DESTINATION include/pixled/api
	)

install(FILES
	src/pixled/animation.h
	src/pixled/led.h
	src/pixled/output.h
	src/pixled/functionnal.h
	DESTINATION include/pixled
	)
	
