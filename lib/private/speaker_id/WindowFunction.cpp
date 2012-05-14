#include "WindowFunction.h"

#include <cmath>

using std::vector;

const float PI = 3.1415926535;

void WindowFunction::Hann(float* data, unsigned length) {
  for (unsigned i = 0; i < length; i++) {
    float val = 0.5 * (1 - cos((2 * PI * i) / (length - 1)));
    data[i] = val * data[i];
  }
}

void WindowFunction::Hann(vector<float> data) {
  Hann(&data[0], data.size());
}

void WindowFunction::Hamming(float* data, unsigned length) {
  for (unsigned i = 0; i < length; i++) {
    float val = 0.54 - 0.46*cos((2 * PI * i) / (length - 1));
    data[i] = val * data[i];
  }
}

void WindowFunction::Gaussian(float* data, unsigned length, float sigma) {
  for (unsigned i = 0; i < length; i++) {
    float val = exp(-0.5 * powf((i - (length-1)/2) / (sigma*(length-1)/2), 2));
    data[i] = val * data[i];
  }
}

void WindowFunction::BartlettHann(float* data, unsigned length) {
  for (unsigned i = 0; i < length; i++) {
    float val = 0.62
              - 0.48 * std::abs((i / (length - 1)) - 0.5)
              - 0.38 * cos(2*PI*i / (length - 1));
    data[i] = val * data[i];
  }
}

void WindowFunction::Blackman(float* data, unsigned length,
                              float alpha = 0.16) {
  for (unsigned i = 0; i < length; i++) {
    float val = ((1 - alpha) / 2)
              - 0.5 * cos((2*PI*i) / (length - 1))
              + (alpha / 2) * cos((4*PI*i) / (length - 1));
    data[i] = val * data[i];
  }
}

