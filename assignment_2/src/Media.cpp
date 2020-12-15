#include "Media.hpp"

Media::Media(const std::string& title)
: title(title) {}

Media::~Media() {}

Media::Media(const Media &other) : title(other.title) {}

bool Media::operator==(const Media& other) const {
  return title == other.title;
}
bool Media::operator!=(const Media& other) const {
  return title != other.title;
}
