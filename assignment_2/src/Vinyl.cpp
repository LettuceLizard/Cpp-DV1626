#include "Vinyl.hpp"

Vinyl::Vinyl(const std::string& title, VinylTypes type, int year,
      const std::string& artist, const Time& runtime)
      : Media(title), type(type), artist(artist), runtime(runtime) {
        this->year = year;
      }

Vinyl::~Vinyl() {}

// void Vinyl::addTrack(const Track& track) {
//   //tredje objectet
// }
const std::string& Vinyl::getTitle() const {
  return title;
}
int Vinyl::getYear() const {
  return year;
}
VinylTypes Vinyl::getType() const {
  return type;
}
const std::string& Vinyl::getArtist() const {
  return artist;
}
const Time& Vinyl::getRuntime() const {
  return runtime;

}
// const std::vector<Track>& Vinyl::getTracks() const {
//   //returnerar track som blivigt tillagda i addTrack(track)
// }
