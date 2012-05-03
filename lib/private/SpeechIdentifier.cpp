#include "SpeechIdentifierImpl.h"

using std::string;
using std::vector;

const vector<Text>* SpeechIdentifierImpl::SendAudio(void* audio,
                                                    unsigned length) {
  vector<Utterance> utterances = utterance_engine_.GetUtterances(audio, length);
  
  vector<Text>* texts = new vector<Text>();
  vector<Utterance>::iterator it;
  for (it = utterances.begin(); it < utterances.end(); ++it) {
    Identity identity = speaker_id_engine_.GetIdentity(*it);
    string text = stt_engine_.GetText(*it);
    texts->push_back(Text(identity, text));
  }

  return texts;
}

void SpeechIdentifierImpl::NameIdentity(const Identity& identity,
                                        const string& name) {
  speaker_id_engine_.NameIdentity(identity, name);
}

