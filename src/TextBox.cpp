#include "TextBox.hpp"

TextBox::TextBox(const char *path,int posx, int posy, float pscale, SDL_Renderer *r, bool interactive)
{
    rect = &text.rect;
    text.Init(path, posx, posy, pscale, r);
    text.SetColor(&color);
    isButton = interactive;
    isEnable = true;
    seconds = 1;
    LoadSound("res/sfx/button.ogg");
}

TextBox::~TextBox()
{
    
}

void TextBox::LoadSound(const char *path)
{
    s.Init(path);
}

void TextBox::Refresh()
{
    if(!isButton)
    {
        timer->Update();
    }
}

void TextBox::SetRenderSpeed(float sec)
{
    seconds = sec;
}

void TextBox::RenderDynamic(SDL_Renderer *renderer)
{
    if(!isButton)
    {    
        if(timer->GetDeltaTime() >= seconds/(int)orgT.length())
        {
            if(!(t == orgT) && index == (int)t.length())
            {
                // append each char 1 by 1
                t += orgT[index];
                index++;
                text.Update((char*)t.c_str(), renderer, false);
            }
            timer->Reset();
        }
        SDL_RenderCopy(renderer, text.GetTexture(), nullptr, &text.rect);
    }
}

void TextBox::Update(SDL_Renderer *r)
{
    if(isEnable)
    {
        if(Clicked())
        {
            if(Mix_PlayingMusic())
            {
                s.Stop();
                s.Play();
            }
            else
            {
                s.Play();
            }
        }
        if(hovered)
        {
            SDL_Color tcolor {0xf5,0xf9,0xad};
            text.SetColor(&tcolor);
            if(orgT == "")
                orgT = " ";
            text.Update((char*)orgT.c_str(), r, true);
        }
        else
        {
            text.SetColor(&color);
            if(orgT == "")
                orgT = " ";
            text.Update((char*)orgT.c_str(), r, true);
        }
    }
    else
    {
        if(orgT == "")
            orgT = " ";
        text.Update((char*)orgT.c_str(), r, true);
    }
}

void TextBox::RenderStatic(SDL_Renderer *renderer)
{
    if(isButton)
    { 
        SDL_RenderCopy(renderer, text.GetTexture(), nullptr, &text.rect);
    }
        
}

void TextBox::SetText(std::string ptext)
{
    if(!isButton)
    {
        t = "";
        index = (int)t.length();
        orgT = ptext;
    }
    else
    {
        orgT = ptext;
    }
}

void TextBox::Enable(bool set)
{
    isEnable = set;
}
