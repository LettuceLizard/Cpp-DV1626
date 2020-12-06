class Media;
#if __has_include("Media.hpp")
#include "Media.hpp"
#endif

#include "catch.hpp"
#include "functionCheckerGenerators.inc"
#include "printers.hpp"

TEMPLATE_TEST_CASE_SIG("Testing the Book class", "",    //
                       ((int Dummy, typename T_Media),  //
                        Dummy, T_Media),                //
                       (42, Media)) {
  if constexpr (!isDefined<T_Media>::value) {
    FAIL(
        "Could not find definition of Media. Skipping the rest of the tests. "
        "Rerun the tests once you have implemented the Media class.");
  } else {
    static constexpr bool isAbstract = std::is_abstract<T_Media>::value;
    static constexpr bool isPolymorphic = std::is_polymorphic<T_Media>::value;

    static constexpr bool hasOpEquals =
        has_const_equalsOp<T_Media, bool, const T_Media&>::value;
    HAS_CONST_FN(prettyPrint, T_Media, std::string);

    WHEN("Running signature tests on the Media class") {
      WHEN("Checking for polymorphism and correct base class") {
        CHECKVAR(isAbstract, "Media is abstract");
        CHECKVAR(isPolymorphic, "Polymorphism");
      }
      CHECKVAR(hasOpEquals, "operator==");
      CHECKVAR2(prettyPrint);
    }
  }
}