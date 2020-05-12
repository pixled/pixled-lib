project(pixled-lib)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_library(pixled
	#)

#install(TARGETS pixled DESTINATION lib)
install(FILES src/pixled.h DESTINATION include)
