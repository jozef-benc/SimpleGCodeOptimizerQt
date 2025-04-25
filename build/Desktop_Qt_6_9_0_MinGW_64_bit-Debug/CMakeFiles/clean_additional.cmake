# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GCodeOptimizerQt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GCodeOptimizerQt_autogen.dir\\ParseCache.txt"
  "GCodeOptimizerQt_autogen"
  )
endif()
