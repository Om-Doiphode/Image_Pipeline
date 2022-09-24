cmake_minimum_required(VERSION 3.10)

project(Image_Pipeline)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# The following folder will be included
include_directories("${CMAKE_SOURCE_DIR}/../include")
link_directories("${CMAKE_SOURCE_DIR}/../include")

# include_directories(${OpenCV_INCLUDE_DIRS})
find_package(OpenCV REQUIRED)

add_executable(working ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/debayering.cpp ${PROJECT_SOURCE_DIR}/WB.cpp ${PROJECT_SOURCE_DIR}/Gamma.cpp ${PROJECT_SOURCE_DIR}/ColorSpace.cpp ${PROJECT_SOURCE_DIR}/Conversion.cpp ${PROJECT_SOURCE_DIR}/Morphology.cpp ${PROJECT_SOURCE_DIR}/Edges.cpp ${PROJECT_SOURCE_DIR}/Filters.cpp)
target_link_libraries(working ${OpenCV_LIBS})