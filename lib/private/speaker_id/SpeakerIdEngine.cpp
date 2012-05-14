#include "SpeakerIdEngine.h"

#include <cmath>

#include "../utterance/Utterance.h"

#define FFT_LEN 1024

SpeakerIdEngine::SpeakerIdEngine() {
  fft(FFT_LEN);
}

const Identity& SpeakerIdEngine::GetIdentity(const Utterance& utterance) {
  float spectrum[FFT_LEN/2];
  fft.ComputeSpectrum(utterance.GetAudio(), utterance.GetLength(), spectrum);

  //
}

void SpeakerIdEngine::NameIdentity(const Identity& identity,
                                   const std::string& name) {
  //
}

