#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <dlfcn.h>
#include "Errors.hpp"

namespace Arcade {
class DirectoryScanner {
public:
  static bool hasSymbol(const std::string& libPath, const std::string& symbolName) {
    void* handle = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!handle) {
      return false;
    }
    
    void* sym = dlsym(handle, symbolName.c_str());
    if (!sym) {
      std::string macOSName = "_" + symbolName;
      sym = dlsym(handle, macOSName.c_str());
    }
    
    dlclose(handle);
    return sym != nullptr;
  }

  static void scan(const std::string& path, std::vector<std::string>& gameLibs, std::vector<std::string>& graphicLibs) {
    gameLibs.clear();
    graphicLibs.clear();

    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
      return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
      std::string extension = entry.path().extension().string();
      
      if (extension == ".so" || extension == ".dylib") {
        std::string filepath = entry.path().string();
        
        if (hasSymbol(filepath, "createGraphics")) {
          graphicLibs.push_back(filepath);
        } else if (hasSymbol(filepath, "createGame")) {
          gameLibs.push_back(filepath);
        }
      }
    }
  }
};
}
