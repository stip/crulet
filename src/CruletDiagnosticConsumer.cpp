#include "CruletDiagnosticConsumer.h"
#include "clang/Tooling/Tooling.h"

namespace clang {
namespace crulet {

void CruletDiagnosticConsumer::HandleDiagnostic(DiagnosticsEngine::Level DiagLevel, const Diagnostic &Info){
  TextDiagnosticPrinter::HandleDiagnostic(DiagLevel, Info);
  // llvm::errs() << "---------------- Info.getID() = " << Info.getID() << " ---------------\n";

  if(Info.getID() == 3196u && Context->isCheckerEnabled("GJB-1.1.7")){    // GJB-1.1.7
    // DiagnosticsEngine &DE = Info.getSourceManager().getDiagnostics();
    // Context->report("GJB-1.1.7", "禁止过程参数只有类型没有标识符", DE, Info.getLocation(), DiagnosticIDs::Warning);
    llvm::errs() << "[GJB-1.1.7] 禁止过程参数只有类型没有标识符\n\n";
  }
  else if(Info.getID() == 1189u && Context->isCheckerEnabled("GJB-2.1.1")){    // GJB-2.1.1
    llvm::errs() << "[GJB-2.1.1] 过程体必须用大括号括起来\n\n";
  }
  else if(Info.getID() == 1963u && Context->isCheckerEnabled("GJB-6.1.10")){    // GJB-6.1.10
    llvm::errs() << "[GJB-6.1.10] 数组下标必须是整型数\n\n";
  }
  else if(Info.getID() == 795u && Context->isCheckerEnabled("GJB-1.1.18")){    // GJB-1.1.18
    llvm::errs() << "[GJB-1.1.18] 禁止在同一个文件中有#if而没有#endif\n\n";
  }
  else if(Info.getID() == 3503u && Context->isCheckerEnabled("GJB-7.1.1")){    // GJB-7.1.1
    llvm::errs() << "[GJB-7.1.1] 实参与形参的个数必须一致\n\n";
  }
  else if(Info.getID() == 3836u && Context->isCheckerEnabled("GJB-9.1.2")){    // GJB-9.1.2
    llvm::errs() << "[GJB-9.1.2] 禁止void类型的过程中的return语句带有返回值\n\n";
  }
  else if(Info.getID() == 3838u && Context->isCheckerEnabled("GJB-9.1.3")){    // GJB-9.1.3
    llvm::errs() << "[GJB-9.1.3] 有返回值的函数中return必须带有返回值\n\n";
  }
  else if(Info.getID() == 3530u && Context->isCheckerEnabled("GJB-7.1.7")){    // GJB-7.1.7
    llvm::errs() << "[GJB-7.1.7] 禁止void类型的过程用在表达式中使用\n\n";
  }
}

} // namespace crulet
} // namespace clang