cmake_minimum_required(VERSION 3.28)

project(cfg-analysis)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(cfg-analysis
        src/parser.cpp
        src/instruction.cpp
        src/factset.cpp
        src/driver.cpp
        src/cfg.cpp
        src/bbl.cpp
        src/main.cpp
        )

