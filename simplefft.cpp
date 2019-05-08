#include <complex>
#include <iostream>
#include <valarray>

const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

// Cooley–Tukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
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

// inverse fft (in-place)
void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);

    // forward fft
    fft( x );

    // conjugate the complex numbers again
    x = x.apply(std::conj);

    // scale the numbers
    x /= x.size();
}

int main()
{
    const Complex test[]={0,0.243,0.4714,0.6716,0.8315,0.9415,0.9952,0.9892,0.9239,0.8032,0.6344,0.4276,0.1951,-0.0491,-0.2903,-0.5141,-0.7071,-0.8577,-0.9569,-0.9988,-0.9808,-0.904,-0.773,-0.5957,-0.3827,-0.1467,0.098,0.3369,0.5556,0.741,0.8819,0.97,1,0.97,0.8819,0.741,0.5556,0.3369,0.098,-0.1467,-0.3827,-0.5957,-0.773,-0.904,-0.9808,-0.9988,-0.9569,-0.8577,-0.7071,-0.5141,-0.2903,-0.0491,0.1951,0.4276,0.6344,0.8032,0.9239,0.9892,0.9952,0.9415,0.8315,0.6716,0.4714,0.243,0,-0.243,-0.4714,-0.6716,-0.8315,-0.9415,-0.9952,-0.9892,-0.9239,-0.8032,-0.6344,-0.4276,-0.1951,0.0491,0.2903,0.5141,0.7071,0.8577,0.9569,0.9988,0.9808,0.904,0.773,0.5957,0.3827,0.1467,-0.098,-0.3369,-0.5556,-0.741,-0.8819,-0.97,-1,-0.97,-0.8819,-0.741,-0.5556,-0.3369,-0.098,0.1467,0.3827,0.5957,0.773,0.904,0.9808,0.9988,0.9569,0.8577,0.7071,0.5141,0.2903,0.0491,-0.1951,-0.4276,-0.6344,-0.8032,-0.9239,-0.9892,-0.9952,-0.9415,-0.8315,-0.6716,-0.4714,-0.243};
    const Complex test1[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };

    size_t size=(sizeof(test)/sizeof(*test));
    std::cout<<"size:"<<size<<std::endl;
    CArray data(test,(size));

    // forward fft
    fft(data);

    std::cout << "fft" << std::endl;
    for (int i = 0; i < size; ++i)
    {
        std::cout << data[i] << std::endl;
    }

    // inverse fft
    ifft(data);

    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < size; ++i)
    {
        std::cout << data[i] << std::endl;
    }
    return 0;
}