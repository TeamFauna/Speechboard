#ifndef __STT_ENGINER_H__
#define __STT_ENGINER_H__

#include <string>

class Utterance;

class STTEngine {
 public:
  const std::string& GetText(const Utterance& utterance);
};

#endif

