#ifndef __SPEAKER_ID_ENGINE_H__
#define __SPEAKER_ID_ENGINE_H__

#include <string>

class Identity;
class Utterance;

class SpeakerIdEngine {
 public:
  const Identity& GetIdentity(const Utterance& utterance);
  void NameIdentity(const Identity& identity, const std::string& name);
};

#endif

