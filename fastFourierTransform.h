#ifndef FAST_FOURIER_TRANSFORM_LIBRARY_H
#define FAST_FOURIER_TRANSFORM_LIBRARY_H

#include <complex>
#include <valarray>
#include <threadpool.h>

class Fft_Manager
{
    private:
    thread_pool_t* threadPool;
    int n_thread;
    public:
    void fft_multithread(std::valarray<std::complex<double>>& valarray);

    Fft_Manager(int threads_number);
    ~Fft_Manager();


};


#endif