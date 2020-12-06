#ifndef PRINTERS_HPP
#define PRINTERS_HPP

#define FMT_HEADER_ONLY
#include <fmt/chrono.h>
#include <fmt/format.h>

#include <iostream>
#include <string>

#include "Time.hpp"
#include "magic.hpp"

class Book;
class Vinyl;
class Ps2Game;

template <typename T, typename std::enable_if<
                          std::is_same<T, Book>::value>::type* = nullptr>
std::ostream& operator<<(std::ostream& os, T const& t) {
  if constexpr (isDefined<Book>::value) {
    os << fmt::format("{} by {}\n\t{} ed. {} pages. isbn: {}", t.getTitle(),
                      t.getAuthor(), t.getEdition(), t.getPages(), t.getIsbn());
  }
  return os;
}

template <typename T, typename std::enable_if<
                          std::is_same<T, Time>::value>::type* = nullptr>
std::string print(T const& time) {
  return fmt::format("{:%M:%S}", time.getChronoTime());
}

class Time;
template <typename T, typename std::enable_if<
                          std::is_same<T, Time>::value>::type* = nullptr>
std::ostream& operator<<(std::ostream& os, T const& time) {
  if constexpr (isDefined<Time>::value) {
    os << fmt::format("{:%M:%S}", time.getChronoTime());
  }
  return os;
}

enum class VinylTypes;
template <typename T, typename std::enable_if<
                          std::is_same<T, VinylTypes>::value>::type* = nullptr>
std::string toString(T t) {
  return t == T::LONG_PLAY ? "LP" : "EP";
}

class Vinyl;
template <typename V, typename std::enable_if<
                          std::is_same<V, Vinyl>::value>::type* = nullptr>
std::ostream& operator<<(std::ostream& os, V const& vinyl) {
  if constexpr (isDefined<Vinyl>::value) {
    std::string type = toString(vinyl.getType());

    std::string str = fmt::format(
        "{} ({}, {}) by {}. Runtime: {}. Track listing:", vinyl.getTitle(),
        type, vinyl.getYear(), vinyl.getArtist(), print(vinyl.getRuntime()));
    int idx = 1;
    for (auto track : vinyl.getTracks()) {
      str += fmt::format("\n\t{} {}: {}", idx++, track.getName(),
                         print(track.getLength()));
    }
    os << str;
  }
  return os;
}

class Ps2Game;
template <typename G, typename std::enable_if<
                          std::is_same<G, Ps2Game>::value>::type* = nullptr>
std::ostream& operator<<(std::ostream& os, G const& game) {
  if constexpr (isDefined<Ps2Game>::value) {
    os << fmt::format("{} by {} ({})", game.getTitle(), game.getStudio(),
                      game.getYear());
  }
  return os;
}

#endif  // PRINTERS_HPP