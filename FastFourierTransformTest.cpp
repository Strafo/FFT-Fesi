#include <iostream>
#include <complex>
#include <valarray>
#include "fastFourierTransform.h"
#include "minunit.h"
#define PRINT_TEST 1

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
using namespace std;
const Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
CArray data;
Fft_Manager fft_manager(2);


MU_TEST(fft_test) {
    fft_manager.fft_multithread(data);
    //fft(data);
    cout << "fft" << endl;
    for (int i = 0; i < 8; ++i) {
        cout << data[i] << endl;
    }
}


MU_TEST(ifft_test){
    //fft_manager.ifft(data);
    cout << endl << "ifft" << endl;
    for (int i = 0; i < 8; ++i) {
        cout << data[i] << endl;
    }
}







MU_TEST_SUITE(fast_fourier_transform_test_suite){
    data=valarray<Complex>(test, 8);

    MU_RUN_TEST(fft_test);//test per la fft
    MU_RUN_TEST(ifft_test);//test per la ifft


}








int main(){
#ifndef PRINT_TEST
    static FILE* nul = fopen( "NUL", "w" );
    *stdout=*nul;
    setvbuf( stdout, NULL, _IONBF, 0 );
#endif
    MU_RUN_TEST(fast_fourier_transform_test_suite);
    MU_REPORT();
    return minunit_status;
}
