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

add_executable(working ${PROJECT_SOURCE_DIR}/auto_white_balance.cpp ${PROJECT_SOURCE_DIR}/color_space_conversion.cpp ${PROJECT_SOURCE_DIR}/conversion.cpp  ${PROJECT_SOURCE_DIR}/create_image.cpp ${PROJECT_SOURCE_DIR}/debayering.cpp ${PROJECT_SOURCE_DIR}/black_level_correction.cpp ${PROJECT_SOURCE_DIR}/auto_exposure.cpp ${PROJECT_SOURCE_DIR}/edges.cpp ${PROJECT_SOURCE_DIR}/filters.cpp ${PROJECT_SOURCE_DIR}/gamma.cpp ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/morphology.cpp ${PROJECT_SOURCE_DIR}/rotate.cpp)
target_link_libraries(working ${OpenCV_LIBS})