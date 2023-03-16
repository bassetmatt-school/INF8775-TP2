cmake_minimum_required(VERSION 3.16)

project(
	"TP2"
	LANGUAGES
	CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
	"${CMAKE_SOURCE_DIR}/cmake/"
)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-O3
	-std=c++20
)
add_executable(tp2
	${SRC_FILES}
)


target_include_directories(tp2 
	PRIVATE
	${PROJECT_SOURCE_DIR}/include
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(tp2 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

set_target_properties(tp2 
	PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin
)
