// Владимир Ларин
// Created by volodya on 06.05.2021.
//
#include <SFML/Graphics/Texture.hpp>
#include <graphics/background_sprite.h>
#include <sf_orbit_shape.h>

#include "sf_graphics/sf_graphics_factory.h"
#include "sf_graphics/sf_rect.h"
#include "sf_graphics/sf_sprite.h"
#include "sf_graphics/sf_texture.h"
#include "sf_graphics/sf_font.h"
#include "sf_graphics/sf_text.h"
#include "graphics/texture_storage.h"

namespace graphics::sf {

    std::unique_ptr<ITexture> SfGraphicsFactory::create_texture(const std::string &filename) {
        ::sf::Texture sf_texture;
        if (!sf_texture.loadFromFile(filename))
            throw std::exception();

        auto texture = std::unique_ptr<ITexture>(new SfTexture(std::move(sf_texture)));

        return texture;
    }

    std::unique_ptr<Sprite> SfGraphicsFactory::create_sprite(const SpriteInfo &info, TextureStorage &storage) {
        auto texture = dynamic_cast<SfTexture *> (storage.get(info.filename));
        if (info.frames == 0) {
            auto sprite = std::unique_ptr<Sprite>(new sf::SfSprite(info.pos, info.size, texture));
            if (info.is_bg){
                return std::make_unique<BackgroundSprite>(std::move(sprite));
            }
            return sprite;
        }
        return std::unique_ptr<Sprite>(new sf::SfHorizontalAnimatedSprite(info.frames, info.pos, info.size, texture));
    }

    std::shared_ptr<Font> SfGraphicsFactory::create_font() {
        return std::make_shared<sf::SfFont>();
    }

    std::unique_ptr<Text> SfGraphicsFactory::create_text() {
        return std::make_unique<sf::SfText>();
    }

    std::unique_ptr<Rect> SfGraphicsFactory::create_rect() {
        return std::make_unique<SfRect>();
    }

    Button SfGraphicsFactory::create_button() {
        return Button(create_rect().release(), create_text().release());
    }

    std::unique_ptr<OrbitShape> SfGraphicsFactory::create_orbit() {
        return std::make_unique<SfOrbitShape>();
    }
}