#include <vector>

void TimeStretch(
  double rate,
  std::vector<double> &in,
  std::vector<double> &out,
  int fs,
  int length
) {
  int template_size = static_cast<int>(fs * 0.01);
  int p_min = static_cast<int>(fs * 0.005);
  int p_max = static_cast<int>(fs * 0.02);

  std::vector<double> x(template_size);
  std::vector<double> y(template_size);
  std::vector<double> r(p_max + 1);

  int offset0 = 0;
  int offset1 = 0;

  while ((offset0 + (2 + p_max)) < length) {
    for (int n = 0; n < template_size; n++) {
      x[n] = in[offset0 + n];
    }

    double max_of_r = 0.0;
    int p = p_min;

    for (int m = p_min; m <= p_max; m++) {
      for (int n = 0; n < template_size; n++) {
        y[n] = in[offset0 + m + n];
      }

      r[m] = 0.0;

      for (int n = 0; n < template_size; n++) {
        r[m] += y[n] * x[n];
      }

      if (r[m] > max_of_r) {
        max_of_r = r[m];
        p = m;
      }
    }

    for (int n = 0; n < p; n++) {
      out[offset1 + n] = (in[offset0 + n] * (p - n)) / p;
      out[offset1 + n] += (in[offset0 + p + n] * n) / p;
    }

    int q = static_cast<int>((p / (rate - 1.0)) + 0.5);

    for (int n = p; n < q; n++) {
      if ((offset0 + p + n) >= length) {
        break;
      }

      out[offset1 + n] = in[offset0 + p + n];
    }

    offset0 += p + q;
    offset1 += q;
  }
}
