#pragma once
#include "Media.hpp"

class Ps2Game : public Media {
public:
  Ps2Game();
  Ps2Game(std::vector<std::string>& commandList);
  Ps2Game(const std::string& title, const std::string& studio, int year);
  Ps2Game(const Ps2Game& other) ;

  const std::string& getTitle() const;
  const std::string& getStudio() const;
  int getYear() const;

  bool operator==(const Ps2Game& other) const;
  bool operator!=(const Ps2Game& other) const;


  std::string prettyPrint() const override;

private:
  // const std::string &title;
  const std::string studio;
  int year;
};
