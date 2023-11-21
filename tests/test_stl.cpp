#include <stl.hpp>
int main(int argc, char **argv) {
  std::cout << stl::TimeStamp() << std::endl;
  std::cout << stl::TimeStamp<std::chrono::milliseconds>() << std::endl;
  std::cout << stl::TimeStamp<std::chrono::microseconds>() << std::endl;

  auto executablePath =
    std::filesystem::current_path() / std::filesystem::path(argv[0]);
  std::cout << "Executable Path: " << executablePath << std::endl;

  return 0;
}
