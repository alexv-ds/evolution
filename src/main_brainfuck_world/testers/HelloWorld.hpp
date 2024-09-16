#pragma once

#include <memory>
#include <boost/noncopyable.hpp>
#include "../ITester.hpp"

namespace testers {

  class [[maybe_unused]] HelloWorld final : public ITester,
                                            public boost::noncopyable {
  public:
    explicit HelloWorld(std::string&& expected_output);

    [[nodiscard]] Result test(const GeneManager::Genes&) const override;

  protected:
    const std::string expected_output;

  };

} // testers

