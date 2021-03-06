#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <debug/exception.hpp>

#include "config_loader.hpp"

namespace game_manager::external {

void ConfigJsonLoader::load(const std::filesystem::path &root,
                            Config &config) const {
    if (root.empty()) {
        throw debug::ARG_ARGUMENT_ERROR("empty file for load in path :"
                                        + root.string());
    }

    namespace pt = boost::property_tree;

    boost::property_tree::ptree tree;
    boost::property_tree::read_json(root, tree);

    auto &text_config = tree.get_child("config");

    if (text_config.empty()) {
        throw debug::ARG_LOAD_ERROR((std::string)root);
    }

    auto &current_config = text_config;

    config.fps = current_config.get<size_t>("fps");
    config.player_id = current_config.get<size_t>("player_id");
    config.levels_path = root.parent_path()
                         / current_config.get<std::string>("levels_path");
    config.sprites_path = root.parent_path() /
                          current_config.get<std::string>("sprites_path");
    config.stats_path = root.parent_path()
                        / current_config.get<std::string>("stats_path");
    config.properties_path = root.parent_path() /
                             current_config.get<std::string>("properties_path");
}

}  // namespace game_manager::external
