#include "FFT.h"

using std::vector;

FILE* test;

FFT::FFT(unsigned length) {
  test = fopen("test.txt", "w");

  length_ = length;
  fft_ = kiss_fft_alloc(length, 0, NULL, NULL);
  ifft_ = kiss_fft_alloc(length, 1, NULL, NULL);
}

FFT::~FFT() {
  fclose(test);

  kiss_fft_free(fft_);
  kiss_fft_free(ifft_);
}

// XXX: FIXME
#define ABS(f) (f >= 0.0f ? f : -f)

void Normalize(float* audio, unsigned length) {
  float max = 0.0f;

  for (unsigned i = 0; i < length; i++) {
    if (ABS(audio[i]) > max) {
      max = ABS(audio[i]);
    }
  }

  for (unsigned i = 0; i < length; i++) {
    audio[i] /= max;
  }
}

void FFT::ComputeSpectrum(float* audio, unsigned audio_length,
                          float* spectrum) {
  kiss_fft_cpx input[length_];
  kiss_fft_cpx output[length_];

  Normalize(audio, audio_length);

  memset(spectrum, 0, length_/2 * sizeof(float));

  unsigned index = 0;
  unsigned segments = ceil(audio_length / 1024.0f);

  while (audio_length >= length_) {
    for (unsigned i = 0; i < length_; i++) {
      input[i].r = audio[index + i];
      input[i].i = 0;
    }

    kiss_fft(fft_, input, output);

    for (unsigned j = 0; j < length_/2; j++) {
      spectrum[j] += sqrt(output[j].r * output[j].r +
                          output[j].i * output[j].i) / segments;
    }

    audio_length -= length_;
    index += length_;
  }

  if (audio_length > 0) {
    for (unsigned i = 0; i < audio_length; i++) {
      input[i].r = audio[index + i];
      input[i].i = 0;
    }
    memset(input + audio_length, 0,
           (length_ - audio_length) * sizeof(kiss_fft_cpx));

    kiss_fft(fft_, input, output);

    for (unsigned j = 0; j < length_/2; j++) {
      spectrum[j] += sqrt(output[j].r * output[j].r +
                          output[j].i * output[j].i) / segments;
    }
  }
}

void FFT::ComputeSpectrum(vector<float> audio, vector<float>& spectrum) {
  ComputeSpectrum(&audio[0], audio.size(), &spectrum[0]);

  for (unsigned i = 0; i < spectrum.size(); i++) {
    fprintf(test, "%f,", spectrum[i]);
  }
  fputs("\n", test);

}

