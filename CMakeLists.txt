if(NOT ESP_PLATFORM)
	project(pixled-lib)

	cmake_minimum_required(VERSION 3.10)

	set(CMAKE_CXX_STANDARD 11)
	set(CMAKE_CXX_STANDARD_REQUIRED True)

	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wpedantic")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

	add_library(pixled
		src/pixled/api/geometry.cpp
		src/pixled/pixel.cpp
		src/pixled/mapping.cpp
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
		src/pixled/api/mapping.h
		src/pixled/api/geometry.h
		DESTINATION include/pixled/api
		)

	install(FILES
		src/pixled/animation.h
		src/pixled/pixel.h
		src/pixled/mapping.h
		DESTINATION include/pixled
		)
	install(FILES
		src/pixled/functionnal/functionnal.h
		src/pixled/functionnal/artithmetic.h
		src/pixled/functionnal/geometry.h
		src/pixled/functionnal/comparisons.h
		src/pixled/functionnal/random.h
		src/pixled/functionnal/signals.h
		DESTINATION include/pixled/functionnal
		)
else()
	idf_component_register(
		SRC_DIRS "src/pixled" "src/pixled/api"
		INCLUDE_DIRS "src")
endif()
