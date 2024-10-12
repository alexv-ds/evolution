#pragma once
#include <boost/asio/io_context.hpp>
#include <flecs.h>
#include <memory>
namespace core::modules {

class IO {
public:
  explicit IO(const flecs::world &world);

  [[nodiscard]] const std::shared_ptr<boost::asio::io_context> &
  context() const noexcept;

private:
  std::shared_ptr<boost::asio::io_context> context_;
};

// ///////////////////////////// //
// /// INLINE IMPLEMENTATION /// //
// ///////////////////////////// //

inline const std::shared_ptr<boost::asio::io_context> &
IO::context() const noexcept {
  return context_;
}

} // namespace core::modules
