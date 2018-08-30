# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# include_directories("${CMAKE_SOURCE_DIR}/include")

# Create a variable containing all .cpp files:
#set(GOL_SOURCES board.cpp main.cpp)
file(GLOB GOAP_SOURCES *.cpp)

# Create an executable file from sources:
add_library(goap STATIC ${GOAP_SOURCES})