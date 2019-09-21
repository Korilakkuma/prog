#include <vector>
#include <cmath>
#include <complex>

std::vector<std::complex<double>> DFT(std::vector<std::complex<double>> &x, int N) {
  std::vector<std::complex<double>> X(N);

  for (int n = 0; n < N; n++) {
    for (int k = 0; k < N; k++) {
      double real =  std::cos((2 * M_PI * k * n) / N);
      double imag = -std::sin((2 * M_PI * k * n) / N);

      X[k] = std::complex<double>(((real * x[n].real()) + (imag * x[n].imag())), ((real * x[n].imag()) + (imag * x[n].real())));
    }
  }

  return X;
}
