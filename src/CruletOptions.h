#ifndef LLVM_CLANG_TOOLS_EXTRA_CRULET_OPTIONS_H
#define LLVM_CLANG_TOOLS_EXTRA_CRULET_OPTIONS_H

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <map>
#include <vector>

namespace clang {
namespace crulet {

class CruletOptions {
public:
  CruletOptions() {}
  ~CruletOptions() {}

  void parseCheckOptions(std::string OptStr);
  bool isCheckerEnabled(std::string ModuleName, std::string CheckerName);

private:
  std::map<std::string, bool> EnabledCheckerMap;

};

} // namespace crulet
} // namespace clang

#endif