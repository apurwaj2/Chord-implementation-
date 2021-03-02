cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp node.cpp Listen.cpp Finger.cpp Finger.h pocoHeader.h Stabilize.cpp auxiliary.h)

target_link_libraries(untitled PocoNet PocoFoundation)
