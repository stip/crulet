#include "Rule_1_1_16.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/Diagnostic.h"

using namespace clang::ast_matchers;

namespace clang {
namespace crulet {
namespace GJB {

void Rule_1_1_16::registerMatchers(MatchFinder *Finder) {
  DeclarationMatcher Matcher = namedDecl(anyOf(
                                          labelDecl(), 
                                          declaratorDecl(), 
                                          typedefDecl(), enumDecl(), recordDecl())
                                ).bind("gjb1116_namedDecl");
  Finder->addMatcher(Matcher, this);
}

void Rule_1_1_16::run(const MatchFinder::MatchResult &Result) {
  if(const NamedDecl *ND = Result.Nodes.getNodeAs<NamedDecl>("gjb1116_namedDecl")){
    SourceManager &SM = Result.Context->getSourceManager();
    SourceLocation SL = ND->getLocation();
    if(!SL.isValid() || SM.isInSystemHeader(SL)){
      return;
    }

    std::string Name = ND->getNameAsString();
    if(Name == ""){
      return;
    }

    if(const auto *FD = dyn_cast<FunctionDecl>(ND)){
      if(!FD->isThisDeclarationADefinition()) {
        return;
      }
    }

    if(VarNameMap.find(Name) != VarNameMap.end()){
      DiagnosticsEngine &DE = Result.Context->getDiagnostics();
      Context->report(this->CheckerName, this->ReportMsg, DE, SL, this->DiagLevel);
      Context->getJsonBugReporter().report(this->CheckerName, this->ReportMsg, SM, SL, VarNameMap[Name], this->DiagLevel);
    }else{
      VarNameMap[Name] = SL;
    }
  }
}

} // namespace GJB
} // namespace crulet
} // namespace clang
