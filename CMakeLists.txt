cmake_minimum_required(VERSION 3.18)
project(CityBuilder)


set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

add_subdirectory(core/)

add_executable(main main.cc)
target_link_libraries(main PRIVATE core sfml-system sfml-network sfml-graphics sfml-window sfml-audio)
