# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("${CMAKE_SOURCE_DIR}/src")

# Create a variable containing all .cpp files:
#set(GOL_SOURCES board.cpp main.cpp)
# file(GLOB EXAMPLES_SOURCES *.cpp)

# Create an executable file from sources:
# add_executable(gol ${FAM_SOURCES})
# add_library(fam ${FAM_SOURCES})
add_executable(wargame_example main.cpp)

# Link to the bundled Intel TBB libs
# link_directories(${CMAKE_SOURCE_DIR}/ext/tbb41_20130613oss/lib)
target_link_libraries(wargame_example goap)
