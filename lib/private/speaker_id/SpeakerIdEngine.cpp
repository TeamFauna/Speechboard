#include "SpeakerIdEngine.h"

#include <cmath>

#include "../utterance/Utterance.h"

#define FFT_LEN 1024

SpeakerIdEngine::SpeakerIdEngine() {
  fft = kiss_fft_alloc(FFT_LEN, 0, NULL, NULL);
  ifft = kiss_fft_alloc(FFT_LEN, 1, NULL, NULL);
}

SpeakerIdEngine::~SpeakerIdEngine() {
  kiss_fft_free(fft);
  kiss_fft_free(ifft);
}

const Identity& SpeakerIdEngine::GetIdentity(const Utterance& utterance) {
  kiss_fft_cpx input[FFT_LEN];
  kiss_fft_cpx output[FFT_LEN];

  float spectrum[FFT_LEN/2];
  memset(spectrum, 0, FFT_LEN/2 * sizeof(float));

  float* audio = utterance.GetAudio();
  unsigned length = utterance.GetLength();
  unsigned index = 0;
  unsigned segments = ceil(length / 1024.0f);

  while (length >= FFT_LEN) {
    for (unsigned i = 0; i < FFT_LEN; i++) {
      input[i].r = audio[index + i];
      input[i].i = 0;
    }

    kiss_fft(fft, input, output);

    for (unsigned j = 0; j < FFT_LEN/2; j++) {
      spectrum[j] += sqrt(output[j].r * output[j].r +
                          output[j].i * output[j].i) / segments;
    }

    length -= FFT_LEN;
    index += FFT_LEN;
  }

  if (length > 0) {
    for (unsigned i = 0; i < length; i++) {
      input[i].r = audio[index + i];
      input[i].i = 0;
    }
    memset(input + length, 0, (FFT_LEN - length) * sizeof(kiss_fft_cpx));

    kiss_fft(fft, input, output);

    for (unsigned j = 0; j < FFT_LEN/2; j++) {
      spectrum[j] += sqrt(output[j].r * output[j].r +
                          output[j].i * output[j].i) / segments;
    }
  }

  //
}

void SpeakerIdEngine::NameIdentity(const Identity& identity,
                                   const std::string& name) {
  //
}

