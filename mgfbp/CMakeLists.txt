cmake_minimum_required(VERSION 3.18)

project(mgfpj CXX CUDA)

find_package(CUDA REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CUDA_RUNTIME_LIBRARY Static)

# Include source file
set(SOURCES
    src/mgfbp.cpp
    src/stdafx.cpp
    src/FbpClass.cu
    src/FbpClass_Agent.cu
)
add_executable(mgfbp ${SOURCES})

# Target
target_compile_features(mgfbp PUBLIC cxx_std_17)
target_link_libraries(mgfbp
    rapidjson
    ${CUDA_LIBRARIES}
    stdc++fs # Remove this line for GCC > 8.2 which fully supports <filesystem>
)
target_include_directories(mgfbp PRIVATE ${PROJECT_SOURCE_DIR}/include)
set_target_properties(mgfbp PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

install(TARGETS mgfbp)
