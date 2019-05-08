#include <assert.h>
#include "fastFourierTransform.h"


const double PI = 3.141592653589793238460;
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
using namespace std;

void* ifft(CArray& array);
void* fft(CArray& array);

Fft_Manager::Fft_Manager(int threads_number) {
    n_thread=threads_number;
    threadPool=create_fixed_size_thread_pool(n_thread);//todo check return value
}

Fft_Manager::~Fft_Manager(){
    shut_down_thread_pool(threadPool);
    destroy_thread_pool(threadPool);
}


void Fft_Manager::fft_multithread(CArray &valarray) {

    future_t* future_array[2];
    const size_t N=valarray.size();
    if(N<=1) {
        return ;
    }
    assert(start_thread_pool(threadPool)==0);//todo

    CArray even = valarray[std::slice(0, N/2, 2)];
    future_array[0]=add_job_tail(threadPool, reinterpret_cast<void *(*)(void *)>(fft),&even );

    CArray  odd = valarray[std::slice(1, N/2, 2)];
    future_array[1]=add_job_tail(threadPool, reinterpret_cast<void *(*)(void *)>(fft),&odd );

    for(int i=0;i<2;i++){
        get_future(future_array[i]);//todo get ret value
        destroy_future(future_array[i]);
    }
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        valarray[k    ] = even[k] + t;
        valarray[k+N/2] = even[k] - t;
    }
    pause_thread_pool(threadPool);
}

void* fft(CArray& array){
    const size_t N=array.size();
    if(N<=1) {
        return nullptr;
    }
    // divide
    CArray even = array[std::slice(0, N/2, 2)];
    CArray  odd = array[std::slice(1, N/2, 2)];

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        array[k    ] = even[k] + t;
        array[k+N/2] = even[k] - t;
    }
    return nullptr;
}


void* ifft(CArray& array){
// conjugate the complex numbers

    array=array.apply(conj);

    // forward fft
    fft(array);

    // conjugate the complex numbers again
    array= array.apply(conj);

    // scale the numbers
    array /= array.size();
    return nullptr;
}
