#pragma once
#include "Media.hpp"

class Book : public Media {

public:
  Book(const std::string& title, const std::string& author,
     const std::string& isbn, int pages, int edition);

   const std::string& getTitle() const;
   const std::string& getAuthor() const;
   const std::string& getIsbn() const;
   int getPages() const;
   int getEdition() const;

   std::string prettyPrint() override;

  ~Book();

private:
      // const std::string& title;
      const std::string& author;
      const std::string& isbn;
      int pages, edition;
};
