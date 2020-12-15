#pragma once
#include <string>
#include <iostream> //TEMP used for cout
#include <vector>

class Media {
public:
  Media();
  Media(const std::string& title);
  virtual ~Media() = 0;
  Media(const Media &other);

  bool operator==(const Media& other) const;
  bool operator!=(const Media& other) const;

  virtual std::string prettyPrint() const = 0;

protected:
  const std::string title;
};
