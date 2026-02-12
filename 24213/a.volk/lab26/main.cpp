#include <cstdio>
#include <exception>
#include <ext/stdio_filebuf.h>
#include <functional>
#include <ios>
#include <iostream>
#include <memory>
#include <ostream>
#include <stdexcept>

void run() {
  FILE *outpipe = popen("tr a-z A-Z", "w");
  if (!outpipe)
    throw std::runtime_error{"popen failed"};
  std::unique_ptr<FILE, std::function<int(FILE *)>> u{outpipe, pclose};

  __gnu_cxx::stdio_filebuf<char> outb{fileno(outpipe), std::ios::out};
  std::ostream outs{&outb};
  outs.exceptions(std::ostream::badbit);

  outs << std::cin.rdbuf();
}

int main() {
  std::cin.exceptions(std::istream::badbit);
  
  try {
    run();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
