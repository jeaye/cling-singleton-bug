cmake_minimum_required(VERSION 3.5)

# Cling needs at least C++14; so does this demo.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Building as separate project.
project(cling-demo)

# This project needs cling.
find_package(Clang REQUIRED CONFIG HINTS "${Cling_DIR}/lib/cmake/clang" NO_DEFAULT_PATH)
find_package(Cling REQUIRED HINTS "${Cling_DIR}/lib/cmake/cling")

# The project has one binary:
add_executable(cling-demo src/main.cpp)

target_include_directories(cling-demo PUBLIC "include")

# ...which links against clingInterpreter (and its dependencies).
target_link_libraries(cling-demo clingInterpreter)
target_include_directories(cling-demo PUBLIC ${CLING_INCLUDE_DIRS})
target_include_directories(cling-demo PUBLIC ${CLANG_INCLUDE_DIRS})
target_include_directories(cling-demo PUBLIC ${LLVM_INCLUDE_DIRS})

# Provide LLVMDIR to cling-demp.cpp:
target_compile_options(cling-demo PUBLIC -DLLVMDIR="${LLVM_BINARY_DIR}")

set_target_properties(cling-demo PROPERTIES ENABLE_EXPORTS 1)
