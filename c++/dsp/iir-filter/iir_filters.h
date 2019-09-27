#include <vector>
#include <cmath>

void IIR_LPF(double fd, double Q, std::vector<double> &a, std::vector<double> &b) {
  double fa = std::tan(M_PI * fd) / (2.0 * M_PI);
  double numerator = 1.0 + ((2.0 * M_PI * fa) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fa) / Q + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2))) / numerator;
  b[0] = (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) / numerator;
  b[1] = (8.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) / numerator;
  b[2] = (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) / numerator;
}

void IIR_HPF(double fd, double Q, std::vector<double> &a, std::vector<double> &b) {
  double fa = tan(M_PI * fd) / (2.0 * M_PI);
  double numerator = 1.0 + ((2.0 * M_PI * fa) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fa) / Q + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2))) / numerator;
  b[0] = 1 / numerator;
  b[1] = -2 / numerator;
  b[2] = 1 / numerator;
}

void IIR_BPF(double fd, double Q, std::vector<double> &a, std::vector<double> &b) {
  double fa = tan(M_PI * fd) / (2.0 * M_PI);
  double numerator = 1.0 + ((2.0 * M_PI * fa) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fa) / Q + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2))) / numerator;
  b[0] = (2 * M_PI * fa / Q) / numerator;
  b[1] = 0;
  b[2] = -(2 * M_PI * fa / Q) / numerator;
}

void IIR_BEF(double fd, double Q, std::vector<double> &a, std::vector<double> &b) {
  double fa = tan(M_PI * fd) / (2.0 * M_PI);
  double numerator = 1.0 + ((2.0 * M_PI * fa) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) - 2.0) / numerator;
  a[2] = (1.0 - (2.0 * M_PI * fa) / Q + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2))) / numerator;
  b[0] = (4 * std::pow(M_PI, 2) * std::pow(fa, 2) + 1) / numerator;
  b[1] = (8 * std::pow(M_PI, 2) * std::pow(fa, 2) - 2) / numerator;
  b[2] = (4 * std::pow(M_PI, 2) * std::pow(fa, 2) + 1) / numerator;
}

void IIR_LOW_SHELVING(double fd, double Q, double g, std::vector<double> &a, std::vector<double> &b) {
  double fa = std::tan(M_PI * fd) / (2.0 * M_PI);
  double numerator = 1.0 + ((2.0 * M_PI * fa) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) - 2.0) / numerator;
  a[2] = (1.0 - ((2.0 * M_PI * fa) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2))) / numerator;
  b[0] = (1 + std::sqrt(1 + g) * ((2 * M_PI * fa) / Q) + 4.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) / numerator;
  b[1] = (8.0 * std::pow(M_PI, 2) * std::pow(fa, 2) * (1 + g) - 2) / numerator;
  b[2] = (1 - std::sqrt(1 + g) * ((2 * M_PI * fa) / Q) + 4.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) / numerator;
}

void IIR_HIGH_SHELVING(double fd, double Q, double g, std::vector<double> &a, std::vector<double> &b) {
  double fa = std::tan(M_PI * fd) / (2.0 * M_PI);
  double numerator = 1.0 + ((2.0 * M_PI * fa) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) - 2.0) / numerator;
  a[2] = (1.0 - ((2.0 * M_PI * fa) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2))) / numerator;
  b[0] = ((1 + g) + std::sqrt(1 + g) * ((2 * M_PI * fa) / Q) + 4.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) / numerator;
  b[1] = (8 * std::pow(M_PI, 2) * std::pow(fa, 2) - 2 * (1 + g)) / numerator;
  b[2] = ((1 + g) - std::sqrt(1 + g) * ((2 * M_PI * fa) / Q) + 4.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) / numerator;
}

void IIR_PEAKING(double fd, double Q, double g, std::vector<double> &a, std::vector<double> &b) {
  double fa = std::tan(M_PI * fd) / (2.0 * M_PI);
  double numerator = 1.0 + ((2.0 * M_PI * fa) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2));

  a[0] = 1.0;
  a[1] = ((8.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) - 2.0) / numerator;
  a[2] = (1.0 - ((2.0 * M_PI * fa) / Q) + (4.0 * std::pow(M_PI, 2) * std::pow(fa, 2))) / numerator;
  b[0] = (1 + ((2 * M_PI * fa) / Q) * (1 + g) + 4.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) / numerator;
  b[1] = (8.0 * std::pow(M_PI, 2) * std::pow(fa, 2) - 2) / numerator;
  b[2] = (1 - ((2 * M_PI * fa) / Q) * (1 + g) + 4.0 * std::pow(M_PI, 2) * std::pow(fa, 2)) / numerator;
}
