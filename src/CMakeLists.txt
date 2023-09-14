cmake_minimum_required(VERSION 3.22)
project(GenAlgo)
include_directories(tclap-1.2.5/include)
include_directories(pcg-cpp-0.98/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(GenAlgo main.cpp Instance.hpp Clause.cpp Clause.hpp Instance.cpp Evolution.cpp Evolution.hpp Individual.cpp Individual.hpp evoConfig.hpp FastPRNG.hpp FastPRNG.cpp Args.cpp Args.hpp ThreadWorker.cpp ThreadWorker.hpp ThreadFile.cpp ThreadFile.hpp)
