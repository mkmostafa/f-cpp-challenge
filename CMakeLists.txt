cmake_minimum_required(VERSION 2.8)

project(FyberCppChallenge LANGUAGES CXX)

include_directories(
	./
	include
)



add_executable(FyberCppChallenge 
src/Banner.cpp
src/Processor.cpp
src/main.cpp)
target_link_libraries (FyberCppChallenge boost_system)
target_compile_options(FyberCppChallenge PRIVATE -std=c++11 -g)
set_target_properties(FyberCppChallenge PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)

