#include "Book.hpp"

Book::Book(const std::string& title, const std::string& author,
     const std::string& isbn, int pages, int edition)
      :Media(title), author(author), isbn(isbn){
        this->pages = pages;
        this->edition = edition;
        std::cout << "--------Creating constructing Book" <<'\n';

}
Book::~Book() {
  std::cout << "--------Destroying deconstructing Book" <<'\n';
}
const std::string& Book::getTitle() const {
  return title;
}

const std::string& Book::getAuthor() const{
  return author;
}

const std::string& Book::getIsbn() const{
  return isbn;
}

int Book::getPages() const {
  return pages;
}

int Book::getEdition() const {
  return edition;
}

std::string Book::prettyPrint() {
  return "override Media prettyPrint";
}
