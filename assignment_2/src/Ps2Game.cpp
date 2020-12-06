#include "Ps2Game.hpp"

Ps2Game::Ps2Game(const std::string& title, const std::string& studio, int year)
: Media(title), studio(studio) {
  this->year = year;
}

const std::string& Ps2Game::getTitle() const {
  return title;
}
const std::string& Ps2Game::getStudio() const {
  return studio;
}
int Ps2Game::getYear() const {
  return year;
}
