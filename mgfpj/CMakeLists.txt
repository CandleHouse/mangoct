cmake_minimum_required(VERSION 3.18)

project(mgfpj CXX CUDA)

find_package(CUDA REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CUDA_RUNTIME_LIBRARY Static)

# Include source file
set(SOURCES
    src/mgfpj.cpp
    src/stdafx.cpp  
    src/FpjClass.cpp
    src/FpjClass_Agent.cu
)
add_executable(mgfpj ${SOURCES})

# Target
target_compile_features(mgfpj PUBLIC cxx_std_17)
target_link_libraries(mgfpj
    rapidjson
    ${CUDA_LIBRARIES}
    stdc++fs # Remove this line for GCC > 8.2 which fully supports <filesystem>
)
target_include_directories(mgfpj PRIVATE ${PROJECT_SOURCE_DIR}/include)
set_target_properties(mgfpj PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

install(TARGETS mgfpj)
