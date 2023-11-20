#include <stl.hpp>
#pragma comment(lib, "libstl.a")
int main() {
  std::cout << stl::TimeStamp() << std::endl;
  std::cout << stl::TimeStamp<std::chrono::milliseconds>() << std::endl;
  std::cout << stl::TimeStamp<std::chrono::microseconds>() << std::endl;

  return 0;
}
