add_library(pixled
	pixled/geometry.cpp
	pixled/color.cpp
	pixled/runtime.cpp
	pixled/color/color.cpp
	pixled/mapping/mapping.cpp
	pixled/animation/animation.cpp
	pixled/geometry/geometry.cpp
	pixled/random/random.cpp
	pixled/signal/signal.cpp
	)

install(TARGETS pixled DESTINATION lib)

install(DIRECTORY . DESTINATION include FILES_MATCHING PATTERN "*.h")

install(TARGETS pixled EXPORT pixledTargets
	DESTINATION lib
	INCLUDES DESTINATION include)

export(EXPORT pixledTargets
	NAMESPACE pixled::)
install(EXPORT pixledTargets
	DESTINATION lib/cmake/pixled
	NAMESPACE pixled::)


