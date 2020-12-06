class Media;
class Ps2Game;
#if __has_include("Ps2Game.hpp")
#include "Ps2Game.hpp"
#endif

#include "catch.hpp"
#include "functionCheckerGenerators.inc"
#include "printers.hpp"

TEMPLATE_TEST_CASE_SIG("Testing the Ps2Game class", "",                     //
                       ((int Dummy, typename T_Media, typename T_Ps2Game),  //
                        Dummy, T_Media, T_Ps2Game),                         //
                       (42, Media, Ps2Game)) {
  if constexpr (!isDefined<T_Ps2Game>::value) {
    FAIL(
        "Could not find definition of Ps2Game. Skipping the rest of the tests. "
        "Rerun the tests once you have implemented the Ps2Game class.");
  } else {
    static constexpr bool isBaseOfMedia =
        std::is_base_of<T_Media, T_Ps2Game>::value;
    static constexpr bool isPolymorphic = std::is_polymorphic<T_Ps2Game>::value;
    static constexpr bool isConstructible =
        std::is_constructible<T_Ps2Game, const std::string&, const std::string&,
                              int>::value;

    static constexpr bool hasOpEquals =
        has_const_equalsOp<T_Ps2Game, bool, const T_Ps2Game&>::value;
    HAS_CONST_FN(getTitle, T_Ps2Game, const std::string&);
    HAS_CONST_FN(getStudio, T_Ps2Game, const std::string&);
    HAS_CONST_FN(getYear, T_Ps2Game, int);
    HAS_CONST_FN(prettyPrint, T_Ps2Game, std::string);

    static constexpr bool signaturesOk = hasOpEquals && var_has_getTitle &&
                                         var_has_getStudio && var_has_getYear &&
                                         var_has_prettyPrint && isBaseOfMedia &&
                                         isPolymorphic && isConstructible;
    WHEN("Running signature tests on the Ps2Game class") {
      WHEN("Checking for polymorphism and correct base class") {
        CHECKVAR(isBaseOfMedia, "Baseclass should be Media");
        CHECKVAR(isPolymorphic, "Polymorphism");
      }
      WHEN("Checking for correct constructors and destructors") {
        CHECKVAR(isConstructible, "Checking Ps2Game constructor");
      }
      WHEN("Checking for correct getters") {
        CHECKVAR2(getTitle);
        CHECKVAR2(getStudio);
        CHECKVAR2(getYear);
      }
      CHECKVAR(hasOpEquals, "operator==");
      CHECKVAR2(prettyPrint);
    }

    WHEN("Testing the Ps2Game class implementation") {
      if constexpr (!signaturesOk) {
        FAIL(
            "Skipping this section as the class does not conform to the "
            "spec. "
            "Make sure you have implented all methods with the correct "
            "signatures. The tests above should guide you and show you what "
            "is actually missing or wrong ");
      } else {
        GIVEN("Two games") {
          T_Ps2Game bfbc2(T_Ps2Game("Battlefield Bad Company 2", "DICE", 2010));
          T_Ps2Game tmp(bfbc2);
          THEN("Getters should return expected values") {
            REQUIRE(tmp.getTitle() == "Battlefield Bad Company 2");
            REQUIRE(tmp.getStudio() == "DICE");
            REQUIRE(tmp.getYear() == 2010);
          }
          THEN("The copy constructor should produce a identical copy") {
            REQUIRE(tmp.getTitle() == bfbc2.getTitle());
            REQUIRE(tmp.getStudio() == bfbc2.getStudio());
            REQUIRE(tmp.getYear() == bfbc2.getYear());
          }
          THEN("The == operator should work") {
            REQUIRE(tmp == bfbc2);
            AND_THEN("And so should the != operator") {
              T_Ps2Game bf4(T_Ps2Game("Battlefield 4", "DICE", 2013));
              REQUIRE(bf4 != bfbc2);
            }
          }
        }
      }
    }
  }
}