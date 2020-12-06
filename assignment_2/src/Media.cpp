#include "Media.hpp"

Media::Media(const std::string& title)
: title(title) {
  std::cout << "--------Constructing constructing Media" << std::endl;
}
Media::~Media() {
  std::cout << "--------Destroying deconstructing Media" << std::endl;
}

std::string Media::prettyPrint() {
  return "yeet";
}
