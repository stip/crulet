#ifndef CRULET_GJB_RULE_4_5_1_2_H
#define CRULET_GJB_RULE_4_5_1_2_H

#include "../../CruletChecker.h"

namespace clang {
namespace crulet {
namespace GJB {

class Rule_4_5_1_2 : public CruletChecker {
public:
  Rule_4_5_1_2(StringRef CheckerName)
    : CruletChecker(CheckerName) {}

  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  virtual void run(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace GJB
} // namespace crulet
} // namespace clang

#endif