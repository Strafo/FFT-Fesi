#include "fftTest.h"


void fft(CArray& x) ;
void ifft(CArray& x);

MU_TEST(fft_test){
    CArray *data[REPETITIONS];
    for (auto & j : data) {
        j=new CArray(TEST,inputsize);
    }

    gettimeofday(&t0, NULL);
    for(int i = 0; i < REPETITIONS; i++){
        fft(*(data[i]));
    }
    gettimeofday(&t1, NULL);
    print_time(t1,t0,"fft");
    for (auto & j : data) {
        delete j;
    }
}

MU_TEST(ifft_test){
    CArray *data[REPETITIONS];
    CArray input(TEST,inputsize);
    fft(input);

    for (auto & j : data) {
        j=new CArray(input);
    }

    gettimeofday(&t0, NULL);
    for(int i = 0; i < REPETITIONS; i++){
        ifft(*data[i]);
    }
    gettimeofday(&t1, NULL);
    print_time(t1,t0,"ifft");

    for (auto & j : data) {
        delete j;
    }
}

MU_TEST(print_test){
    CArray* fft_result;
    CArray* ifft_result;

    fft_result=new CArray(TEST,inputsize);
    fft(*fft_result);
    std::cout << std::endl << "fft" << std::endl;
    for (int i = 0; i < inputsize; ++i)
    {
        std::cout << fft_result->operator[](i) << std::endl;
    }

    ifft_result=fft_result;
    ifft(*ifft_result);
    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < inputsize; ++i)
    {
        std::cout << ifft_result->operator[](i) << std::endl;
    }
}

MU_TEST_SUITE(simple_fft_test_suite){
    MU_RUN_TEST(fft_test);
    MU_RUN_TEST(ifft_test);
    MU_RUN_TEST(print_test);
}

int main()
{
    inputsize=(sizeof(TEST)/sizeof(*TEST));
    std::cout<<"SIMPLE TEST size:"<<inputsize<<std::endl;
    MU_RUN_TEST(simple_fft_test_suite);
    MU_REPORT();
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
