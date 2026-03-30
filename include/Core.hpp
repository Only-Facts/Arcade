/*
** EPITECH PROJECT, 2026
** CORE
** File description:
** arcade
*/

#ifndef CORE
  #define CORE
  #define SUCCESS 0
  #define HELP 2026
  #define ERROR 84
  #define FAIL 1
  #include "IGraphic.hpp"
  #include "PluginApi.hpp"

namespace Arcade {
class Core {
private:
  std::string _graphicalPath;
  void* _graphicHandle;
  IGraphics* _graphics;
  DestroyFn _destroyGraphics;

public:
  explicit Core(const std::string &initalGraphicPath) : _graphicalPath(initalGraphicPath),
    _graphicHandle(nullptr),
    _graphics(nullptr),
    _destroyGraphics(nullptr) {};
  ~Core() = default;
  void run();
};
}

#endif /* CORE */
