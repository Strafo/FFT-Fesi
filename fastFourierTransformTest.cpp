#include "fftTest.h"
#include "fastFourierTransform.h"
#include <array>


using namespace std;

Fft_Manager fft_manager=Fft_Manager();


MU_TEST(fft_test){
    CArray *data[REPETITIONS];
    for (auto & j : data) {
        j=new CArray(TEST,inputsize);
    }

    gettimeofday(&t0, NULL);
    for(int i = 0; i < REPETITIONS; i++){
        fft_manager.fft(*(data[i]),(*(data[i])).size());
    }
    gettimeofday(&t1, NULL);
    print_time(t1,t0,"fft");
    for (auto & j : data) {
        delete j;
    }
}

MU_TEST(ifft_test){
#ifndef TODO
    CArray *data[REPETITIONS];
    CArray input(TEST,inputsize);
    fft_manager.fft(input);

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
    CArray fft_result= CArray(TEST,inputsize);
    fft_manager.fft(fft_result,fft_result.size());
    std::cout << std::endl << "fft" << std::endl;
    for (int i = 0; i < inputsize; ++i)
    {
        std::cout << fft_result[i] << std::endl;
    }

    //ifft
    fft_manager.ifft(fft_result);
    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < inputsize; ++i)
    {
        std::cout << fft_result.operator[](i) << std::endl;
    }
}

MU_TEST_SUITE(fast_fourier_transform_test_suite){
    MU_RUN_TEST(print_test);
    //MU_RUN_TEST(fft_test);
    //MU_RUN_TEST(ifft_test);
}



int main(){
    inputsize=(sizeof(TEST)/sizeof(*TEST));
    std::cout<<"MULTIT TEST size:"<<inputsize<<std::endl;
    MU_RUN_TEST(fast_fourier_transform_test_suite);
    MU_REPORT();
    return minunit_status;
}
