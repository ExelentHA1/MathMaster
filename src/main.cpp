#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <array>
#include <time.h>

#include "Window.hpp"
#include "Mouse.hpp"
#include "Timer.hpp"
#include "Clock.hpp"
#include "TextBox.hpp"

WindowRenderer *Window;

SDL_Texture *LoadTexture(SDL_Renderer *renderer, const char *path);

enum state
{
    menu = 0, game // change game state names
};

enum questionSet
{
    add = 0, sub, mul, dvd
};

const int WIDTH = 1280; // screen size
const int HEIGHT = 720;

int main(int argc, char *argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    uint32_t frameStart;
    int frameTime;
    Window = new WindowRenderer();
    Window->create("", WIDTH, HEIGHT);
    Timer gtime;

    TextBox question("res/ttf/Playtime.ttf", ((2*WIDTH)/4), (HEIGHT/4)+ -30, 0.3f, Window->renderer, false);

    
    TextBox btn_question1("res/ttf/Playtime.ttf", (WIDTH/4)+14, (HEIGHT/2)+60, 0.4f, Window->renderer, true);
    TextBox btn_question2("res/ttf/Playtime.ttf", (WIDTH/4)+14, (21*HEIGHT)/24, 0.4f, Window->renderer, true);
    TextBox btn_question3("res/ttf/Playtime.ttf", (3*WIDTH/4)-15, (HEIGHT/2)+60, 0.4f, Window->renderer, true);
    TextBox btn_question4("res/ttf/Playtime.ttf", (3*WIDTH/4)-15, (21*HEIGHT)/24, 0.4f, Window->renderer, true);

    TextBox tb_menu1("res/ttf/Playtime.ttf", ((2*WIDTH)/4), (2*HEIGHT/5)-12, 0.2f, Window->renderer, false);
    tb_menu1.SetRenderSpeed(0.5);
    TextBox tb_menu2("res/ttf/Playtime.ttf", ((2*WIDTH)/4), (HEIGHT/8), 0.2f, Window->renderer, false);
    tb_menu1.SetRenderSpeed(0.5);

    // init
    Mouse cursor(Window->renderer, "res/cursor2.png");
    Clock clock("res/ttf/carre.ttf",(WIDTH/2)-8, ((HEIGHT+HEIGHT)/3)+60, 0.4f, Window->renderer);
    // clock.SetTime(99);
    // question.SetText("MATH WIZARD");

    // btn_question1.SetText("ADD +");
    // btn_question2.SetText("SUB -");
    // btn_question3.SetText("MUL x");
    // btn_question4.SetText("DIV /");

    SDL_Texture *bg = LoadTexture(Window->renderer, "res/bgR.png");

    state gameState = menu;
    bool isAlreadyMenu = false; // flags to prevent one-time-call-functions from executing morethan once
    bool isAlreadyGame = false;
    bool GameOver;
    questionSet choosenSet;
    bool isGameQuestionStillUp = false; // this will tell if the current question is not yet solved
    int level, score, streak, mistakes, corrects, noQuest, corrAnsBtn;

    bool running = true;
    SDL_Event event;
    while(running)
    {
        frameStart = SDL_GetTicks();
        clock.Refresh();
        question.Refresh();
        tb_menu1.Refresh();
        tb_menu2.Refresh();

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
            // handles events
            btn_question1.Events(&event);
            btn_question2.Events(&event);
            btn_question3.Events(&event);
            btn_question4.Events(&event);
        }
        Window->clear(); // clear renderer
        // update objects
        cursor.update();

        switch (gameState)
        {
        case menu:
            if(!isAlreadyMenu) // initialize texts
            {
                question.SetText("MATH WIZARD");
                tb_menu1.SetText("Choose Problem Set.");
                tb_menu2.SetText("Welcome To,");
                btn_question1.SetText("ADD +");
                btn_question2.SetText("SUB -");
                btn_question3.SetText("MUL x");
                btn_question4.SetText("DIV /");
                clock.SetTime(0);
                isAlreadyMenu = true; // so these functions will not initialize again
            }
            // logic
            if(btn_question1.Clicked())
            {
                gameState = game;
                isAlreadyMenu = false;
                choosenSet = add;
            }
            if(btn_question2.Clicked())
            {
                gameState = game;
                isAlreadyMenu = false;
                choosenSet = sub;
            }
            if(btn_question3.Clicked())
            {
                gameState = game;
                isAlreadyMenu = false;
                choosenSet = mul;
            }
            if(btn_question4.Clicked())
            {
                gameState = game;
                isAlreadyMenu = false;
                choosenSet = dvd;
            }
            break;
        
        default:
            if(!isAlreadyGame) // initialize texts
            {
                level = 1;
                score = 0;
                noQuest = 0;
                corrects = 0;
                mistakes = 0;
                streak = 0;
                GameOver = false;
                isGameQuestionStillUp = false;

                srand(time(0));
                question.SetText("Question");
                tb_menu1.SetText("Correct/Mistake");
                tb_menu2.SetText("Score: 0");
                clock.SetTime(99);
                isAlreadyGame = true; // so these functions will not initialize again
            }
            // logic
            // generate a problem
            if(!isGameQuestionStillUp) // generate a new problem
            {
                int lval, rval, result;
                int min, max, tmp;
                std::string op;
                std::array<int, 4> ans = {0, 0, 0, 0};
                switch(choosenSet)
                {
                    case add:
                        op = " + ";
                        lval = 1 + (rand() % 10 + (score*level));
                        rval = 1 + (rand() % 10 + (score*level));
                        // std::cout << rval << " " << lval << std::endl; 
                        result = lval + rval;
                        if(result != 0) // in certain senario the program will generate a 0 result leading for wierd set of answer choices
                        {
                            if (result <= 4) // fewer choice of selection will result into never ending loop
                            {                   // the program will not generate multiple answer duplicates
                                min = result - 10;
                                max = result + 10;
                            }
                            else
                            {
                                min = result - (result * 0.5);
                                max = result + (result * 0.5);
                            }
                        }
                        else
                        {
                            min = result - 5;
                            max = result + 5;
                        }
                        min = result - (result * 0.5);
                        max = result + (result * 0.5);
                        for(int i = 0; i < (int)ans.size(); i++)
                        {
                            int n;
                            bool dup; // no duplicate choices
                            if(i == 0)
                            {
                                ans[i] = result;
                                continue;
                            }
                            else
                            {
                                do
                                {
                                    n = (rand() % (max-min)) + min;
                                    dup = false;
                                    for(int j =0; j < i; j++)
                                    {
                                        if(ans[j] == n)
                                        dup = true;
                                        break;
                                    }
                                } while (dup);
                                ans[i] = n;
                            }
                        }
                        break;
                    case sub:
                        op = " - ";
                        lval = 1 + (rand() % 10 + (score*level));
                        rval = 1 + (rand() % 10 + (score*level));
                        result = lval - rval;
                        if(result != 0) // in certain senario the program will generate a 0 result leading for wierd set of answer choices
                        {
                            if (result <= 4) // fewer choice of selection will result into never ending loop
                            {                   // the program will not generate multiple answer duplicates
                                min = result - 10;
                                max = result + 10;
                            }
                            else
                            {
                                min = result - (result * 0.5);
                                max = result + (result * 0.5);
                            }
                        }
                        else
                        {
                            min = result - 5;
                            max = result + 5;
                        }
                        for(int i = 0; i < (int)ans.size(); i++)
                        {
                            int n;
                            bool dup; // no duplicate choices
                            if(i == 0)
                            {
                                ans[i] = result;
                                continue;
                            }
                            else
                            {
                                do
                                {
                                    n = (rand() % (max-min)) + min;
                                    dup = false;
                                    for(int j =0; j < i; j++)
                                    {
                                        if(ans[j] == n)
                                        dup = true;
                                        break;
                                    }
                                } while (dup);
                                ans[i] = n;
                            }
                        }
                        break;
                    case mul:
                        op = " x ";
                        lval = 1 + (rand() % 10 + (score*level));
                        rval = 1 + (rand() % 10 + (score*level));
                        // std::cout << rval << " " << lval << std::endl; 
                        result = lval * rval;
                        if(result != 0) // in certain senario the program will generate a 0 result leading for wierd set of answer choices
                        {
                            if (result <= 4) // fewer choice of selection will result into never ending loop
                            {                   // the program will not generate multiple answer duplicates
                                min = result - 10;
                                max = result + 10;
                            }
                            else
                            {
                                min = result - (result * 0.5);
                                max = result + (result * 0.5);
                            }
                        }
                        else
                        {
                            min = result - 5;
                            max = result + 5;
                        }
                        min = result - (result * 0.5);
                        max = result + (result * 0.5);
                        for(int i = 0; i < (int)ans.size(); i++)
                        {
                            int n;
                            bool dup; // no duplicate choices
                            if(i == 0)
                            {
                                ans[i] = result;
                                continue;
                            }
                            else
                            {
                                do
                                {
                                    n = (rand() % (max-min)) + min;
                                    dup = false;
                                    for(int j =0; j < i; j++)
                                    {
                                        if(ans[j] == n)
                                        dup = true;
                                        break;
                                    }
                                } while (dup);
                                ans[i] = n;
                            }
                        }
                        break;
                    case dvd:
                        op = " / ";
                        lval = 1 + (rand() % 10 + (score*level));
                        rval = 1 + (rand() % 10 + (score*level));
                        // std::cout << rval << " " << lval << std::endl; 
                        result = lval * rval;
                        if(result != 0) // in certain senario the program will generate a 0 result leading for wierd set of answer choices
                        {
                            if (result <= 4) // fewer choice of selection will result into never ending loop
                            {                   // the program will not generate multiple answer duplicates
                                min = result - 10;
                                max = result + 10;
                            }
                            else
                            {
                                min = result - (result * 0.5);
                                max = result + (result * 0.5);
                            }
                        }
                        else
                        {
                            min = result - 5;
                            max = result + 5;
                        }
                        min = result - (result * 0.5);
                        max = result + (result * 0.5);
                        for(int i = 0; i < (int)ans.size(); i++)
                        {
                            int n;
                            bool dup; // no duplicate choices
                            if(i == 0)
                            {
                                ans[i] = lval;
                                continue;
                            }
                            else
                            {
                                do
                                {
                                    n = (rand() % (max-min)) + min;
                                    dup = false;
                                    for(int j =0; j < i; j++)
                                    {
                                        if(ans[j] == n)
                                        dup = true;
                                        break;
                                    }
                                } while (dup);
                                ans[i] = n;
                            }
                        }
                        tmp = lval;
                        lval = result;
                        result = tmp;
                        break;
                    default:
                        break;
                }
                std::random_shuffle(ans.begin(), ans.end());
                // update and set text screens, ie problem selection and problem text
                question.SetText(std::to_string(lval)+op+std::to_string(rval));
                btn_question1.SetText(std::to_string(ans[0]));
                btn_question2.SetText(std::to_string(ans[1]));
                btn_question3.SetText(std::to_string(ans[2]));
                btn_question4.SetText(std::to_string(ans[3]));
                // determinr correct answer button
                corrAnsBtn = 0;
                for(auto i : ans)
                {
                    if(i == result)
                        break;
                    corrAnsBtn++;
                }
                isGameQuestionStillUp = true;
            }
            else
            {
                // check the clock
                if(!clock.NoTime())
                {
                    if(btn_question1.Clicked())
                    {
                        if(0 == corrAnsBtn) // check if correct
                        {
                            corrects++;
                            switch (streak) // streak can increase points
                            {
                            case 1:
                                score +=0*level;
                                break;
                            case 2:
                                score +=2*level;
                                break;
                            case 3:
                                score +=3*level;
                                break;
                            default:
                                break;
                            }
                            if(streak < 3)
                                streak++;
                            if(noQuest>10)
                            {
                                noQuest = 0;
                                level++;
                            }
                            else 
                            {
                                noQuest++;
                            }
                            score +=1;
                            tb_menu1.SetText("LV: ("+ std::to_string(level) + ") "+std::to_string(corrects)+"/"+std::to_string(mistakes));
                            tb_menu2.SetText("Score: "+std::to_string(score));
                            isGameQuestionStillUp = false;
                        }
                        else // mistake
                        {
                            mistakes++;
                            streak = 0;
                            if(noQuest>10)
                            {
                                noQuest = 0;
                                level++;
                            }
                            else 
                            {
                                noQuest++;
                            }
                            if(!(score<1))
                                score--;
                            tb_menu1.SetText("LV: ("+ std::to_string(level) + ") "+std::to_string(corrects)+"/"+std::to_string(mistakes));
                            tb_menu2.SetText("Score: "+std::to_string(score));
                            isGameQuestionStillUp = false;
                        }
                    }
                    // -----------------------------------------------------------------
                    if(btn_question2.Clicked())
                    {
                        if(1 == corrAnsBtn) // check if correct
                        {
                            corrects++;
                            switch (streak) // streak can increase points
                            {
                            case 1:
                                score +=0*level;
                                break;
                            case 2:
                                score +=2*level;
                                break;
                            case 3:
                                score +=3*level;
                                break;
                            default:
                                break;
                            }
                            if(streak < 3)
                                streak++;
                            if(noQuest>10)
                            {
                                noQuest = 0;
                                level++;
                            }
                            else 
                            {
                                noQuest++;
                            }
                            score +=1;
                            tb_menu1.SetText("LV: ("+ std::to_string(level) + ") "+std::to_string(corrects)+"/"+std::to_string(mistakes));
                            tb_menu2.SetText("Score: "+std::to_string(score));
                            isGameQuestionStillUp = false;
                        }
                        else // mistake
                        {
                            mistakes++;
                            streak = 0;
                            if(noQuest>10)
                            {
                                noQuest = 0;
                                level++;
                            }
                            else 
                            {
                                noQuest++;
                            }
                            if(!(score<1))
                                score--;
                            tb_menu1.SetText("LV: ("+ std::to_string(level) + ") "+std::to_string(corrects)+"/"+std::to_string(mistakes));
                            tb_menu2.SetText("Score: "+std::to_string(score));
                            isGameQuestionStillUp = false;
                        }
                    }
                    // -----------------------------------------------------------------
                    if(btn_question3.Clicked())
                    {
                        if(2 == corrAnsBtn) // check if correct
                        {
                            corrects++;
                            switch (streak) // streak can increase points
                            {
                            case 1:
                                score +=0*level;
                                break;
                            case 2:
                                score +=2*level;
                                break;
                            case 3:
                                score +=3*level;
                                break;
                            default:
                                break;
                            }
                            if(streak < 3)
                                streak++;
                            if(noQuest>10)
                            {
                                noQuest = 0;
                                level++;
                            }
                            else 
                            {
                                noQuest++;
                            }
                            score +=1;
                            tb_menu1.SetText("LV: ("+ std::to_string(level) + ") "+std::to_string(corrects)+"/"+std::to_string(mistakes));
                            tb_menu2.SetText("Score: "+std::to_string(score));
                            isGameQuestionStillUp = false;
                        }
                        else // mistake
                        {
                            mistakes++;
                            streak = 0;
                            if(noQuest>10)
                            {
                                noQuest = 0;
                                level++;
                            }
                            else 
                            {
                                noQuest++;
                            }
                            if(!(score<1))
                                score--;
                            tb_menu1.SetText("LV: ("+ std::to_string(level) + ") "+std::to_string(corrects)+"/"+std::to_string(mistakes));
                            tb_menu2.SetText("Score: "+std::to_string(score));
                            isGameQuestionStillUp = false;
                        }
                    }
                    // -----------------------------------------------------------------
                    if(btn_question4.Clicked())
                    {
                        if(3 == corrAnsBtn) // check if correct
                        {
                            corrects++;
                            switch (streak) // streak can increase points
                            {
                            case 1:
                                score +=0*level;
                                break;
                            case 2:
                                score +=2*level;
                                break;
                            case 3:
                                score +=3*level;
                                break;
                            default:
                                break;
                            }
                            if(streak < 3)
                                streak++;
                            if(noQuest>10)
                            {
                                noQuest = 0;
                                level++;
                            }
                            else 
                            {
                                noQuest++;
                            }
                            score +=1;
                            tb_menu1.SetText("LV: ("+ std::to_string(level) + ") "+std::to_string(corrects)+"/"+std::to_string(mistakes));
                            tb_menu2.SetText("Score: "+std::to_string(score));
                            isGameQuestionStillUp = false;
                        }
                        else // mistake
                        {
                            mistakes++;
                            streak = 0;
                            if(noQuest>10)
                            {
                                noQuest = 0;
                                level++;
                            }
                            else 
                            {
                                noQuest++;
                            }
                            if(!(score<1))
                                score--;
                            tb_menu1.SetText("LV: ("+ std::to_string(level) + ") "+std::to_string(corrects)+"/"+std::to_string(mistakes));
                            tb_menu2.SetText("Score: "+std::to_string(score));
                            isGameQuestionStillUp = false;
                        }
                    }
                }
                else // game over
                {
                    // set all questions to blank
                    // show results
                    gtime.Update();
                    if(!GameOver)
                    {
                        question.SetText("Your Score: " + std::to_string(score));
                        tb_menu1.SetText("[X]"+std::to_string(mistakes) + "[O]"+std::to_string(corrects));
                        tb_menu2.SetText("GAME OVER");
                        btn_question1.SetText("");
                        btn_question2.SetText("");
                        btn_question3.SetText("");
                        btn_question4.SetText("");
                        GameOver = true;
                    }

                    if(gtime.GetDeltaTime() >= 10.f/1)
                    {
                        gameState = menu;
                        gtime.Reset();
                    }
                }
            }
            
            break;
        }


        clock.Update(Window->renderer);

        btn_question1.Update(Window->renderer);
        btn_question2.Update(Window->renderer);
        btn_question3.Update(Window->renderer);
        btn_question4.Update(Window->renderer);
        
        // Draw to screen

        // render static objects
        Window->render(bg, 0, 0, 0, 0, 1); // background

        btn_question1.RenderStatic(Window->renderer);
        btn_question2.RenderStatic(Window->renderer);
        btn_question3.RenderStatic(Window->renderer);
        btn_question4.RenderStatic(Window->renderer);

        tb_menu1.RenderDynamic(Window->renderer);
        tb_menu2.RenderDynamic(Window->renderer);
        // render unstatic objects
        question.RenderDynamic(Window->renderer);
        
        clock.Render(Window->renderer);
        cursor.Draw(Window->renderer);
        // if(play_btn.Clicked())
        //     printf("Clicked");
        Window->present(); // present screen
        //limit frames
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    Window->clean();

    delete Window;
    return 0;
}

SDL_Texture *LoadTexture(SDL_Renderer *renderer, const char *path)
{
    SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, path);
	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	return texture;
}