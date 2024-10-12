#pragma once
#include <boost/noncopyable.hpp>
#include <flecs.h>
#include <map>
#include <memory>
#include <thread>

namespace core {

class Core : boost::noncopyable, public std::enable_shared_from_this<Core> {
public:
  using core_ptr = std::weak_ptr<Core>;

  static std::shared_ptr<Core> create();

  [[nodiscard]] const std::shared_ptr<flecs::world> &world() const;

  void run();

private:
  std::shared_ptr<flecs::world> world_;
  bool is_running = false;

  Core();

  void initialize();
};

// /////////////////////////////// //
// //// INLINE IMPLEMENTATION //// //
// /////////////////////////////// //

inline const std::shared_ptr<flecs::world> &Core::world() const {
  return world_;
}

} // namespace core
