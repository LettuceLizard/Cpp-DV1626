#include "MediaManager.hpp"

MediaManager::MediaManager() {}

MediaManager::~MediaManager() {
  for (int i = 0; i < MediaInsert ; i++) {
    delete mediaArray[i];
  }
  delete[] mediaArray;

}

bool MediaManager::operator==(const MediaManager& other) const {
  for (int i = 0; i < MediaInsert; i++) {
    if (mediaArray[i] != other.mediaArray[i]) {
      return false;
    }
  }
  return true;
}

void MediaManager::addMedia(Media* media) {}

void MediaManager::addBook(const Book& book) {
  mediaArray[MediaInsert] = new Book(book);
  MediaInsert++;
}

void MediaManager::addVinyl(const Vinyl& vinyl) {
  mediaArray[MediaInsert] = new Vinyl(vinyl);
  MediaInsert++;
}

void MediaManager::addPs2Game(const Ps2Game& game) {
  mediaArray[MediaInsert] = new Ps2Game(game);
  MediaInsert++;
}

std::string MediaManager::printMedia() const {
  std::string allMedia;
  for (int i = 0; i < MediaInsert; i++) {
    if(dynamic_cast<Book*>(mediaArray[i]) != nullptr) {
      allMedia += dynamic_cast<Book*>(mediaArray[i])->getTitle();
    }
    if(dynamic_cast<Ps2Game*>(mediaArray[i]) != nullptr) {
      allMedia += dynamic_cast<Ps2Game*>(mediaArray[i])->getTitle();
    }
    if(dynamic_cast<Vinyl*>(mediaArray[i]) != nullptr) {
      allMedia += dynamic_cast<Vinyl*>(mediaArray[i])->getTitle();
    }
    allMedia += " ";
  }
  return allMedia;
}

std::vector<Book> MediaManager::getBooks() const {
  std::vector<Book> temp;
  for (int i = 0; i < MediaInsert; i++) {
    if(dynamic_cast<Book*>(mediaArray[i]) != nullptr) {
      temp.push_back(*dynamic_cast<Book*>(mediaArray[i]));
    }
  }
  return temp;
}
std::vector<Vinyl> MediaManager::getVinyls() const {
  std::vector<Vinyl> temp;
  for (int i = 0; i < MediaInsert; i++) {
    if(dynamic_cast<Vinyl*>(mediaArray[i]) != nullptr) {
      temp.push_back(*dynamic_cast<Vinyl*>(mediaArray[i]));
    }
  }
  return temp;
}
std::vector<Ps2Game> MediaManager::getPs2Games() const {
  std::vector<Ps2Game> temp;
  for (int i = 0; i < MediaInsert; i++) {
    if(dynamic_cast<Ps2Game*>(mediaArray[i]) != nullptr) {
      temp.push_back(*dynamic_cast<Ps2Game*>(mediaArray[i]));
    }
  }
  return temp;
}
