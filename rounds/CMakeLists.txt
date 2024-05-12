if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

include_directories(.)
subdirs(943)
subdirs(944)
subdirs(1953)