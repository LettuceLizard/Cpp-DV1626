#pragma once
#include "Media.hpp"
#include "Track.hpp"
#include "VinylTypes.hpp"
#include <vector>

class Vinyl : public Media {
public:
  Vinyl();
  Vinyl(std::vector<std::string>& commandList);
  Vinyl(const std::string& title, VinylTypes type, int year,
      const std::string& artist, const Time& runtime);
  ~Vinyl();

  Vinyl(const Vinyl& other);

  void addTrack(const Track& track);
  const std::string& getTitle() const;
  int getYear() const;
  VinylTypes getType() const;
  const std::string& getArtist() const;
  const Time& getRuntime() const;
  const std::vector<Track>& getTracks() const;

  bool operator==(const Vinyl& other) const;
  bool operator!=(const Vinyl& other) const;


  std::string prettyPrint() const override;


private:
  // const std::string& title;
  std::vector<Track > tracks;
  VinylTypes type;
  int year;
  const std::string artist;
  const Time runtime;

};
