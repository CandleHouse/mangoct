# mangoct-linux

<p align="center">
    <img src="demo.png"></img>
</p>

This is a fork version of [mangoct](https://github.com/ustcfdm/mangoct) tomography reconstruction toolkit, with compilation toolchain transferred from Visual Studio to cross-platform CMake. Then, **working on Linux is possible**. And since no OS related libraries and features are used, **this might also compile on Windows** (but not tested yet).

## Prerequisites

- GCC with `<filesystem>` or `<experimental/filesystem>` and C++ 17 support
- CMake
- NVIDIA GPU with CUDA > 10

## Installation

1. **Install [RapidJSON](https://github.com/Tencent/rapidjson) first.** (Dependency of mangoct)

   - Clone or download

       ```sh
       git clone git@github.com:Tencent/rapidjson.git --depth=1
       # or `wget` the zip file
       ```
   
   - Use [CMake](http://cmake.org/) to configurate.
   
     - Set `CMAKE_INSTALL_PREFIX`, `CMAKE_INSTALL_DIR`.
     
     - Set `INCLUDE_INSTALL_DIR`, `LIB_INSTALL_DIR`, `DOC_INSTALL_DIR`.
     
     - Check `RAPIDJSON_BUILD_CXX17`.
     
     - Uncheck `RAPIDJSON_BUILD_DOC`, `RAPIDJSON_BUILD_EXAMPLES`, `RAPIDJSON_BUILD_TESTS`.
     
     - Modify other options as you need.
   
   - Generate, go to the generated path, and
   
       ```sh
       make
       make install
       ```
   
   - Check `<CMAKE_INSTALL_PREFIX>/include/rapidjson` has headers inside.
   
   - *FYI: Since RapidJSON is header-only, just copy `include/rapidjson` from source code might also work. No need to bother CMake.*

2. **Compile mangoct.**

   - Clone or download

     ```sh
     git clone git@github.com:z0gSh1u/mangoct-linux.git
     # or `wget` the zip file
     ```

   - Use [CMake](http://cmake.org/) to configurate.

     - Set `CUDA_TOOLKIT_ROOT_DIR` to somewhere `/usr/local/cuda-*.*`, configure.

     - Set `CMAKE_CUDA_COMPILER` according to `CUDA_NVCC_EXECUTABLE`, configure.

     - Set `CUDA_TOOLKIT_ROOT_DIR` again, configure. Make sure the right CUDA is selected if there are multiple CUDAs on your system. Most `CUDA_*_LIBRARY` should points to somewhere in your CUDA installation path.

     - Set `CMAKE_INSTALL_PREFIX` to the path compiled binary file should be saved.

     - RapidJSON should be automatically found by CMake. If not, set `RapidJSON_DIR` yourself.

     - You may need to remove `stdc++fs` library link if your compiler fully supports `<filesystem>` header with only `-std=c++17` flag.

       ```cmake
       # mgfpj/CMakeLists.txt and mgfbp/CMakeLists.txt
       target_link_libraries(<project_name>
           rapidjson
           ${CUDA_LIBRARIES}
           stdc++fs # Remove this line for GCC > 8.2 which fully supports <filesystem>
       )
       ```

     - Modify other options as you need.

   - Generate, go to the generated path, and

     ```sh
     make
     make install
     ```

   - Congratulations! mangoct executables (mgfpj, mgfbp) will compile to `<CMAKE_INSTALL_PREFIX>/bin/`.

## Usage

Please refer to the [upstream Windows version of mangoct](https://github.com/ustcfdm/mangoct) for detail.

- Forward projection using mgfpj.

  ```sh
  ./mgfpj config_mgfpj.jsonc
  ```

- FBP / FDK reconstruction using mgfbp.

  ```sh
  ./mgfbp config_mgfbp.jsonc
  ```

## Current Upstream Version

mangoct-linux is forked from [ustcfdm/mangoct](https://github.com/ustcfdm/mangoct). To support Linux compilation, some breaking modifications are made, so `Fetch upstream` and `git cherry-pick` doesn't work quite well. The upstream updates are manually merged into mangoct-linux periodically.

Current version is up to upstream commit [8091b5d207de577413bdc52b19e6b844ee943ef0](https://github.com/ustcfdm/mangoct/commit/8091b5d207de577413bdc52b19e6b844ee943ef0).

