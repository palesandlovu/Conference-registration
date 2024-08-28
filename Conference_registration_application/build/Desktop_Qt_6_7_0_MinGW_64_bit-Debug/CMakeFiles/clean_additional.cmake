# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Question3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Question3_autogen.dir\\ParseCache.txt"
  "Question3_autogen"
  )
endif()
