#include "game.hpp"





Game::Game()
{
    map.Init();

}

void Game::UpdateAndDraw()
{
    map.Draw();



}




bool Timer(int &timer, int const second)
{

    timer++;
    if(timer==second*60){
        timer = 0;
        return true;
    }
    return false;

}