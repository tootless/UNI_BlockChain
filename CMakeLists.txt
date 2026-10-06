cmake_minimum_required(VERSION 3.10)
project(hashFunction)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# pagrindine hash programa su ivestimi/failais
add_executable(hash_f main.cpp)

# eksperimentai
add_executable(experiments experiments/main.cpp 
	experiments/1/experiment1.cpp 
	experiments/2/experiment2.cpp 
	experiments/3/experiment3.cpp)

target_include_directories(experiments PRIVATE ${CMAKE_SOURCE_DIR})