#include "Book.hpp"
#include "Ps2Game.hpp"
#include "Vinyl.hpp"

#include "VinylTypes.hpp"
#include "Track.hpp"
#include "Time.hpp"

#include "MediaManager.hpp"

#include <sstream>
#include <iterator>

// void createCommandList(const std::string& line, std::vector<std::string>& commandList) {
//   bool ignoreSpace = false;
//   bool ignoreChr = false;
//   std::string command;
//
//   std::cout << line << std::endl;
//
//   for (int i = 0; i < line.size(); i++) {
//     // set to ignore space
//     if(line[i] == '\n' || line[i] == '"' || line[i] == '\r' || line[i] == ' ') {
//       ignoreChr = true;
//     }
//     // if the chr is space and lastchr!=" and ignoreSpace=false
//     if(line[i] == ' ' && line[i-1] != '"' && ignoreSpace == false) {
//       std::cout << "ignore space false" << std::endl;
//       commandList.push_back(command);
//       command.clear();
//     }
//     // end of full command
//     if (line[i] == '"' && ignoreSpace == true) {
//       std::cout << "ignore space true" << std::endl;
//       ignoreSpace = false;
//       commandList.push_back(command);
//       command.clear();
//     }
//     // if ignchr = false exception if ignoreSpace == true and
//     if(ignoreChr == false) {
//       command += line[i];
//     }
//     if(ignoreChr && ignoreSpace && line[i] == ' ')
//       command += line[i];
//
//     // this is the begining to ignore space
//     if(line[i] == '"' && ignoreSpace == false) {
//       ignoreSpace = true;
//     }
//     ignoreChr = false;
//   }
//   commandList.push_back(command);
// }

int main() {
  std::string userCommand;
  MediaManager manager;
  // std::vector<std::string> commandList;


  std::cout << "Welcome to mediamanager" << std::endl;
  std::cout << "COMMANDS:              " << std::endl;
  std::cout << "q quit" << std::endl;
  std::cout << "addBook title author isbn pages edition" << std::endl;
  std::cout << "addPs2Game title studio year" << std::endl;
  std::cout << "addVinyl title vinyltype year artist minutes seconds" << std::endl;
  std::cout << "getBooks" << std::endl;
  std::cout << "getPs2Games" << std::endl;
  std::cout << "getVinyls" << std::endl;
  std::cout << "printMedia" << std::endl;
  std::cout << "##########################################################\n" << std::endl;

  while (userCommand != "q") {
    getline(std::cin, userCommand);
    std::stringstream ss(userCommand);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> commandList(begin, end);
    // createCommandList(userCommand, commandList);

    //Actions to perform
    if(commandList[0] == "addBook") {
      if(commandList.size() == 6) {
        Book tempBook(commandList);
        manager.addBook(tempBook);
    } else
        std::cout << "Wrong number of parameters :)" << std::endl;
    }

    if(commandList[0] == "addPs2Game") {
      if(commandList.size() == 4) {
        Ps2Game tempPs2Game(commandList);
        manager.addPs2Game(tempPs2Game);
    } else
        std::cout << "Wrong number of parameters :)" << std::endl;
    }

    if(commandList[0] == "addVinyl") {
      if(commandList.size() == 7) {
        Vinyl tempVinyl(commandList);
        manager.addVinyl(tempVinyl);
      } else
      std::cout << "Wrong number of parameters :)" << std::endl;
    }

    if(commandList[0] == "getBooks") {
      std::vector<Book> books = manager.getBooks();
      for (int i = 0; i < books.size(); i++) {
        std::cout << books[i].prettyPrint() << std::endl;
      }
    }

    if(commandList[0] == "getPs2Games") {
      std::vector<Ps2Game> ps2Games = manager.getPs2Games();
      for (int i = 0; i < ps2Games.size(); i++) {
        std::cout << ps2Games[i].prettyPrint() << std::endl;
      }
    }

    if(commandList[0] == "getVinyls") {
      std::vector<Vinyl> vinyls = manager.getVinyls();
      for (int i = 0; i < vinyls.size(); i++) {
        std::cout << vinyls[i].prettyPrint() << std::endl;
      }
    }

    if(commandList[0] == "printMedia")
      std::cout << manager.printMedia() << std::endl;

    commandList.clear();
  }
  std::cout << "Quiting the program" << std::endl;
}
