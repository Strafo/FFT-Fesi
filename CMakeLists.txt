cmake_minimum_required(VERSION 3.10)
project(FFT)

set(CMAKE_CXX_STANDARD 11)

add_library(FFT fastFourierTransform.cpp fastFourierTransform.h)
add_executable(FFTTEST fastFourierTransform.cpp)
target_link_libraries(FFTTEST FFT)