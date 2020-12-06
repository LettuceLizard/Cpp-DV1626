#include "Track.hpp"

Track::Track(const std::string& name, const Time& length)
: name(name), length(length) {}
Track::~Track() {}

const std::string& Track::getName() const {
  return name;
}
const Time& Track::getLength() const {
  return length;
}
