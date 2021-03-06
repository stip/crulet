#include "CruletOptions.h"

namespace clang {
namespace crulet {

void CruletOptions::parseCheckOptions(std::string OptStr){
  int start = 0;
  OptStr += ",";
  for(unsigned int i = 0; i < OptStr.size(); i++){
    if(OptStr[i] == ','){
      std::string item = OptStr.substr(start, i-start);
      start = i+1;

      if(item.empty()) continue;

      if(item[0] == '-'){
        item = item.substr(1);
        if(!item.empty()){
          EnabledCheckerMap[item] = false;
        }
      }else{
        EnabledCheckerMap[item] = true;
      }
    }
  }
}

bool CruletOptions::isCheckerEnabled(std::string CheckerName){
  std::string ModuleName = CheckerName.substr(0, CheckerName.find("-"));

  if(EnabledCheckerMap.find(CheckerName) != EnabledCheckerMap.end()){
    return EnabledCheckerMap[CheckerName];
  }else if(EnabledCheckerMap.find(ModuleName + "-*") != EnabledCheckerMap.end()){
    return EnabledCheckerMap[ModuleName + "-*"];
  }else if(EnabledCheckerMap.find("-" + ModuleName + "-*") != EnabledCheckerMap.end()){
    return false;
  }else if(EnabledCheckerMap.find("*") != EnabledCheckerMap.end()){
    return true;
  }else if(EnabledCheckerMap.find(CheckerName.substr(0, CheckerName.find('.')) + "*") != EnabledCheckerMap.end()){
    return true;
  }

  return false;
}

} // namespace crulet
} // namespace clang
