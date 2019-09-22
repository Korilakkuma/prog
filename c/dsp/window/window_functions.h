#include <math.h>

void hanning_window(double *w, int N) {
  if ((N % 2) == 0) {
    for (int n = 0; n < N; n++) {
      w[n] = 0.5 - (0.5 * cos((2.0 * M_PI * n) / N));
    }
  } else {
    for (int n = 0; n < N; n++) {
      w[n] = 0.5 - (0.5 * cos((2.0 * M_PI * (n - 0.5)) / N));
    }
  }
}
