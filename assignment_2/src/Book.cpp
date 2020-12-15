#include "Book.hpp"

Book::Book(std::vector<std::string>& commandList)
        :Media(commandList[1]), author(commandList[2]),
        isbn(commandList[3]) {
          this->pages = std::stoi(commandList[4]);
          this->edition = std::stoi(commandList[5]);
        }


Book::Book(const std::string& title, const std::string& author,
     const std::string& isbn, int pages, int edition)
      :Media(title), author(author), isbn(isbn){
        this->pages = pages;
        this->edition = edition;
}
Book::Book(const Book &other)
: Media(other.title), author(other.author),
 isbn(other.isbn), pages(other.pages),
 edition(other.edition) {}

const std::string& Book::getTitle() const {return title;}

const std::string& Book::getAuthor() const{return author;}

const std::string& Book::getIsbn() const{
  return isbn;
}

int Book::getPages() const {
  return pages;
}

int Book::getEdition() const {
  return edition;
}

bool Book::operator==(const Book& other) const {
  return title == other.title && author == other.author && isbn == other.isbn && pages == other.pages && edition == other.edition;
}
bool Book::operator!=(const Book& other) const {
  return title != other.title || author != other.author || isbn != other.isbn || pages != other.pages || edition != other.edition;
}

std::string Book::prettyPrint() const {
  return title + " " + author + " " + isbn + " " + std::to_string(pages) + " " + std::to_string(edition);
}
