#include <iostream>
#include <stack>
#include "fft.h"

/**DIT ALGO FOR FFT (decimate in time)**/
const double PI = 3.14159265358979323846264338328L;
const double TAU=PI*2;
using namespace std;

void free_twiddle_factors(size_t ws,Complex **&w);



struct Stack_fft{
    CArray* array;
    size_t N;
};

/**CONSTRUCTOR/DESTRUCTOR**/
Fft_Manager::Fft_Manager() {

}


Fft_Manager::~Fft_Manager(){
    free_twiddle_factors(WSIZE,W);
}

/**IMPLEMEMENTATION**/

void Fft_Manager::init_twiddle_factor(int input_size){
    double theta=TAU/(double)input_size;
    if(input_size>WSIZE) {//aggiorno i tw factor sse quelli precedenti non erano sufficenti
        cout<<"init tw"<<input_size<<endl;

        WSIZE=input_size;

        if(W == nullptr){
            free_twiddle_factors(WSIZE,W);
        }
        W = new Complex *[WSIZE/2];
        for (int k = 0; k < input_size/2; k++) {
            W[k] = new Complex(cos(-theta * k), sin(-theta * k));
        }
    }
}

inline Complex Fft_Manager::get_twiddle_factor(const int &n,const int &k){
    int passo=WSIZE/n;
    return  Complex(*W[k*passo]);
}



void Fft_Manager::fft_aux(CArray& input, size_t N) {
    stack<Stack_fft*> stack;
    Stack_fft* sp=new Stack_fft;
    Stack_fft* argp;
    sp->array=&input;
    sp->N=N;
    stack.push(sp);
    while (!stack.empty()) {
        sp=stack.top();
        stack.pop();
        //caso base
        if (N <= 1)return;
        size_t NH = sp->N / 2;
        CArray even = sp->array->operator[](std::slice(0, NH, 2));
        CArray odd = sp->array->operator[](std::slice(1, NH, 2));

        argp=new Stack_fft;
        argp->array=&odd;
        argp->N=NH;
        stack.push(argp);
        argp=new Stack_fft;
        argp->array=&even;
        argp->N=NH;
        stack.push(argp);
        for (size_t k = 0; k < NH; k++) {
            Complex t = get_twiddle_factor(N, k) * odd[k];
            input[k] = even[k] + t;
            input[k + NH] = even[k] - t;
        }
    }
}

void Fft_Manager::fft(CArray& input, size_t size) {
    init_twiddle_factor(size);
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
    init_twiddle_factor(inputsize);
}


void free_twiddle_factors(size_t ws,Complex **&w){
    if(w== nullptr)return;
    for(int i=0; i<ws/2; ++i)
        delete w[i];
    delete[] w;
    w= nullptr;
}