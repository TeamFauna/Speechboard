#ifndef __TEXT_H__
#define __TEXT_H__

#include <string>

using std::string;

class Identity {
 public:
  Identity() :
      identity_(0) {}

  Identity(unsigned identity) :
      identity_(identity) {}

  Identity(unsigned identity, const string& name) :
      identity_(identity),
      name_(name) {}

  unsigned GetIdentity() const { return identity_; }
  const string& GetName() const { return name_; }

 private:
  unsigned identity_;
  string name_;
};

class Text {
 public:
  Text() {}

  Text(const Identity& identity) :
      identity_(identity) {}

  Text(const Identity& identity, const string& text) {
      identity_(identity),
      text_(text) {}
  
  const Identity& GetIdentity() const { return identity_; }
  const string& GetText() const { return text_; }

 private:
  Identity identity_;
  string text_;
};

#endif

