#pragma once
#include "Media.hpp"

class Ps2Game : public Media {
public:
  Ps2Game(const std::string& title, const std::string& studio, int year);
  const std::string& getTitle() const;
  const std::string& getStudio() const;
  int getYear() const;

private:
  // const std::string &title;
  const std::string &studio;
  int year;
};
