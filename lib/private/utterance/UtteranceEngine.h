#ifndef __UTTERANCE_ENGINE_H__
#define __UTTERANCE_ENGINE_H__

#include <vector>

#include "Utterance.h"

class UtteranceEngine {
 public:
  std::vector<Utterance> GetUtterances(void* audio, unsigned length);
};

#endif

