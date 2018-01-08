#include "Rule_14_1_1.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_14_1_1::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = binaryOperator(hasOperatorName("==")).bind("equalComp");
  Finder->addMatcher(Matcher, this);
}

void Rule_14_1_1::run(const MatchFinder::MatchResult &Result) {
  if(const BinaryOperator *Op = Result.Nodes.getNodeAs<BinaryOperator>("equalComp")){
    Expr* LHS = Op->getLHS();
    Expr* RHS = Op->getRHS();
    if(LHS && RHS){
      const Type *LHSType = LHS->getType().getTypePtr();
      const Type *RHSType = RHS->getType().getTypePtr();
      if((LHSType && LHSType->isRealFloatingType()) || (RHSType && RHSType->isRealFloatingType())){
        DiagnosticsEngine &DE = Result.Context->getDiagnostics();
        Context->report(this->CheckerName, this->ReportMsg, DE, Op->getOperatorLoc(), DiagnosticIDs::Warning);
      }
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang