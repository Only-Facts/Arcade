/*
** EPITECH PROJECT, 2026
** core
** File description:
** core
*/

#include <memory>
#include <iostream>
#include <dlfcn.h>
#include "Core.hpp"
#include "DLLoader.hpp"
#include "IGame.hpp"

namespace Arcade {
  /*
  Core::~Core(){
    unloadGraphics();
  }

  void Core::loadGraphics(const std::string& path){
    // open graphic lib
    _graphicHandle = dlopen(path.c_str(), RTLD_LAZY);
    if (!_graphicHandle)
      throw ARCError(dlerror());

    // load getType function of the lib 
    auto getType = reinterpret_cast<GetTypeFn>(dlsym(_graphicHandle, "getType"));
    const char *error = dlerror();
    if (error)
      throw ARCError(error);

    // load the create function of the lib
    auto create = reinterpret_cast<CreateFn>(dlsym(_graphicHandle, "create"));
    error = dlerror();
    if (error)
      throw ARCError(error);

    //load the destroy fun of the lib
    _destroyGraphics = reinterpret_cast<DestroyFn>(dlsym(_graphicHandle, "destroy"));
    error = dlerror();
    if (error)
      throw ARCError(error);

    // Error Handling for wrong lib
    if (getType() != PluginType::Graphics)
      throw ARCError("'" + path + "' is not a graphical library");

    // create _graphics object for core use
    _graphics = static_cast<IGraphics*>(create());
    if (!_graphics)
      throw ARCError("failed to create graphics instance");
  }

  void Core::unloadGraphics()
  {
    if (_graphics && _destroyGraphics) {
      _destroyGraphics(_graphics);
      _graphics = nullptr;
    }
    _destroyGraphics = nullptr;
    if (_graphicHandle) {
      dlclose(_graphicHandle);
      _graphicHandle = nullptr;
    }
  }
  */

  void Core::run() {
    DLLoader<IGraphics> graphLoader(_graphicalPath);
    std::unique_ptr<IGraphics> graphLib = graphLoader.getInstance("entryPoint");

    //temporary
    std::cout << "Graphics library loaded successfully\n";

    std::string game = "snake"; // todo
    DLLoader<IGame> gameLoader("./lib/Core" + game + ".so");

    // todo
  }
} 
