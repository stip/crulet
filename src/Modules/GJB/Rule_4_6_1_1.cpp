#include "Rule_4_6_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_4_6_1_1::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = stmt(anyOf(
    ifStmt(hasCondition(binaryOperator(hasOperatorName("=")).bind("gjb4611"))),
    ifStmt(hasCondition(expr(hasDescendant(binaryOperator(hasOperatorName("=")).bind("gjb4611"))))),
    forStmt(hasCondition(binaryOperator(hasOperatorName("=")).bind("gjb4611"))),
    forStmt(hasCondition(expr(hasDescendant(binaryOperator(hasOperatorName("=")).bind("gjb4611")))))
  ));
  Finder->addMatcher(Matcher, this);
}

void Rule_4_6_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("gjb4611")){
    DiagnosticsEngine &DE = Result.Context->getDiagnostics();
    std::string msg = "[" + CheckerName + "] " + "禁止在非赋值表达式中出现赋值操作符";
    unsigned DiagID = DE.getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Warning, msg);
    DE.Report(Op->getOperatorLoc(), DiagID);
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang