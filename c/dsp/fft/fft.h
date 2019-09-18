#include <math.h>

int pow2(int n) {
  if (n == 0) {
    return 1;
  }

  return 2 << (n - 1);
}

void FFT(double *x_real, double *x_imag, int N) {
  int n, m, r;
  int rest;
  int number_of_stages = log2(N);

  int *index;

  double a_real, a_imag;
  double b_real, b_imag;
  double c_real, c_imag;
  double tmp_real, tmp_imag;

  for (int stage = 1; stage <= number_of_stages; stage++) {
    for (int i = 0; i < pow2(stage - 1); i++) {
      rest = number_of_stages - stage;

      for (int j = 0; j < pow2(rest); j++) {
        n = i * pow2(rest + 1) + j;
        m = pow2(rest) + n;
        r = j * pow2(stage - 1);

        a_real = x_real[n];
        a_imag = x_imag[n];
        b_real = x_real[m];
        b_imag = x_imag[m];
        c_real = cos((2.0 * M_PI * r) / N);
        c_imag = -sin((2.0 * M_PI * r) / N);

        if (stage < number_of_stages) {
          x_real[n] = a_real + b_real;
          x_imag[n] = a_imag + b_imag;
          x_real[m] = (c_real * (a_real - b_real)) - (c_imag * (a_imag - b_imag));
          x_imag[m] = (c_real * (a_imag - b_imag)) - (c_imag * (a_real - b_real));
        } else {
          x_real[n] = a_real + b_real;
          x_imag[n] = a_imag + b_imag;
          x_real[m] = a_real - b_real;
          x_imag[m] = a_imag - b_imag;
        }
      }
    }
  }

  index = (int *)calloc(N, sizeof(int));

  for (int stage = 1; stage <= number_of_stages; stage++) {
    rest = number_of_stages - stage;

    for (int i = 0; i < pow2(stage - 1); i++) {
      index[pow2(stage - 1) + i] = index[i] + pow2(rest);
    }
  }

  for (int k = 0; k < N; k++) {
    if (index[k] <= k) {
      continue;
    }

    tmp_real = x_real[index[k]];
    tmp_imag = x_imag[index[k]];

    x_real[index[k]] = x_real[k];
    x_imag[index[k]] = x_imag[k];

    x_real[k] = tmp_real;
    x_imag[k] = tmp_imag;
  }

  free(index);
}
