#ifndef __SPEECHLIB_H__
#define __SPEECHLIB_H__

#include <string>
#include <vector>

#include "SpeechIdentifierImpl.h"
#include "Text.h"

class SpeechIdentifier {
 public:
  const std::vecotr<Text>* SendAudio(void* audio, unsigned length) {
    return impl.SendAudio(audio, length);
  }

  void NameIdentity(const Identity& identity, const find::string& name) {
    impl.NameIdentity(identity, name);
  }

 private:
  SpeechIdentifierImpl impl;
};

#endif

