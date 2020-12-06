class Media;
class Vinyl;
enum class VinylTypes;
class Track;
#if __has_include("Vinyl.hpp")
#include "Vinyl.hpp"
#endif

#include "Time.hpp"
#include "catch.hpp"
#include "functionCheckerGenerators.inc"
#include "printers.hpp"

using namespace std::chrono_literals;

TEMPLATE_TEST_CASE_SIG("Testing the Vinyl class", "",  //
                       ((int Dummy, typename T_Media, typename T_Vinyl,
                         typename T_VinylTypes,
                         typename T_Track),                               //
                        Dummy, T_Media, T_Vinyl, T_VinylTypes, T_Track),  //
                       (42, Media, Vinyl, VinylTypes, Track)) {
  static constexpr bool vinylDefined = isDefined<T_Vinyl>::value;
  static constexpr bool vinylTypeDefined = isDefined<T_VinylTypes>::value;
  static constexpr bool trackDefined = isDefined<T_Track>::value;

  if constexpr (!vinylDefined || !vinylTypeDefined || !trackDefined) {
    FAIL(
        "Could not find definition of Vinyl, VinylType and/or Track. Skipping "
        "the rest of the tests. Rerun the tests once you have implemented the "
        "above classes and enums.");
  } else {
    static constexpr bool vinylConstructible =
        std::is_constructible<T_Vinyl, const std::string&, T_VinylTypes, int,
                              const std::string&, const Time&>::value;
    static constexpr bool isBaseOfMedia =
        std::is_base_of<T_Media, T_Vinyl>::value;
    static constexpr bool isPolymorphic = std::is_polymorphic<T_Vinyl>::value;

    static constexpr bool trackConstructible =
        std::is_constructible<T_Track, std::string, Time>::value;

    static constexpr bool hasOpEquals =
        has_const_equalsOp<T_Vinyl, bool, const T_Vinyl&>::value;

    HAS_CONST_FN(getTitle, T_Vinyl, const std::string&);
    HAS_CONST_FN(getYear, T_Vinyl, int);
    HAS_CONST_FN(getArtist, T_Vinyl, const std::string&);
    HAS_CONST_FN(getType, T_Vinyl, T_VinylTypes);
    HAS_CONST_FN(getRuntime, T_Vinyl, const Time&);
    HAS_CONST_FN(getTracks, T_Vinyl, const std::vector<T_Track>&);
    HAS_FN(addTrack, T_Vinyl, void, const T_Track&);
    HAS_CONST_FN(prettyPrint, T_Vinyl, std::string);

    static constexpr bool signaturesOk =
        vinylConstructible && trackConstructible && hasOpEquals &&
        var_has_getTitle && var_has_getYear && var_has_getArtist &&
        var_has_getType && var_has_getRuntime && var_has_getTracks &&
        var_has_addTrack && var_has_prettyPrint && isBaseOfMedia &&
        isPolymorphic;
    WHEN("Running signature tests on the Vinyl class") {
      WHEN("Checking for polymorphism and correct base class") {
        CHECKVAR(isBaseOfMedia, "Baseclass should be Media");
        CHECKVAR(isPolymorphic, "Polymorphism");
      }
      WHEN("Checking for correct constructors and destructors") {
        CHECKVAR(vinylConstructible, "Checking Vinyl constructor");
        CHECKVAR(trackConstructible, "Checking Track constructor");
      }
      WHEN("Checking for correct getters") {
        CHECKVAR2(getTitle);
        CHECKVAR2(getYear);
        CHECKVAR2(getType);
        CHECKVAR2(getArtist);
        CHECKVAR2(getRuntime);
        CHECKVAR2(getTracks)
      }
      CHECKVAR(hasOpEquals, "operator==");
      CHECKVAR2(prettyPrint);
      CHECKVAR2(addTrack);
    }

    WHEN("Testing the Vinyl class implementation") {
      if constexpr (!signaturesOk) {
        FAIL(
            "Skipping this section as the class does not conform to the "
            "spec. "
            "Make sure you have implented all methods with the correct "
            "signatures. The tests above should guide you and show you what "
            "is actually missing or wrong ");
      } else {
        GIVEN("Probably the best \"Vikingarna\" LP") {
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

          THEN("Getters should return expected values") {
            REQUIRE(kramgoaSeven.getArtist() == "Vikingarna");
            REQUIRE(kramgoaSeven.getRuntime() == Time(46min));
            REQUIRE(kramgoaSeven.getTitle() == "Kramgoa Låtar 7");
            REQUIRE(kramgoaSeven.getType() == T_VinylTypes::LONG_PLAY);
            REQUIRE(kramgoaSeven.getYear() == 1979);
          }

          THEN("All tracks should have been added, and in the correct order") {
            REQUIRE(kramgoaSeven.getTracks().size() == 8);
            REQUIRE(kramgoaSeven.getTracks()[0].getName() == "Djinghis Khan");
            REQUIRE(kramgoaSeven.getTracks()[4].getName() ==
                    "Så länge du älskar är du ung");
          }

          WHEN("Creating a copy") {
            T_Vinyl kramgoaSevenCopy(kramgoaSeven);
            THEN("Getters should return expected values") {
              REQUIRE(kramgoaSevenCopy.getArtist() == "Vikingarna");
              REQUIRE(kramgoaSevenCopy.getRuntime() == Time(46min));
              REQUIRE(kramgoaSevenCopy.getTitle() == "Kramgoa Låtar 7");
              REQUIRE(kramgoaSevenCopy.getType() == T_VinylTypes::LONG_PLAY);
              REQUIRE(kramgoaSevenCopy.getYear() == 1979);
              REQUIRE(kramgoaSevenCopy.getTracks().size() == 8);
              REQUIRE(kramgoaSevenCopy.getTracks()[0].getName() ==
                      "Djinghis Khan");
              REQUIRE(kramgoaSevenCopy.getTracks()[4].getName() ==
                      "Så länge du älskar är du ung");
            }

            THEN("The == operator should work") {
              REQUIRE(kramgoaSevenCopy == kramgoaSeven);
              AND_THEN("And so should the != operator") {
                kramgoaSevenCopy.addTrack(T_Track("fejk", Time(43s)));
                REQUIRE(kramgoaSevenCopy != kramgoaSeven);
              }
            }
          }
        }
      }
    }
  }
}