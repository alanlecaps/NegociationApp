# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/projet-informatique-sa7_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/projet-informatique-sa7_autogen.dir/ParseCache.txt"
  "projet-informatique-sa7_autogen"
  )
endif()
