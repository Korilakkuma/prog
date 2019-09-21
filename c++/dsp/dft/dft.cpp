#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include "../wave/wave.h"
#include "../window/window_functions.h"
#include "dft.h"

enum {
  N = 64
};

int main(int argc, char **argv) {
  MONO_PCM pcm;

  std::vector<std::complex<double>> x(N);
  std::vector<std::complex<double>> X(N);
  std::vector<double> w;

  WAVE::wave_read(&pcm, "sample.wav");

  w = hanning_window(N);

  for (int n = 0; n < N; n++) {
    double real;

    if (argc > 1) {
      real = w[n] * pcm.s[n];
    } else {
      real = pcm.s[n];
    }

    x[n] = std::complex<double>(real, 0.0);
  }

  X = DFT(x, N);

  for (int k = 0; k < N; k++) {
    std::cout << "[" << k << "]" << " " <<  X[k].real() << " + j" << std::fixed << X[k].imag() << std::endl;
  }
}
