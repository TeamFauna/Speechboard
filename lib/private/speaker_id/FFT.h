#ifndef __FFT_H__
#define __FFT_H__

#include <kiss_fft.h>
#include <vector>

class FFT {
 public:
  FFT(unsigned length);
  ~FFT();

  void ComputeSpectrum(float* audio, unsigned length, float* spectrum);
  void ComputeSpectrum(std::vector<float> audio, std::vector<float> spectrum);

 private:
  unsigned length_;

  kiss_fft_cfg fft_;
  kiss_fft_cfg ifft_;
};

#endif

