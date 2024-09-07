cmake_minimum_required(VERSION 3.30)
project(opengl)
include(FetchContent)
FetchContent_Declare(
	sdl2
	GIT_REPOSITORY https://github.com/libsdl-org/SDL
	GIT_TAG release-2.30.x
)
FetchContent_GetProperties(sdl2)
FetchContent_MakeAvailable(sdl2)
add_executable(opengl main.c glad.c)
link_directories(${sdl2_BINARY_DIR})
target_link_libraries(opengl SDL2)
