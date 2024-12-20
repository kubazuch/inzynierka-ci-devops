#ifndef RESIN_HPP
#define RESIN_HPP

#include <chrono>
#include <cstdint>
#include <memory>
#include <resin/core/window.hpp>
#include <resin/event/event.hpp>
#include <resin/event/window_events.hpp>

int main();

namespace resin {

using namespace std::chrono_literals;
using duration_t = std::chrono::nanoseconds;

class Resin {
 public:
  Window& main_window() const { return *window_; }
  static Resin& instance() {
    static Resin instance;
    return instance;
  }

  Resin(const Resin&)            = delete;
  Resin(Resin&&)                 = delete;
  Resin& operator=(const Resin&) = delete;
  Resin& operator=(Resin&&)      = delete;

 private:
  Resin();
  ~Resin() = default;

  void run();
  void update(duration_t delta);
  void render();

  bool on_window_close(WindowCloseEvent& e);
  bool on_window_resize(WindowResizeEvent& e);

 public:
  static constexpr duration_t kTickTime = 16666us;  // 60 TPS = 16.6(6) ms/t

 private:
  std::unique_ptr<Window> window_;
  std::unique_ptr<EventDispatcher> dispatcher_;

  bool running_   = true;
  bool minimized_ = false;

  duration_t time_ = 0ns;
  uint16_t fps_ = 0, tps_ = 0;
  friend int ::main();
};

}  // namespace resin

#endif  // RESIN_HPP
