#ifndef __WINDOW_FUNCTION_H__
#define __WINDOW_FUNCTION_H__

#include <vector>

class WindowFunction {
 public:
  static void Hann(float* data, unsigned length);
  static void Hann(std::vector<float> data);

  static void Hamming(float* data, unsigned length);
  static void Hamming(std::vector<float> data);

  static void Gaussian(float* data, unsigned length, float sigma);
  static void Gaussian(std::vector<float> data, float sigma);

  static void BartlettHann(float* data, unsigned length);
  static void BartlettHann(std::vector<float> data);

  static void Blackman(float* data, unsigned length, float alpha);
  static void Blackman(std::vector<float> data, float alpha);
};

#endif

