//
// Created by strafo on 16/05/19.
//
#include<minunit.h>
#include <complex>
#include <iostream>
#include <valarray>
#include <sys/time.h>
#include <fstream>
#include "fastFourierTransform.h"
#define TESTNUM 15 //24
using namespace std;
const double PI = 3.141592653589793238460;

void fft(CArray& x) ;
void ifft(CArray& x);
void dft(CArray& x);
struct timeval t0,t1;
size_t inputsize;
int *array;
Fft_Manager fft_manager=Fft_Manager();
CArray *data;
ofstream file;



MU_TEST(fft_test){
        //fft_manager.fft(*data,inputsize);
        //fft(*data);
        dft(*data);
}




MU_TEST_SUITE(fast_fourier_transform_test_suite){
        for (int i=TESTNUM-1;i>0;i--){
            inputsize=pow(2,i);
            array=new int[inputsize];
            for(int j=0;j<inputsize;j++){
                array[j]=rand()%2-1;
            }
            data=new CArray(*array,inputsize);
            fft_manager.prepare_tw(inputsize);
            gettimeofday(&t0, NULL);
            MU_RUN_TEST(fft_test);
            gettimeofday(&t1, NULL);
            file<< t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec)<<endl;
            delete []array;
            delete data;
        }
}



int main(){
    file.open("times.txt");
    MU_RUN_TEST(fast_fourier_transform_test_suite);
    MU_REPORT();
    file<<endl;
    for(int i=TESTNUM-1; i>0;i--){
        file<<pow(2,i)<<endl;
    }
    file.close();
    return minunit_status;
}


//FFT ALGO

void fft(CArray& x) {
    const size_t N = x.size();
    if (N <= 1) return;

    // divide
    CArray even = x[std::slice(0, N / 2, 2)];
    CArray odd = x[std::slice(1, N / 2, 2)];

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N / 2; ++k) {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

void ifft(CArray& x)
{
    x = x.apply(std::conj);
    fft( x );
    x = x.apply(std::conj);
    x /= x.size();
}

void dft(CArray& x){
    CArray out = CArray(x.size());
    for(int k=0;k<x.size();k++){
        out[k]=x[0];
        for(int n=1;n<x.size();n++){
            out[k]+=x[n]*polar(1.0, -2 * PI * k*n /x.size());
        }
    }
}