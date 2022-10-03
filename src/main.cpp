#include <iostream>
#include <array>

#include <cling/Interpreter/Interpreter.h>
#include <cling/Interpreter/Value.h>

#include "singleton.hpp"

int main(int const argc, char const **argv)
{
  std::array<char const*, 2> cling_args{ argv[0], "-std=c++17" };
  cling::Interpreter jit(cling_args.size(), cling_args.data(), LLVMDIR);

  jit.AddIncludePath("include");
  jit.process("#include \"singleton.hpp\"");

  std::cout << "before: " << singleton<int>().b << std::endl;
  std::cout << "cling: ";
  jit.process("singleton<int>().b");
  std::cout << "after: " << singleton<int>().b << std::endl;
}
