#if !defined(INC_H___51A2AF25_67CA_4EC7_BDD4_110BF0B02226__HEAD__)
#define INC_H___51A2AF25_67CA_4EC7_BDD4_110BF0B02226__HEAD__
/**
 * @file stl.h
 *
 * @brief Only C++ STL functionality is encapsulated.
 *
 * @author Martell
 * @date 2023-11-13
 * @location SHE(ISO 3166-1)
 */

#define _PLATFORM_STL_VER __cplusplus

#ifdef _WINDOWS
#define _CRT_SECURE_NO_WARNINGS
#if _MSC_VER
#undef _PLATFORM_STL_VER
#define _PLATFORM_STL_VER _MSVC_LANG
#endif
#endif

#define _STL_HAS_CXX03 0
#define _STL_HAS_CXX11 0
#define _STL_HAS_CXX14 0
#define _STL_HAS_CXX17 0
#define _STL_HAS_CXX20 0
#define _STL_HAS_CXX23 0

#if _PLATFORM_STL_VER >= 199711L
#undef _STL_HAS_CXX03
#define _STL_HAS_CXX03 1
#endif

#if _PLATFORM_STL_VER >= 201103L
#undef _STL_HAS_CXX11
#define _STL_HAS_CXX11 1
#endif

#if _PLATFORM_STL_VER >= 201402L
#undef _STL_HAS_CXX14
#define _STL_HAS_CXX14 1
#endif

#if _PLATFORM_STL_VER >= 201703L
#undef _STL_HAS_CXX17
#define _STL_HAS_CXX17 1
#endif

#if _PLATFORM_STL_VER >= 202002L
#undef _STL_HAS_CXX20
#define _STL_HAS_CXX20 1
#endif

#if _PLATFORM_STL_VER > 202002L
#undef _STL_HAS_CXX23
#define _STL_HAS_CXX23 1
#endif


#if _STL_HAS_CXX03
#include <fcntl.h>

#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#endif

#if _STL_HAS_CXX11
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <random>
#include <regex>
#include <thread>
#include <tuple>
#include <typeinfo>
#endif

#if _STL_HAS_CXX14
#include <bitset>
#include <deque>
#include <any>
#include <filesystem>
#include <future>
#include <optional>
#include <string_view>
#include <variant>
#endif

#if _STL_HAS_CXX17

#endif

#if _STL_HAS_CXX20
#include <concepts>
#include <coroutine>
#include <format>
#endif

#if _STL_HAS_CXX23
#include <span> //(proposed for C++23, but may be available in some compilers)
#endif

namespace stl {

template <typename T = std::chrono::seconds>
#if _STL_HAS_CXX17
  requires std::is_convertible_v<T, std::chrono::milliseconds> ||
           std::is_convertible_v<T, std::chrono::minutes> ||
           std::is_convertible_v<T, std::chrono::microseconds>
#endif
static std::time_t TimeStamp() {
  return std::chrono::duration_cast<T>(
           std::chrono::time_point_cast<T>(std::chrono::system_clock::now())
             .time_since_epoch())
    .count();
}

template <typename T = std::string>
#if _STL_HAS_CXX17
  requires std::is_convertible_v<T, std::string> ||
           std::is_convertible_v<T, std::wstring>
#endif
static T Lower(const T &input) {
  T result{input};
  if (!result.empty()) {
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  }
  return result;
}

template <typename T = std::string>
#if _STL_HAS_CXX17
  requires std::is_convertible_v<T, std::string> ||
           std::is_convertible_v<T, std::wstring>
#endif
static T Upper(const T &input) {
  T result{input};
  if (!result.empty()) {
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  }
  return result;
}

static std::string
ReadFile(/*std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary*/
         const std::string &file_,
         const int &mode_ = std::ios::in | std::ios::binary) {
  std::string result;
  std::fstream of(file_, static_cast<std::ios_base::openmode>(mode_));
  do {
    if (!of.is_open())
      break;
    of.seekg(0, of.end);
    size_t size = static_cast<size_t>(of.tellg());
    if (size <= 0)
      break;
    result.resize(size, 0x00);
    of.seekg(0, of.beg);
    of.read(&result[0], size);
  } while (0);
  if (of.is_open())
    of.close();
  return result;
}

static void
ReadFile(/*std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary*/
         const std::string &file_, std::vector<char> &out_,
         const int &mode_ = std::ios::in | std::ios::binary) {
  out_.clear();
  std::fstream of(file_, static_cast<std::ios_base::openmode>(mode_));
  do {
    if (!of.is_open())
      break;
    of.seekg(0, of.end);
    size_t size = static_cast<size_t>(of.tellg());
    if (size <= 0)
      break;
    out_.resize(size, 0x00);
    of.seekg(0, of.beg);
    of.read(&out_[0], size);
  } while (0);
  if (of.is_open())
    of.close();
}

static bool WriteFile(const std::string &file_, const std::string &data_,
                      const int &mode_ = static_cast<int>(std::ios::binary) |
                                         static_cast<int>(std::ios::out) |
                                         static_cast<int>(std::ios::trunc)) {
  bool result = false;
  do {
    if (data_.empty())
      break;
#if 0
   if (!Win::AccessA(Win::GetPathByPathnameA(FilePathname)))
    Win::CreateDirectoryA(Win::GetPathByPathnameA(FilePathname));
#endif
    std::fstream of(file_, static_cast<std::ios_base::openmode>(mode_));
    if (!of.is_open())
      break;
    of << data_;
    of.close();
    result = true;
  } while (0);
  return result;
}

static bool WriteFileAddto(const std::string &file_, const std::string &data_) {
  bool result = false;
  do {
    if (data_.empty())
      break;
#if 0
   if (!Win::AccessA(FilePathname))
    Win::CreateDirectoryA(Win::GetPathByPathnameA(FilePathname));
#endif
    std::ofstream of(file_, std::ios::binary | std::ios::out | std::ios::app);
    if (!of.is_open())
      break;
    of << data_;
    of.close();
    result = true;
  } while (0);
  return result;
}

static std::string BinaryToHexString(const std::string &s) {
  std::ostringstream oss;
  for (unsigned char ch : s) {
#if WIN32
    oss << std::hex << std::setw(2) << std::setfill('0') << (int)ch;
#endif
  }
  return oss.str();
}

static std::string HexStringToBinary(const std::string &s) {
  std::string result;
  do {
    if ((s.length() % 2) != 0) {
      break;
    }
    result.reserve(s.length() / 2);
    std::string extract;
    for (std::string::const_iterator pos = s.begin(); pos < s.end(); pos += 2) {
      extract.assign(pos, pos + 2);
      result.push_back(std::stoi(extract, nullptr, 16));
    }
  } while (0);
  return result;
}

static std::vector<std::string> StringSpilt(const std::string &input,
                                            const std::string &delim) {
  std::vector<std::string> result;
  do {
    if (input.empty())
      break;
    if (delim.empty()) {
      result.emplace_back(input);
      break;
    }
    std::regex re(delim);
    result = std::vector<std::string>{
      std::sregex_token_iterator(input.begin(), input.end(), re, -1),
      std::sregex_token_iterator()};
  } while (0);
  return result;
}
static std::vector<std::wstring> WStringSplit(const std::wstring &input,
                                              const std::wstring &delim) {
  std::vector<std::wstring> result;
  do {
    if (input.empty())
      break;
    if (delim.empty()) {
      result.emplace_back(input);
      break;
    }
    std::wregex re(delim);
    result = std::vector<std::wstring>{
      std::wsregex_token_iterator(input.begin(), input.end(), re, -1),
      std::wsregex_token_iterator()};
  } while (0);
  return result;
}

#if 0
 //!@ input example : c:\\Windows\\System32\\
  //!
 template <typename T>
#if __cplusplus >= 201703L
  requires std::is_convertible_v<T, std::string> ||
           std::is_convertible_v<T, std::wstring>
#endif
 static bool CreateDirectories(const T &input_path)
 {
  bool result = false;
  T path_tmp = input_path;
  do
  {
   if (path_tmp.empty())
    break;
   do
   {
    if (path_tmp.empty())
     return false;
    if (*std::prev(path_tmp.end()) == '\\' ||
        *std::prev(path_tmp.end()) == '/')
    {
     path_tmp.pop_back();
     continue;
    }
    break;
   } while (1);
   result =
       std::filesystem::create_directories(std::filesystem::path(path_tmp));
  } while (0);
  return result;
 }

 template <typename T>
#if __cplusplus >= 201703L
  requires std::is_convertible_v<T, std::string> ||
           std::is_convertible_v<T, std::wstring>
#endif
 static bool PathOrFileExists(const T &input_path)
 {
  bool result = false;
  do
  {
   if (input_path.empty())
    break;
   std::filesystem::path path = input_path;
   if (!std::filesystem::exists(path))
    break;
   result = true;
  } while (0);
  return result;
 }
#endif

template <typename T>
#if __cplusplus >= 201703L
  requires std::is_convertible_v<T, std::string> ||
           std::is_convertible_v<T, std::wstring>
#endif
static bool PathVerify(const T &input_path) {
  bool result = false;
  do {
    if (input_path.empty())
      break;
    if (input_path.find('/') == T::npos && input_path.find('\\') == T::npos)
      break;
    result = true;
  } while (0);
  return result;
}
template <typename T>
#if __cplusplus >= 201703L
  requires std::is_convertible_v<T, std::string> ||
           std::is_convertible_v<T, std::wstring>
#endif
static T PathFix(const T &input_path, const T &path_spilt) {
  T result = input_path;
  do {
    if (!PathVerify(result) || path_spilt.empty())
      break;
    for (auto it = result.begin(); it != result.end();) {
      if (*it == '\\' || *it == '/') {
        *it = *path_spilt.begin();
      }
      if (it == result.begin()) {
        ++it;
        continue;
      }
      if (*std::prev(it) == *it && *it == *path_spilt.begin()) {
        it = result.erase(it);
        continue;
      }
      ++it;
    }
  } while (0);
  return result;
}

template <typename T>
#if __cplusplus >= 201703L
  requires std::is_convertible_v<T, std::string>
#endif
static T UrlFix(const T &inputUrlOrPath) {
  T result = inputUrlOrPath;
  if (result.empty())
    return result;
  for (auto it = result.begin(); it != result.end(); ++it) {
    if (*it == '\\')
      *it = '/';
  }
  do {
    auto found = result.find("//");
    if (found == T::npos)
      break;
    result.replace(found, T("//").size(), "/");
  } while (1);

  do {
    auto found = result.find(":/");
    if (found == T::npos)
      break;
    result.replace(found, T(":/").size(), "://");
  } while (0);
  return result;
}

template <typename T>
#if __cplusplus >= 201703L
  requires std::is_convertible_v<T, std::string> ||
           std::is_convertible_v<T, std::wstring>
#endif
static T PathnameToPath(const T &input_pathname) {
  T result = input_pathname;
  do {
    if (result.empty())
      break;
    if (!PathVerify(result))
      break;
    for (auto rit = result.rbegin(); rit != result.rend(); ++rit) {
      if (*rit != '\\' && *rit != '/') {
        result.resize(std::distance(result.begin(), rit.base()) - 1);
        continue;
      }
      break;
    }
  } while (0);
  return result;
}
} // namespace stl

#pragma comment(lib, "stl.lib")
/// /*新生®（上海）**/
/// /*2022_02_19T06:18:54.5642649Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif /// INC_H___51A2AF25_67CA_4EC7_BDD4_110BF0B02226__HEAD__
