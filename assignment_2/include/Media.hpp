#pragma once
#include <string>
#include <iostream> //TEMP used for cout

class Media {
public:
  Media(const std::string& title);
  virtual ~Media();

  virtual std::string prettyPrint();

  // int year;
  const std::string& title;
};
