cmake_minimum_required(VERSION 3.5)

project(ppmSim LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.11.2
)

FetchContent_MakeAvailable(cpr)

add_executable(ppmSim ./src/main.cpp ./src/network.cpp)

target_link_libraries(ppmSim PRIVATE cpr::cpr)