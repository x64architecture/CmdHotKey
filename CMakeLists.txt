cmake_minimum_required(VERSION 2.8)
project(CmdHotKey)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows")

add_executable(
	CmdHotKey

	main.c
	resource.h
	assemblyinfo.rc
)