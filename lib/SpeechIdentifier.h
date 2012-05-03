#ifndef __SPEECHLIB_H__
#define __SPEECHLIB_H__

#include <string>

#include "SpeechIdentifierImpl.h"
#include "Text.h"

using std::string;

class SpeechIdentifier {
 public:
  Text* SendAudio(void* audio) { return impl.SendAudio(audio); }
  void NameIdentity(unsigned identity, const string& name) {
    impl.NameIdentity(identity, name);
  }

 private:
  SpeechIdentifierImpl impl;
};

#endif

