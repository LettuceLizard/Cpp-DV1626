#pragma once
#include "Media.hpp"

class Book : public Media {

public:
  Book();
  Book(std::vector<std::string>& commandList);
  Book(const std::string& title, const std::string& author,
     const std::string& isbn, int pages, int edition);

     Book(const Book& other);

   const std::string& getTitle() const;
   const std::string& getAuthor() const;
   const std::string& getIsbn() const;
   int getPages() const;
   int getEdition() const;

   bool operator==(const Book& other) const;
   bool operator!=(const Book& other) const;


   std::string prettyPrint() const override;

private:
      // const std::string& title;
      const std::string author;
      const std::string isbn;
      int pages, edition;
};
