#include <vector>
#include <cmath>

void IIR_LPF(double fc, double Q, std::vector<double> &a, std::vector<double> &b) {
  fc = std::tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fc) / Q + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2))) / numerator;
  b[0] = (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) / numerator;
  b[1] = (8.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) / numerator;
  b[2] = (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) / numerator;
}

void IIR_HPF(double fc, double Q, std::vector<double> &a, std::vector<double> &b) {
  fc = tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fc) / Q + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2))) / numerator;
  b[0] = 1 / numerator;
  b[1] = -2 / numerator;
  b[2] = 1 / numerator;
}

void IIR_BPF(double fc, double Q, std::vector<double> &a, std::vector<double> &b) {
  fc = tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fc) / Q + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2))) / numerator;
  b[0] = (2 * M_PI * fc / Q) / numerator;
  b[1] = 0;
  b[2] = -(2 * M_PI * fc / Q) / numerator;
}

void IIR_BEF(double fc, double Q, std::vector<double> &a, std::vector<double> &b) {
  fc = tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fc) / Q + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2))) / numerator;
  b[0] = (4 * std::pow(M_PI, 2) * std::pow(fc, 2) + 1) / numerator;
  b[1] = (8 * std::pow(M_PI, 2) * std::pow(fc, 2) - 2) / numerator;
  b[2] = (4 * std::pow(M_PI, 2) * std::pow(fc, 2) + 1) / numerator;
}

void IIR_LOW_SHELVING(double fc, double Q, double g, std::vector<double> &a, std::vector<double> &b) {
  fc = std::tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - ((2.0 * M_PI * fc) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2))) / numerator;
  b[0] = (1 + std::sqrt(1 + g) * ((2 * M_PI * fc) / Q) + 4.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) / numerator;
  b[1] = (8.0 * std::pow(M_PI, 2) * std::pow(fc, 2) * (1 + g) - 2) / numerator;
  b[2] = (1 - std::sqrt(1 + g) * ((2 * M_PI * fc) / Q) + 4.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) / numerator;
}

void IIR_HIGH_SHELVING(double fc, double Q, double g, std::vector<double> &a, std::vector<double> &b) {
  fc = std::tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - ((2.0 * M_PI * fc) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2))) / numerator;
  b[0] = ((1 + g) + std::sqrt(1 + g) * ((2 * M_PI * fc) / Q) + 4.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) / numerator;
  b[1] = (8 * std::pow(M_PI, 2) * std::pow(fc, 2) - 2 * (1 + g)) / numerator;
  b[2] = ((1 + g) - std::sqrt(1 + g) * ((2 * M_PI * fc) / Q) + 4.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) / numerator;
}

void IIR_PEAKING(double fc, double Q, double g, std::vector<double> &a, std::vector<double> &b) {
  fc = std::tan(M_PI * fc) / (2.0 * M_PI);

  double numerator = 1.0 + ((2.0 * M_PI * fc) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) - 2.0) / numerator;
  a[2] = (1.0 - ((2.0 * M_PI * fc) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fc, 2))) / numerator;
  b[0] = (1 + ((2 * M_PI * fc) / Q) * (1 + g) + 4.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) / numerator;
  b[1] = (8.0 * std::pow(M_PI, 2) * std::pow(fc, 2) - 2) / numerator;
  b[2] = (1 - ((2 * M_PI * fc) / Q) * (1 + g) + 4.0 * std::pow(M_PI, 2) * std::pow(fc, 2)) / numerator;
}
