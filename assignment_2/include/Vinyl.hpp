#pragma once
#include "Media.hpp"
#include "Track.hpp"
#include "VinylTypes.hpp"

class Vinyl : public Media {
public:
  Vinyl(const std::string& title, VinylTypes type, int year,
      const std::string& artist, const Time& runtime);
  ~Vinyl();

  // void addTrack(const Track& track);
  const std::string& getTitle() const;
  int getYear() const;
  VinylTypes getType() const;
  const std::string& getArtist() const;
  const Time& getRuntime() const;
  // const std::vector<Track>& getTracks() const;

private:
  // const std::string& title;
  VinylTypes type;
  int year;
  const std::string& artist;
  const Time& runtime;

};
