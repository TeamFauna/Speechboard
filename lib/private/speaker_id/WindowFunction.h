#ifndef __WINDOW_FUNCTION_H__
#define __WINDOW_FUNCTION_H__

class WindowFunction {
 public:
  static void Hann(float* data, unsigned length);
  static void Hamming(float* data, unsigned length);
  static void Gaussian(float* data, unsigned length, float sigma);
  static void BartlettHann(float* data, unsigned length);
  static void Blackman(float* data, unsigned length, float alpha);
};

#endif

