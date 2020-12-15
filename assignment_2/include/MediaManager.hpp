#pragma once
#include "Book.hpp"
#include "Ps2Game.hpp"
#include "Vinyl.hpp"
#include <vector>

class MediaManager {
public:
  MediaManager();
  ~MediaManager();

  bool operator==(const MediaManager& other) const;
  bool operator!=(const MediaManager& other) const;

  void addMedia(Media* media);
  void addBook(const Book& book);
  void addVinyl(const Vinyl& vinyl);
  void addPs2Game(const Ps2Game& game);

  std::string printMedia() const;
  std::vector<Book> getBooks() const;
  std::vector<Vinyl> getVinyls() const;
  std::vector<Ps2Game> getPs2Games() const;
private:
  int MediaInsert = 0;
  const int MEDIA_STORAGE = 420;
  Media** mediaArray = new Media*[MEDIA_STORAGE];

};
