#include <iostream>
#include <vector>
#include <cmath>
#include "../wave/wave.h"
#include "../window/window_functions.h"

enum {
  N = 64
};

int main(int argc, char **argv) {
  MONO_PCM pcm;

  std::vector<double> x_real, x_imag;
  std::vector<double> X_real, X_imag;
  std::vector<double> w;

  double W_real, W_imag;

  WAVE::wave_read(&pcm, "sample.wav");

  long length = N;

  x_real.reserve(length);
  x_imag.reserve(length);
  X_real.reserve(N);
  X_imag.reserve(N);

  w = Hanning_window(N);

  for (int n = 0; n < length; n++) {
    if (argc > 1) {
      x_real[n] = w[n] * pcm.s[n];
    } else {
      x_real[n] = pcm.s[n];
    }

    x_imag[n] = 0.0;
  }

  for (int k = 0; k < N; k++) {
    X_real[k] = 0.0;
    X_imag[k] = 0.0;
  }

  for (int n = 0; n < length; n++) {
    for (int k = 0; k < N; k++) {
      W_real = std::cos(2 * M_PI * k * n / N);
      W_imag = -std::sin(2 * M_PI * k * n / N);

      X_real[k] += (W_real * x_real[n]) + (W_imag * x_imag[n]);
      X_imag[k] += (W_real * x_imag[n]) + (W_imag * x_real[n]);
    }
  }

  for (int k = 0; k < N; k++) {
    if (X_imag[k] >= 0) {
      std::cout << "[" << k << "]" << " " <<  X_real[k] << " + j" << std::fixed << X_imag[k] << std::endl;
    } else {
      std::cout << "[" << k << "]" << " " <<  X_real[k] << " - j" << std::fabs(X_imag[k]) << std::endl;
    }
  }
}
