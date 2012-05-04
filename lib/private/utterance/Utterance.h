#ifndef __UTTERANCE_H__
#define __UTTERANCE_H__

class Utterance {
 public:
  float* GetAudio() const;
  unsigned GetLength() const;
};

#endif

