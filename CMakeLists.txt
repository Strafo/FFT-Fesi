cmake_minimum_required(VERSION 3.14)
project(FFT)
set(CMAKE_CXX_STANDARD 11)
find_package(Threads)
#sub-modules
include(FetchContent)
FetchContent_Declare(
        Thread-Pool-C
        GIT_REPOSITORY https://github.com/Strafo/Thread-Pool-C.git
        GIT_TAG        origin/master
)
FetchContent_Declare(
        minunit
        GIT_REPOSITORY https://github.com/siu/minunit.git
        GIT_TAG        origin/master
)


FetchContent_MakeAvailable(minunit Thread-Pool-C )
include_directories(${PROJECT_SOURCE_DIR}/cmake-build-debug/_deps/thread-pool-c-src/src)
include_directories(${PROJECT_SOURCE_DIR}/cmake-build-debug/_deps/minunit-src)
#library
add_library(FFT fastFourierTransform.cpp fastFourierTransform.h)
target_link_libraries(FFT ${PROJECT_SOURCE_DIR}/cmake-build-debug/_deps/thread-pool-c-build/src/libThreadPool.a )
target_link_libraries(FFT ${PROJECT_SOURCE_DIR}/cmake-build-debug/_deps/thread-pool-c-build/src/libhl_linklist/libLinkListLib.a )
target_link_libraries(FFT ${CMAKE_THREAD_LIBS_INIT} )

#test
add_executable(FFTTEST fastFourierTransformTest.cpp )
target_link_libraries(FFTTEST FFT)

#temp test
add_executable(SIMPLEFFT simplefft.cpp)
add_executable(TIMESFFT timeTest.cpp)
target_link_libraries(TIMESFFT FFT)

