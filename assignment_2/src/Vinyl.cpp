#include "Vinyl.hpp"

Vinyl::Vinyl(std::vector<std::string>& commandList)
    :Media(commandList[1]), year(std::stoi(commandList[3])),
     artist(commandList[4]), runtime(std::stoi(commandList[5]),
    std::stoi(commandList[6])){
       if (commandList[2] == "LONG_PLAY")
        this->type = VinylTypes::LONG_PLAY;
      else
        this->type = VinylTypes::EXTENDED_PLAY;
;
}


Vinyl::Vinyl(const std::string& title, VinylTypes type, int year,
      const std::string& artist, const Time& runtime)
      : Media(title), type(type), artist(artist), runtime(runtime) {
        this->year = year;
      }

Vinyl::~Vinyl() {}

Vinyl::Vinyl(const Vinyl& other)
: Media(other.title), tracks(other.tracks),
  type(other.type), year(other.year),
  artist(other.artist), runtime(other.runtime) {}

void Vinyl::addTrack(const Track& track) {
  tracks.push_back(track);
}
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
const std::vector<Track>& Vinyl::getTracks() const {
  return tracks;
}

bool Vinyl::operator==(const Vinyl& other) const {
  return title == other.title && type == other.type && year == other.year &&
  artist == other.artist && getRuntime() == other.getRuntime() &&  tracks.size() == other.tracks.size();
}
bool Vinyl::operator!=(const Vinyl& other) const {
  return title != other.title || type != other.type || year != other.year ||
  artist != other.artist || getRuntime() != other.getRuntime() || tracks.size() != other.tracks.size();
}


std::string Vinyl::prettyPrint() const {
  return title + " " + std::to_string(year) + " " + artist ;
}
