#include "Ps2Game.hpp"

Ps2Game::Ps2Game(std::vector<std::string>& commandList)
: Media(commandList[1]), studio(commandList[2]),
  year(std::stoi(commandList[3])){}

Ps2Game::Ps2Game(const std::string& title, const std::string& studio, int year)
: Media(title), studio(studio) {
  this->year = year;
}
Ps2Game::Ps2Game(const Ps2Game& other)
  :Media(other.title), studio(other.studio),
  year(other.year) {}
const std::string& Ps2Game::getTitle() const {
  return title;
}
const std::string& Ps2Game::getStudio() const {
  return studio;
}
int Ps2Game::getYear() const {
  return year;
}

bool Ps2Game::operator==(const Ps2Game& other) const {
  return title == other.title && studio == other.studio && year == other.year;
}
bool Ps2Game::operator!=(const Ps2Game& other) const {
  return title != other.title || studio != other.studio || year != other.year;
}


std::string Ps2Game::prettyPrint() const {
  return title + " " + studio + " " + std::to_string(year);
}
