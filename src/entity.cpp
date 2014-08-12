#include <SDL2/SDL.h>

#include "entity.hpp"

Entity::Entity(Spritesheet& n_spritesheet)
{
    spritesheet = &n_spritesheet;
    position_rect.x = 0;
    position_rect.y = 0;

    position.set(0.0, 0.0);

    rotation = 0;

    flip_type = SDL_FLIP_NONE;

    SDL_QueryTexture(spritesheet->get_texture(), NULL, NULL, &position_rect.w, &position_rect.h);

    center.x = position_rect.w/2;
    center.y = position_rect.h/2;

    alive = true;
    blending = SDL_BLENDMODE_BLEND;
    alpha = 255;
};

Entity::~Entity()
{
    /// prevent nullifying any existing textures
    /// aka 'unload' the gun / pointer.
    /// texture = NULL;
};

void Entity::draw(SDL_Renderer* game_renderer)
{
    /*/// For my debugging purposes.
    SDL_SetRenderDrawColor(game_renderer, 255, 64, 64, 128);
    SDL_RenderDrawRect(game_renderer, &position_rect);
    */
    SDL_BlendMode old_blend;
    uint8_t old_alpha;

    SDL_GetTextureBlendMode(spritesheet->get_texture(), &old_blend);
    SDL_GetTextureAlphaMod(spritesheet->get_texture(), &old_alpha);

    SDL_SetTextureAlphaMod(spritesheet->get_texture(), alpha);
    SDL_SetTextureBlendMode(spritesheet->get_texture(), blending);

    SDL_RenderCopyEx(game_renderer, spritesheet->get_texture(), spritesheet->get_clip_rect(), &position_rect, rotation, &center, flip_type);

    SDL_SetTextureBlendMode(spritesheet->get_texture(), old_blend);
    SDL_SetTextureAlphaMod(spritesheet->get_texture(), old_alpha);
};

void Entity::update()
{
    rotation += 0.1; /// DEBUG
    Vector2D movement(0.5, 0.3); /// DEBUG

    position = position + movement;
    move(position.get_x(), position.get_y());

    /// Use screen width info. DEBUG.
    if(position_rect.x >= 650)
        move(-10.0, position.get_y());
    if(position_rect.y >= 490)
        move(position.get_x(), -10.0);
};

void Entity::stretch(int new_width, int new_height)
{
    /************************************
    * Possibly re-center here?
    ************************************/
    position_rect.w = new_width;
    position_rect.h = new_height;
};

void Entity::scale(float scale)
{
    /************************************
    * Possibly re-center here, too?
    ************************************/
    position_rect.w = spritesheet->get_clip_rect()->w * scale;
    position_rect.h = spritesheet->get_clip_rect()->h * scale;
};

void Entity::move(float new_x, float new_y)
{
    position.set(new_x, new_y);
    position_rect.x = (int)position.get_x();
    position_rect.y = (int)position.get_y();
};

void Entity::rotate(float angle)
{
    rotation = angle;
};

Spritesheet* const Entity::get_spritesheet()
{
    return spritesheet;
}

bool Entity::is_alive()
{
    return alive;
};

void Entity::center_on_rect()
{
    center.x = position_rect.w/2;
    center.y = position_rect.w/2;
};

void Entity::set_center(int new_x, int new_y)
{
    center.x = new_x;
    center.y = new_y;
};

void Entity::set_blending(SDL_BlendMode new_blend)
{
    blending = new_blend;
};

void Entity::set_alpha(uint8_t new_alpha)
{
    alpha = new_alpha;
};

void Entity::flip_sprite(SDL_RendererFlip new_flip)
{
    flip_type = new_flip;
};

