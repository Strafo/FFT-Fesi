//
// Created by strafo on 08/05/19.
//
#ifndef FFT_FFTTEST_H
#define FFT_FFTTEST_H
#define PRINT_TEST
#define REPETITIONS 1
#define TEST test1
#define TODO
#include<minunit.h>
#include <complex>
#include <iostream>
#include <valarray>
#include <sys/time.h>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;


const double PI = 3.141592653589793238460;
Complex sinfunction[128]={0,0.243,0.4714,0.6716,0.8315,0.9415,0.9952,0.9892,0.9239,0.8032,0.6344,0.4276,0.1951,-0.0491,-0.2903,-0.5141,-0.7071,-0.8577,-0.9569,-0.9988,-0.9808,-0.904,-0.773,-0.5957,-0.3827,-0.1467,0.098,0.3369,0.5556,0.741,0.8819,0.97,1,0.97,0.8819,0.741,0.5556,0.3369,0.098,-0.1467,-0.3827,-0.5957,-0.773,-0.904,-0.9808,-0.9988,-0.9569,-0.8577,-0.7071,-0.5141,-0.2903,-0.0491,0.1951,0.4276,0.6344,0.8032,0.9239,0.9892,0.9952,0.9415,0.8315,0.6716,0.4714,0.243,0,-0.243,-0.4714,-0.6716,-0.8315,-0.9415,-0.9952,-0.9892,-0.9239,-0.8032,-0.6344,-0.4276,-0.1951,0.0491,0.2903,0.5141,0.7071,0.8577,0.9569,0.9988,0.9808,0.904,0.773,0.5957,0.3827,0.1467,-0.098,-0.3369,-0.5556,-0.741,-0.8819,-0.97,-1,-0.97,-0.8819,-0.741,-0.5556,-0.3369,-0.098,0.1467,0.3827,0.5957,0.773,0.904,0.9808,0.9988,0.9569,0.8577,0.7071,0.5141,0.2903,0.0491,-0.1951,-0.4276,-0.6344,-0.8032,-0.9239,-0.9892,-0.9952,-0.9415,-0.8315,-0.6716,-0.4714,-0.243};
Complex test1[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
size_t inputsize;
struct timeval t0, t1;





void print_time(timeval& t1 ,timeval& t0,std::string testname){
#ifndef PRINT_TEST
    static FILE* nul = fopen( "NUL", "w" );
    *stdout=*nul;
    setvbuf( stdout, NULL, _IONBF, 0 );
#endif
    printf("Test \"%s\" did %u calls in %.2g seconds\n", testname.c_str(),REPETITIONS,
           t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));
}

#endif //FFT_FFTTEST_H
