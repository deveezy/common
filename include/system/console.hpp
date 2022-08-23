#pragma once

#include <ostream>

namespace common
{
//! Supported console colors
enum class Color {
  BLACK,        //!< Black color
  BLUE,         //!< Blue color
  GREEN,        //!< Green color
  CYAN,         //!< Cyan color
  RED,          //!< Red color
  MAGENTA,      //!< Magenta color
  BROWN,        //!< Brown color
  GREY,         //!< Grey color
  DARKGREY,     //!< Dark grey color
  LIGHTBLUE,    //!< Light blue color
  LIGHTGREEN,   //!< Light green color
  LIGHTCYAN,    //!< Light cyan color
  LIGHTRED,     //!< Light red color
  LIGHTMAGENTA, //!< Light magenta color
  YELLOW,       //!< Yellow color
  WHITE,         //!< White color
  COUNT
};

// Change console text color
template <class OutputStream>
OutputStream &operator<<(OutputStream &_stream, Color _color);

//! Stream manipulator: change console text and background colors
/*!
    \param stream - Output stream
    \param colors - Console text and background colors
    \return Output stream
*/
template <class OutputStream>
OutputStream &operator<<(OutputStream &_stream, std::pair<Color, Color> _colors);

/* Provides console management functionality such as setting
   text and background colors.

   THREAD-SAFE
*/
class Console
{
public:
  Console() = delete;
  Console(const Console &) = delete;
  Console &operator=(const Console &) = delete;
  Console(Console &&) = delete;
  Console &operator=(Console &&) = delete;
  ~Console() = delete;

  static void SetColor(Color _color, Color _background = Color::BLACK);
};

template <class OutputStream>
inline OutputStream &operator<<(OutputStream &_stream, Color _color) {
  Console::SetColor(_color);
  return _stream;
}

template <class OutputStream>
inline OutputStream &operator<<(OutputStream &_stream, std::pair<Color, Color> _colors) {
  Console::SetColor(_colors.first, _colors.second);
  return _stream;
}
} // namespace common
