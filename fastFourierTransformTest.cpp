#include "fftTest.h"
#include "fastFourierTransform.h"
#define THREAD_POOL_SIZE 2


using namespace std;

Fft_Manager fft_manager(THREAD_POOL_SIZE);

int rep=0;

MU_TEST(fft_test){
    CArray *data[REPETITIONS];
    for (auto & j : data) {
        j=new CArray(TEST,inputsize);
    }

    gettimeofday(&t0, NULL);
    for(int i = 0; i < REPETITIONS; i++){
        rep=i;
        fft_manager.fft_multithread(*(data[i]));
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
    fft_manager.fft_multithread(input);
#ifndef TODO
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
#endif
}

MU_TEST(print_test){
    CArray* fft_result;
    CArray* ifft_result;

    fft_result=new CArray(TEST,inputsize);
    fft_manager.fft_multithread(*fft_result);
    std::cout << std::endl << "fft" << std::endl;
    for (int i = 0; i < inputsize; ++i)
    {
        std::cout << fft_result->operator[](i) << std::endl;
    }
#ifndef TODO
    ifft_result=fft_result;
    ifft(*ifft_result);
    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < inputsize; ++i)
    {
        std::cout << ifft_result->operator[](i) << std::endl;
    }
#endif
}






MU_TEST_SUITE(fast_fourier_transform_test_suite){
    MU_RUN_TEST(fft_test);
    MU_RUN_TEST(ifft_test);
    MU_RUN_TEST(print_test);
}








int main(){
    inputsize=(sizeof(TEST)/sizeof(*TEST));
    std::cout<<"MULTIT TEST size:"<<inputsize<<std::endl;
    MU_RUN_TEST(fast_fourier_transform_test_suite);
    MU_REPORT();
    return minunit_status;
}
