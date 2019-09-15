#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../wave/wave.h"

enum {
  N = 64
};

int main(void) {
  MONO_PCM pcm;

  double *x_real, *x_imag;
  double *X_real, *X_imag;
  double W_real, W_imag;

  mono_wave_read(&pcm, "sample.wav");

  long length = N;

  x_real = (double *)calloc(length, sizeof(double));
  x_imag = (double *)calloc(length, sizeof(double));
  X_real = (double *)calloc(N, sizeof(double));
  X_imag = (double *)calloc(N, sizeof(double));

  for (int n = 0; n < length; n++) {
    x_real[n] = pcm.s[n];
    x_imag[n] = 0.0;
  }

  for (int n = 0; n < length; n++) {
    for (int k = 0; k < N; k++) {
      W_real = cos(2 * M_PI * k * n / N);
      W_imag = -sin(2 * M_PI * k * n / N);

      X_real[k] += (W_real * x_real[n]) + (W_imag * x_imag[n]);
      X_imag[k] += (W_real * x_imag[n]) + (W_imag * x_real[n]);
    }
  }

  for (int k = 0; k < N; k++) {
    if (X_imag[k] >= 0) {
      printf("[%d] %f + j%f\n", k, X_real[k], X_imag[k]);
    } else {
      printf("[%d] %f - j%f\n", k, X_real[k], fabs(X_imag[k]));
    }
  }

  free(pcm.s);
  free(x_real);
  free(x_imag);
  free(X_real);
  free(X_imag);

  return 0;
}
