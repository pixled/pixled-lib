if(NOT ESP_PLATFORM)
	cmake_minimum_required(VERSION 3.10)

	project(pixled-lib VERSION 0.1)

	set(CMAKE_CXX_STANDARD 11)
	set(CMAKE_CXX_STANDARD_REQUIRED True)

	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wpedantic")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

	add_subdirectory(src)
	add_subdirectory(tests)
	#add_subdirectory(examples EXCLUDE_FROM_ALL)

	include(CMakePackageConfigHelpers)
	write_basic_package_version_file(
		${CMAKE_CURRENT_BINARY_DIR}/pixledConfigVersion.cmake
		COMPATIBILITY SameMajorVersion)
	install(FILES
		cmake/pixledConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/pixledConfigVersion.cmake
		DESTINATION lib/cmake/pixled)


	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)
		set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)
		set(DOXYGEN_MACRO_EXPANSION "YES")
		set(DOXYGEN_EXTRACT_STATIC "YES")
		set(DOXYGEN_HTML_OUTPUT ".")
		set(DOXYGEN_IMAGE_PATH
			${CMAKE_CURRENT_SOURCE_DIR}/examples/gif
			)
		set(DOXYGEN_SORT_MEMBER_DOCS "NO")
		set(DOXYGEN_PREDEFINED "DOXYGEN_BUILD")
		set(DOXYGEN_HAVE_DOT "YES")
		#set(DOXYGEN_TEMPLATE_RELATIONS "YES")
		set(DOXYGEN_VERBATIM_VARS DOXYGEN_ALIASES)
		set(DOXYGEN_HIDE_FRIEND_COMPOUNDS "YES")
		set(DOXYGEN_EXAMPLE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/examples)
		set(DOXYGEN_ALIASES 
			[[Function{1}="\ref base::Function \"base::Function<\1>\""]]
			[[Function="\ref base::Function \"Function\""]]
			[[function_call_operator="\ref function_call_operator \"base::Function::operator()(point, time)\""]]
			[[Functions="\ref base::Function \"Functions\""]]
			[[SFINAE="[SFINAE](https://en.cppreference.com/w/cpp/language/sfinae)"]]

			)
		doxygen_add_docs(doc
			${CMAKE_CURRENT_SOURCE_DIR}/src
			)
	endif()
else()
	idf_component_register(
		SRC_DIRS "src/pixled" "src/pixled/api"
		INCLUDE_DIRS "src")
endif()
