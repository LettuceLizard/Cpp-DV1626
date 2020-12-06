class Media;
#if __has_include("Media.hpp")
#include "Media.hpp"
#endif

class MediaManager;
#if __has_include("MediaManager.hpp")
#include "MediaManager.hpp"
#endif

class Book;
#if __has_include("Book.hpp")
#include "Book.hpp"
#endif

class Ps2Game;
#if __has_include("Ps2Game.hpp")
#include "Ps2Game.hpp"
#endif

class Vinyl;
class Track;
enum class VinylTypes;
#if __has_include("Vinyl.hpp")
#include "Vinyl.hpp"
#endif

#include <catch.hpp>

#include "functionCheckerGenerators.inc"
#include "printers.hpp"

using namespace std::chrono_literals;

GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(addMedia)
GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(addBook)
GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(addVinyl)
GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(addPs2Game)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(printMedia)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(getBooks)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(getVinyls)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(getPs2Games)

TEMPLATE_TEST_CASE_SIG("Testing the MediaManager class", "",
                       ((int Dummy, typename T_MediaManager, typename T_Media,
                         typename T_Book, typename T_Ps2Game, typename T_Vinyl,
                         typename T_VinylTypes, typename T_Track),
                        Dummy, T_MediaManager, T_Media, T_Book, T_Ps2Game,
                        T_Vinyl, T_VinylTypes, T_Track),
                       (42, MediaManager, Media, Book, Ps2Game, Vinyl,
                        VinylTypes, Track)) {
  static constexpr bool vinylDefined = isDefined<T_Vinyl>::value;
  static constexpr bool vinylTypeDefined = isDefined<T_VinylTypes>::value;
  static constexpr bool trackDefined = isDefined<T_Track>::value;
  static constexpr bool bookDefined = isDefined<T_Book>::value;
  static constexpr bool ps2gameDefined = isDefined<T_Ps2Game>::value;
  static constexpr bool mediaManagerDefined = isDefined<T_MediaManager>::value;
  if constexpr (!vinylDefined || !vinylTypeDefined || !trackDefined ||
                !bookDefined || !ps2gameDefined || !mediaManagerDefined) {
    FAIL(
        "Could not find definition of Vinyl, VinylType, Track, Book, Ps2Game "
        "and/or MediaManager. Skipping the rest of the tests. Rerun the tests "
        "once you have implemented the above classes and enum classes.");
  } else {
    static constexpr bool isConstructible =
        std::is_constructible<T_MediaManager>::value;
    static constexpr bool hasOpEquals =
        has_const_equalsOp<T_MediaManager, bool, const T_MediaManager&>::value;
    HAS_FN(addMedia, T_MediaManager, void, T_Media*);
    HAS_FN(addBook, T_MediaManager, void, const T_Book&);
    HAS_FN(addVinyl, T_MediaManager, void, const T_Vinyl&);
    HAS_FN(addPs2Game, T_MediaManager, void, const T_Ps2Game&);
    HAS_CONST_FN(printMedia, T_MediaManager, std::string);
    HAS_CONST_FN(getBooks, T_MediaManager, std::vector<T_Book>);
    HAS_CONST_FN(getVinyls, T_MediaManager, std::vector<T_Vinyl>);
    HAS_CONST_FN(getPs2Games, T_MediaManager, std::vector<T_Ps2Game>);
    static constexpr bool signaturesOk =
        hasOpEquals && var_has_addMedia && var_has_addBook &&
        var_has_addVinyl && var_has_addPs2Game && var_has_printMedia &&
        var_has_getBooks && var_has_getVinyls && var_has_getPs2Games;
    WHEN("Running signature tests on the MediaManager class") {
      WHEN("Checking for correct constructors and destructors") {
        CHECKVAR(isConstructible, "Checking MediaManager constructor");
      }
      WHEN("Checking for correct getters") {
        CHECKVAR2(addMedia);
        CHECKVAR2(addBook);
        CHECKVAR2(addVinyl);
        CHECKVAR2(addPs2Game);
        CHECKVAR2(printMedia);
        CHECKVAR2(getBooks);
        CHECKVAR2(getVinyls);
        CHECKVAR2(getPs2Games);
      }
      CHECKVAR(hasOpEquals, "operator==");
    }

    WHEN("Testing the Book class implementation") {
      if constexpr (!signaturesOk) {
        FAIL(
            "Skipping this section as the class does not conform to the "
            "spec. "
            "Make sure you have implented all methods with the correct "
            "signatures. The tests above should guide you and show you what "
            "is actually missing or wrong ");
      } else {
        T_MediaManager mediaManager;
        GIVEN("Three books has been added to the media manager") {
          T_Book hitchickersGuide("Liftarens guide till galaxen", "Douglas Adams",
                                "9789132212697", 42, 3);
          mediaManager.addBook(hitchickersGuide);
          T_Book yachtDesign("Principles of Yacht Design",
                           "Lars Larsson, Rolf Eliasson, Michal Orych",
                           "9781408187906", 352, 4);
          mediaManager.addBook(yachtDesign);
          T_Book revelationSpace("Revelation Space", "Alastair Reynolds",
                               "9780575083097", 576, 1);
          mediaManager.addBook(revelationSpace);

          WHEN("getBooks() is called") {
            std::vector<T_Book> books = mediaManager.getBooks();
            THEN(
                "There should be three books in the supplied vector after the "
                "function call") {
              REQUIRE(books.size() == 3);
            }
            THEN("The first book should be \"Liftarens guide till galaxen\"") {
              REQUIRE(books[0] == hitchickersGuide);
              REQUIRE(books[0].getTitle() == "Liftarens guide till galaxen");
              REQUIRE(books[0].getAuthor() == "Douglas Adams");
              REQUIRE(books[0].getIsbn() == "9789132212697");
              REQUIRE(books[0].getPages() == 42);
              REQUIRE(books[0].getEdition() == 3);
            }
            THEN("The second book should be \"Principles of Yacht Design\"") {
              REQUIRE(books[1] == yachtDesign);
            }
            THEN("The third book should be \"Revelation Space\"") {
              REQUIRE(books[2] == revelationSpace);
            }
          }
        }

        GIVEN("A Vikingarna LP has been added to the media library") {
          T_Vinyl kramgoaSeven("Kramgoa Låtar 7", T_VinylTypes::LONG_PLAY, 1979,
                               "Vikingarna", Time(46min));
          kramgoaSeven.addTrack(T_Track("Djinghis Khan", Time(3min + 3s)));
          kramgoaSeven.addTrack(T_Track("Hjärtats röst", Time(2min + 23s)));
          kramgoaSeven.addTrack(T_Track("Annie's Song", Time(3min + 14s)));
          kramgoaSeven.addTrack(
              T_Track("Om du lämnar mig så här", Time(3min + 14s)));
          kramgoaSeven.addTrack(
              T_Track("Så länge du älskar är du ung", Time(3min + 22s)));
          kramgoaSeven.addTrack(T_Track("Jag kommer hem", Time(2min + 27s)));
          kramgoaSeven.addTrack(T_Track("Jag var så kär", Time(2min + 55s)));
          kramgoaSeven.addTrack(T_Track("Such a Night", Time(2min + 57s)));
          mediaManager.addVinyl(kramgoaSeven);
          WHEN("The library is printed") {
            std::vector<T_Vinyl> vinyls = mediaManager.getVinyls();
            THEN(
                "There should be one vinyl in the supplied vector after the "
                "function call") {
              REQUIRE(vinyls.size() == 1);
            }
            THEN("The Vinyl should be \"Kramgoa Låtar 7\"") {
              REQUIRE(vinyls[0] == kramgoaSeven);
            }
          }
        }
        GIVEN("Games") {
          mediaManager.addPs2Game(
              T_Ps2Game("Battlefield Bad Company 2", "DICE", 2010));
          mediaManager.addPs2Game(T_Ps2Game("Battlefield 4", "DICE", 2013));
          WHEN("The library is printed") {
            std::vector<Ps2Game> games = mediaManager.getPs2Games();
            THEN(
                "There should be two games in the supplied vector after the "
                "function call") {
              REQUIRE(games.size() == 2);
            }
            THEN("The first game should be \"Battlefield Bad Company 2\"") {
              REQUIRE(games[0] ==
                      T_Ps2Game("Battlefield Bad Company 2", "DICE", 2010));
            }
            THEN("The first game should be \"Battlefield 4\"") {
              REQUIRE(games[1] == T_Ps2Game("Battlefield 4", "DICE", 2013));
            }
          }
        }
      }
    }
  }
}