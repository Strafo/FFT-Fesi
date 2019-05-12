#ifndef FAST_FOURIER_TRANSFORM_LIBRARY_H
#define FAST_FOURIER_TRANSFORM_LIBRARY_H

#include <complex>
#include <valarray>
#include <threadpool.h>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

class Fft_Manager
{
private:
    Complex **W= nullptr;
    size_t WSIZE=0;
    void init_twiddle_factor(int input_size);
    Complex get_twiddle_factor(const int &n,const int &k);
    void fft_aux(CArray& in,size_t n);

public:
    void fft(CArray& input,size_t size);
    void ifft(CArray& input);
    Fft_Manager();
    ~Fft_Manager();


};


#endif