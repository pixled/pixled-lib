add_library(pixled
	pixled/geometry.cpp
	pixled/pixel.cpp
	pixled/runtime.cpp
	pixled/pixel/pixel.cpp
	pixled/mapping/mapping.cpp
	pixled/animation/animation.cpp
	pixled/geometry/geometry.cpp
	pixled/random/random.cpp
	pixled/signal/signal.cpp
	)

install(TARGETS pixled DESTINATION lib)

install(DIRECTORY . DESTINATION include FILES_MATCHING PATTERN "*.h")
