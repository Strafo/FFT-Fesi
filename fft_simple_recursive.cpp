#include <iostream>
#include "fft.h"

/**DIT ALGO FOR FFT (decimate in time)**/
const double PI = 3.14159265358979323846264338328L;
using namespace std;
void Fft_Manager::fft_aux(CArray& x, size_t N2) {
    const size_t N = x.size();
    if (N <= 1) return;

    // divide
    CArray even = x[std::slice(0, N / 2, 2)];
    CArray odd = x[std::slice(1, N / 2, 2)];

    // conquer
    fft(even,0);
    fft(odd,0);

    // combine
    for (size_t k = 0; k < N / 2; ++k) {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}
void Fft_Manager::fft(CArray& input, size_t size) {
    fft_aux(input,size);
}
void Fft_Manager::ifft(CArray& x)
{
    x = x.apply(std::conj);
    fft( x,x.size() );
    x = x.apply(std::conj);
    x /= x.size();
}








void Fft_Manager::prepare_tw(size_t inputsize) {
}



/**CONSTRUCTOR/DESTRUCTOR**/
Fft_Manager::Fft_Manager() {

}


Fft_Manager::~Fft_Manager(){
}

/**IMPLEMEMENTATION**/

void Fft_Manager::init_twiddle_factor(int input_size){
}

inline Complex Fft_Manager::get_twiddle_factor(const int &n,const int &k){
}
