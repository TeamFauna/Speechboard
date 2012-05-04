#ifndef __SPEAKER_ID_ENGINE_H__
#define __SPEAKER_ID_ENGINE_H__

#include <string>

class Identity;
class Utterance;

class SpeakerIdEngine {
 public:
  SpeakerIdEngine();
  ~SpeakerIdEngine();

  const Identity& GetIdentity(const Utterance& utterance);
  void NameIdentity(const Identity& identity, const std::string& name);

 private:
  kiss_fft_cfg fft;
  kiss_fft_cfg ifft;
};

#endif

