#ifndef __FFT_H__
#define __FFT_H__

#include <kiss_fft.h>

class FFT {
 public:
  FFT(unsigned length);
  ~FFT();

  void ComputeSpectrum(float* audio, unsigned length, float* spectrum);

 private:
  unsigned length_;

  kiss_fft_cfg fft_;
  kiss_fft_cfg ifft_;
};

#endif

