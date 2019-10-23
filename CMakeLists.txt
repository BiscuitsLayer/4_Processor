cmake_minimum_required(VERSION 3.15)
project(4_Processor)

set(CMAKE_CXX_STANDARD 14)

add_executable(4_Processor main.cpp
        cmake-build-debug/third_party_libraries/StackLib.cpp
        processor_parts/CPU.cpp             processor_parts/CPU.h
        processor_parts/Assembler.cpp       processor_parts/Assembler.h
        processor_parts/Disassembler.cpp    processor_parts/Disassembler.h)