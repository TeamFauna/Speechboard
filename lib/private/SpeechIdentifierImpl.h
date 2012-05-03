#ifndef __SPEECH_IDENTIFIER_IMPL_H__
#define __SPEECH_IDENTIFIER_IMPL_H__

#include <string>
#include <vector>

#include "speaker_id/SpeakerIdEngine.h"
#include "stt/STTEngine.h"
#include "Text.h"
#include "utterance/UtteranceEngine.h"

class SpeechIdentifierImpl {
 public:
  const std::vector<Text>* SendAudio(void* audio, unsigned length);
  void NameIdentity(const Identity& identity, const std::string& name);

 private:
  UtteranceEngine utterance_engine_;
  SpeakerIdEngine speaker_id_engine_;
  STTEngine stt_engine_;
};

#endif

