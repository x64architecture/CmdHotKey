cmake_minimum_required(VERSION 2.8.8)
project(CmdHotKey C)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows")

add_executable(
	CmdHotKey

	main.c
)
