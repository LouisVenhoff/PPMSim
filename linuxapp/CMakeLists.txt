cmake_minimum_required(VERSION 3.5)

project(ppmSim LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.11.2
)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(cpr)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(ppmSim ./src/main.cpp ./src/network.cpp ./src/udp.cpp ./src/virtualDevice.cpp)

target_link_libraries(ppmSim PRIVATE cpr::cpr)
target_link_libraries(ppmSim PRIVATE nlohmann_json::nlohmann_json)