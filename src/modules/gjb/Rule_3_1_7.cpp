#include "Rule_3_1_7.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_3_1_7::registerMatchers(MatchFinder *Finder) {
  StatementMatcher Matcher = switchStmt().bind("gjb317_switch");
  Finder->addMatcher(Matcher, this);
}

void Rule_3_1_7::run(const MatchFinder::MatchResult &Result) {
  if(const SwitchStmt *SS = Result.Nodes.getNodeAs<SwitchStmt>("gjb317_switch")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = SS->getSwitchLoc();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    const Stmt* SSBody = SS->getBody();
    bool OK = true;
    auto PreStmtItr = SSBody->child_end();
    SourceLocation CaseLocation;
    
    for(auto it = SSBody->child_begin(); it != SSBody->child_end(); ++it){
      if(isa<CaseStmt>(*it)){

        if(PreStmtItr != SSBody->child_end() && !isa<BreakStmt>(*PreStmtItr)){
          OK = false;
          break;
        }

        CaseLocation = cast<CaseStmt>(*it)->getCaseLoc();
      }
      PreStmtItr = it;
    }

    if(!OK){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, CaseLocation, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, CaseLocation, this->DiagLevel);
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
