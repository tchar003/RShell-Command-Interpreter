CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_CXX_STANDARD 14)


ADD_EXECUTABLE(rshell
	src/main.cpp
	src/Cmd.cpp
	src/Executor.cpp
)
