#ifndef __TEXT_H__
#define __TEXT_H__

#include <string>

class Identity {
 public:
  Identity(unsigned identity) :
      identity_(identity) {}

  Identity(unsigned identity, const std::string& name) :
      identity_(identity),
      name_(name) {}

  unsigned GetIdentity() const { return identity_; }
  const std::string& GetName() const { return name_; }

 private:
  unsigned identity_;
  std::string name_;
};

class Text {
 public:
  Text(const Identity& identity, const std::string& text) :
      identity_(identity),
      text_(text) {}
  
  const Identity& GetIdentity() const { return identity_; }
  const std::string& GetText() const { return text_; }

 private:
  Identity identity_;
  std::string text_;
};

#endif

