#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

#include "classes_obj.cpp"
#include "begin_his.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "My window");
    //window.setVerticalSyncEnabled(true);//синхронизация частоты кадров
    start_his(&window);

    background bc("image/back.png", "image/road2.png", "image/light.png", "image/rain.png", "image/lightning.png", "music/grom.wav", "music/rain.wav", "music/morgen.wav");
    man morgen("image/morgen.png", "image/morgen_sit.png");
    object obj;

    sf::Font font;
    font.loadFromFile("font/myf.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(100);
    char string_score[1024];


    int score = 0;
    int time_stop = 15;
    int if_dead = 0;

    while (window.isOpen())
    {
        if (if_dead)
        {
            score = 0;
            time_stop = 15;
            if_dead = 0;
            obj.reset_pos();
            continue;
        }

        window.clear(sf::Color::White);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                    morgen.jump_men();
                if (event.key.shift)
                {
                    morgen.sit_men(1);
                    break;
                }
            }
            else
                morgen.sit_men(0);

            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
        }

        // draw everything here...
        bc.draw_back(&window);
        morgen.draw_man(&window);
        obj.draw_obj(&window);
        bc.draw_fore(&window, score);

        itoa(score, string_score, 10);
        text.setString(string_score);
        text.setOrigin(-500 + (int)strlen(string_score) * 25, -50);
        window.draw(text);
        //stop draw...

        window.display();

        if (morgen.if_crash(obj.get_x(), obj.get_y(), obj.get_x_len(), obj.get_y_len()))
        {
            //wait_event(&window);
            if_dead = 1;
            bc.draw_back_end(&window);
            window.draw(text);
            window.display();
            sf::Clock clock;

            wait_event(&window);
            continue;
        }

        time_stop = (15 - score / 1500);
        if (time_stop < 1)
            time_stop = 1;

        sf::Clock clock;
        while (clock.getElapsedTime().asMilliseconds() < time_stop);
        //printf("score:%d\n", score);
        score++;
    }

    return 0;
}
