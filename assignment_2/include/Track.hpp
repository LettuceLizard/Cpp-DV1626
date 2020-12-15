#pragma once
#include "Time.hpp"
#include <string>


class Track {
public:
  Track(const std::string& name, const Time& length);
  ~Track();

  const std::string& getName() const;
  const Time& getLength() const;
private:
  const std::string name;
  const Time length;
};
