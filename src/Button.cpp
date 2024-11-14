#include "Button.hpp"

Button::Button()
{
    
}

Button::~Button()
{
}

void Button::Events(const SDL_Event *ev)
{
    if(ev->type == SDL_MOUSEBUTTONDOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT &&
                ev->button.x >= rect->x &&
                ev->button.x <= (rect->x + rect->w) &&
                ev->button.y >= rect->y &&
                ev->button.y <= (rect->y + rect->h)) {
            pressed = true;
        }
    }
    if(ev->type == SDL_MOUSEMOTION)
    {
        if( (ev->motion.x >= rect->x &&
            ev->motion.x <= (rect->x + rect->w) &&
            ev->motion.y >= rect->y &&
            ev->motion.y <= (rect->y + rect->h))
            )
        {
            hovered = true;
            // std::cout << hovered;
        }
        else
        {
            hovered = false;
            // std::cout << hovered;
        }
    }
}

bool Button::Clicked()
{
    if(pressed) {
        pressed = false;
        return true;
    }
    return false;
}

