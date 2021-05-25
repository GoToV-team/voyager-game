#pragma once

#include <cstdlib>
#include <filesystem>

#include <game_manager/interface.hpp>
#include <graphics/i_graphics_factory.h>
#include <graphics/i_spite_loader.h>
#include <loaders/properties_loader.hpp>
#include <loaders/progress_loader.hpp>
#include <loaders/level_loader.hpp>

namespace game_manager {

class ILoaderConfig;

class Config {
  public:
    Config(Config &other) = delete;

    void operator=(const Config &) = delete;

    static const Config &get_instance();

    static void load(const std::filesystem::path& root
                     , const ILoaderConfig &loader
                     , const IInitImportImplForConfig& initer);

    std::size_t player_id;
    std::size_t fps;
    std::filesystem::path levels_path;
    std::filesystem::path sprites_path;
    std::filesystem::path stats_path;
    std::filesystem::path properties_path;

    std::shared_ptr<game::CreatorLevel> level_manager;
    std::shared_ptr<graphics::IGraphicsFactory> graphics_factory;
    std::shared_ptr<graphics::ISpiteLoader> sprite_loader;
    std::shared_ptr<game::PlayerPropertiesLoader> properties_loader;
    std::shared_ptr<game::ProgressLoader> progress_loader;
    std::shared_ptr<game::CreatorLevel> levels_loader;

  protected:
    Config();

  private:
    static Config &_get_instance();
};

}  // namespace game_manager