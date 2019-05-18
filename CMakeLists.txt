cmake_minimum_required(VERSION 3.14)
project(FFT)
set(CMAKE_CXX_STANDARD 11)
#sub-modules
include(FetchContent)
FetchContent_Declare(
        minunit
        GIT_REPOSITORY https://github.com/siu/minunit.git
        GIT_TAG        origin/master
)


FetchContent_MakeAvailable(minunit )
include_directories(${PROJECT_SOURCE_DIR}/cmake-build-debug/_deps/minunit-src)



#library
add_library(FFT_RECURSIVE_PRECOMP_TW fft_recursive_precomp_tw.cpp fft.h)

add_library(FFT_RECURSIVE_SIMPLE fft_simple_recursive.cpp fft.h)


#executable time
add_executable(TIME_FFT_RECURSIVE_PRECOMP_TW timeTest.cpp)
target_link_libraries(TIME_FFT_RECURSIVE_PRECOMP_TW  FFT_RECURSIVE_PRECOMP_TW)


#add_executable(FFT_RECURSIVE_SIMPLE timeTest.cpp)
#target_link_libraries(TIME_FFT_RECURSIVE_SIMPLE  FFT_RECURSIVE_SIMPLE)


