#include <math.h>

void IIR_LPF(double fc, double Q, double *a, double *b) {
  fc = tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * pow(M_PI, 2) * pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * pow(M_PI, 2) * pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fc) / Q + (4.0 * pow(M_PI, 2) * pow(fc, 2))) / numerator;
  b[0] = (4.0 * pow(M_PI, 2) * pow(fc, 2)) / numerator;
  b[1] = (8.0 * pow(M_PI, 2) * pow(fc, 2)) / numerator;
  b[2] = (4.0 * pow(M_PI, 2) * pow(fc, 2)) / numerator;
}

void IIR_HPF(double fc, double Q, double *a, double *b) {
  fc = tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * pow(M_PI, 2) * pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * pow(M_PI, 2) * pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fc) / Q + (4.0 * pow(M_PI, 2) * pow(fc, 2))) / numerator;
  b[0] = 1 / numerator;
  b[1] = -2 / numerator;
  b[2] = 1 / numerator;
}

void IIR_BPF(double fc, double Q, double *a, double *b) {
  fc = tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * pow(M_PI, 2) * pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * pow(M_PI, 2) * pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fc) / Q + (4.0 * pow(M_PI, 2) * pow(fc, 2))) / numerator;
  b[0] = (2 * M_PI * fc / Q) / numerator;
  b[1] = 0;
  b[2] = -(2 * M_PI * fc / Q) / numerator;
}

void IIR_BEF(double fc, double Q, double *a, double *b) {
  fc = tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * pow(M_PI, 2) * pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * pow(M_PI, 2) * pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fc) / Q + (4.0 * pow(M_PI, 2) * pow(fc, 2))) / numerator;
  b[0] = (4 * pow(M_PI, 2) * pow(fc, 2) + 1) / numerator;
  b[1] = (8 * pow(M_PI, 2) * pow(fc, 2) - 2) / numerator;
  b[2] = (4 * pow(M_PI, 2) * pow(fc, 2) + 1) / numerator;
}
