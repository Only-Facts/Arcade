#include "IGame.hpp"

class PacmanModule : public Arcade::IGame {
public:
  PacmanModule() = default;
  ~PacmanModule() = default;
  void reset() override {
    return;
  };
  void update() override {
    return;
  };
  void onInput(Arcade::InputAction) override {
    return;
  };
  std::vector<Arcade::Cell> getDisplay() const override {
    return std::vector<Arcade::Cell>();
  };
  int getScore() const override {
    return 0;
  };
  std::string getName() const override {
    return std::string("Pacman");
  };
};

extern "C" Arcade::IGame* createGame() {
  return new PacmanModule();
}
