#pragma once

#include "SDL_error.h"
#include <chrono>
#include <filesystem>
#include <source_location>
#include <string>

constexpr int LOG_AT = -1;

enum class ll // calling it log_level was too annoying
{
  NOTE = 0,
  WARNING = 1,
  ERROR = 2,
  CRITICAL = 3,
};

// This struct is necessary to have a function accept variable arg count,
// while also providing the source information of the caller.
struct FormatWithLocation
{
  const char *value;
  std::source_location loc;

  FormatWithLocation(const char *s, const std::source_location &l =
                                        std::source_location::current())
      : value(s), loc(l)
  {
  }
};

extern std::chrono::time_point<std::chrono::system_clock> boot_time;
std::string get_time_since_boot();

// ====================== Our various logging methods ==========================

/*
The last argument must be a log level.

  log("Test: %d", val, ll::WARNING);
*/
template <typename... Args> void log(FormatWithLocation fmt, Args &&...args)
{
  // Retrieve last argument and check if it is a log level.
  // This will fail on compile if not properly provided by user.
  ll level = ll::WARNING;
  auto &&last = std::get<sizeof...(Args) - 1>(std::forward_as_tuple(args...));
  level = last;

  // Filter out logs we don't want
  if (static_cast<int>(level) < LOG_AT)
    return;

  // Print out log message
  std::filesystem::path path(fmt.loc.file_name());
  std::string current_time = get_time_since_boot();
  std::string path_str = path.filename().string();

  printf("[%s (%d) (%03d:%02d %s)] ", current_time.c_str(),
         static_cast<int>(level), fmt.loc.line(), fmt.loc.column(),
         path_str.c_str());
  printf(fmt.value, args...);
  printf("\n");
}

// Appends SDL_GetError output to log call
template <typename... Args> void log_sdl(FormatWithLocation fmt, Args &&...args)
{
  std::string t = std::string(fmt.value) + "\n\tSDL_ERROR: " + SDL_GetError();
  fmt.value = t.c_str();
  log(fmt, args...);
}

// ============================================================================
