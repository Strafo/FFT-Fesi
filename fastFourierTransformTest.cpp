#include <iostream>
#include <complex>
#include <valarray>
#include "fastFourierTransform.h"
#include <minunit.h>
#define PRINT_TEST

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
using namespace std;
const Complex test1[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
const Complex test[]={0,0.243,0.4714,0.6716,0.8315,0.9415,0.9952,0.9892,0.9239,0.8032,0.6344,0.4276,0.1951,-0.0491,-0.2903,-0.5141,-0.7071,-0.8577,-0.9569,-0.9988,-0.9808,-0.904,-0.773,-0.5957,-0.3827,-0.1467,0.098,0.3369,0.5556,0.741,0.8819,0.97,1,0.97,0.8819,0.741,0.5556,0.3369,0.098,-0.1467,-0.3827,-0.5957,-0.773,-0.904,-0.9808,-0.9988,-0.9569,-0.8577,-0.7071,-0.5141,-0.2903,-0.0491,0.1951,0.4276,0.6344,0.8032,0.9239,0.9892,0.9952,0.9415,0.8315,0.6716,0.4714,0.243,0,-0.243,-0.4714,-0.6716,-0.8315,-0.9415,-0.9952,-0.9892,-0.9239,-0.8032,-0.6344,-0.4276,-0.1951,0.0491,0.2903,0.5141,0.7071,0.8577,0.9569,0.9988,0.9808,0.904,0.773,0.5957,0.3827,0.1467,-0.098,-0.3369,-0.5556,-0.741,-0.8819,-0.97,-1,-0.97,-0.8819,-0.741,-0.5556,-0.3369,-0.098,0.1467,0.3827,0.5957,0.773,0.904,0.9808,0.9988,0.9569,0.8577,0.7071,0.5141,0.2903,0.0491,-0.1951,-0.4276,-0.6344,-0.8032,-0.9239,-0.9892,-0.9952,-0.9415,-0.8315,-0.6716,-0.4714,-0.243};
size_t  size1;
CArray data;
Fft_Manager fft_manager(2);


MU_TEST(fft_test) {
    fft_manager.fft_multithread(data);
    //fft(data);
    cout << "fft" << endl;
    for (int i = 0; i < size1; ++i) {
        cout << data[i] << endl;
    }
}


MU_TEST(ifft_test){
    //fft_manager.ifft(data);
    cout << endl << "ifft" << endl;
    for (int i = 0; i < size1; ++i) {
        cout << data[i] << endl;
    }
}







MU_TEST_SUITE(fast_fourier_transform_test_suite){
    data=valarray<Complex>(test, size1);

    MU_RUN_TEST(fft_test);//test per la fft
    MU_RUN_TEST(ifft_test);//test per la ifft

}








int main(){
#ifndef PRINT_TEST
    static FILE* nul = fopen( "NUL", "w" );
    *stdout=*nul;
    setvbuf( stdout, NULL, _IONBF, 0 );
#endif
    size1=(sizeof(test)/sizeof(*test));

    cout<<"TEST:"<<endl;
    MU_RUN_TEST(fast_fourier_transform_test_suite);
    MU_REPORT();
    return minunit_status;
}
