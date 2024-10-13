#include "visualization.hpp"
#include "io.hpp"
#include "visualization/impl/components.hpp"
#include <SFML/Graphics.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <cmath>
#include <spdlog/spdlog.h>

namespace core::modules::visualization {

static void OnAddWindowCreate(const flecs::entity &e, const WindowCreate &) {
  e.world().add<impl::SfmlWindowInit>();
}

static void OnRemoveWindow(const flecs::entity &e, const Window &) {
  e.world().remove<impl::SfmlWindow>();
  e.world().remove<impl::SfmlWindowInit>();
  e.world().remove<WindowCreate>();
}

static void InitWindow(flecs::iter &it) {
  while (it.next()) {
    const flecs::world world = it.world();
    // auto init = it.field<impl::SfmlWindowInit>(0);
    auto window_create = it.field<const WindowCreate>(1);

    impl::SfmlWindow sfml_window;

    constexpr sf::Vector2u minimum_size(500, 500);
    const sf::Vector2u size = [minimum_size]() {
      const sf::Vector2u desktop_size = sf::VideoMode::getDesktopMode().size;
      constexpr float size_factor = 0.7;
      const auto estimated_size =
          sf::Vector2u(static_cast<unsigned int>(
                           static_cast<float>(desktop_size.x) * size_factor),
                       static_cast<unsigned int>(
                           static_cast<float>(desktop_size.y) * size_factor));

      const sf::Vector2u real_size(std::max(estimated_size.x, minimum_size.x),
                                   std::max(estimated_size.y, minimum_size.y));
      return real_size;
    }();

    sfml_window.window.create(sf::VideoMode(size), window_create->title);

    if (!window_create->icon.empty()) {
      if (boost::filesystem::exists(window_create->icon)) {
        sf::Image icon;
        if (icon.loadFromFile(window_create->icon)) {
          sfml_window.window.setIcon(icon);
        } else {
          SPDLOG_ERROR("Icon could not be loaded");
        }
      } else {
        SPDLOG_ERROR("Cannot set window icon: file not exists - {}",
                     window_create->icon);
      }
    }

    sfml_window.window.setMinimumSize(minimum_size);

    world.set(std::move(sfml_window));
    world.add<Window>();
    world.remove<impl::SfmlWindowInit>();
    world.remove<WindowCreate>();
  }
}

static void PollWindowEvents(flecs::iter &it) {
  while (it.next()) {
    const flecs::world world = it.world();

    const auto sfml_window = it.field<impl::SfmlWindow>(0);

    while (const auto event = sfml_window->window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        sfml_window->window.close();
        world.remove<Window>();
      }
    }
  }
}

static void WindowClear(flecs::iter &it) {
  while (it.next()) {
    const auto sfml_window = it.field<impl::SfmlWindow>(0);
    sfml_window->window.clear(sf::Color(35, 36, 35));
  }
}
static void WindowDisplay(flecs::iter &it) {
  while (it.next()) {
    const auto sfml_window = it.field<impl::SfmlWindow>(0);
    sfml_window->window.display();
  }
}

static void ExitIfWindowClosed(flecs::iter &it) {
  while (it.next()) {
    it.world().quit();
    SPDLOG_INFO("Window closed - shutdown world");
  }
}

// static void

// ///////////////////////////
// ///////////////////////////
// ///////////////////////////

static void init_components(const flecs::world &world) {
  world.component<impl::SfmlWindowInit>("impl::SfmlWindowInit");
  world.component<impl::SfmlWindow>("impl::SfmlWindow");
  world.component<Window>("Window");
  world.component<WindowCreate>("WindowCreate");
  world.component<ExitOnWindowClose>("ExitOnWindowClose");
}

static void init_observers(const flecs::world &world) {
  const auto _ = world.scope("impl::observers");

  world.observer<const WindowCreate>("OnAddWindowCreate")
      .term_at(0)
      .singleton()
      .event(flecs::OnAdd)
      .each(OnAddWindowCreate);

  world.observer<const Window>("OnRemoveWindow")
      .term_at(0)
      .singleton()
      .event(flecs::OnRemove)
      .each(OnRemoveWindow);
}

static void init_systems(const flecs::world &world) {
  const auto _ = world.scope("impl::systems");

  world.system<impl::SfmlWindowInit, const WindowCreate>("SfmlWindowInit")
      .kind(flecs::PreFrame)
      .term_at(0)
      .singleton()
      .term_at(1)
      .singleton()
      .run(InitWindow);

  world.system<impl::SfmlWindow>("PollWindowEvents")
      .kind(flecs::OnLoad)
      .term_at(0)
      .read_write()
      .singleton()
      .run(PollWindowEvents);

  world.system<impl::SfmlWindow>("WindowClear")
      .kind(flecs::PreStore)
      .term_at(0)
      .read_write()
      .singleton()
      .run(WindowClear);

  world.system<impl::SfmlWindow>("WindowDisplay")
      .kind(flecs::PostFrame)
      .term_at(0)
      .read_write()
      .singleton()
      .run(WindowDisplay);

  world.system<ExitOnWindowClose>("ExitOnWindowClose")
      .kind(flecs::PostFrame)
      .term_at(0)
      .read_write()
      .singleton()
      .without<Window>()
      .singleton()
      .run(ExitIfWindowClosed);
}

} // namespace core::modules::visualization

core::modules::Visualization::Visualization(flecs::world &world) {
  using namespace visualization;

  world.import <IO>();
  world.module<Visualization>("::core::visualisation");

  // const IO *io = world.get<IO>();
  // if (!io) {
  //   throw std::runtime_error("Cannot get IO module");
  // }
  // std::string str = boost::dll::program_location().parent_path().string();
  // sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
  // auto keks = 123;
  // boost::dll

  init_components(world);
  init_observers(world);
  init_systems(world);
}
