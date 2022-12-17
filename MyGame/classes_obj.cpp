#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

class background
{
    private:
        sf::Texture texture_back;
        sf::Sprite sprite_back;

        sf::Texture texture_road;
        sf::Sprite sprite_road;

        sf::Texture texture_light;
        sf::Sprite sprite_light;

        sf::Texture texture_rain;
        sf::Sprite sprite_rain;

        sf::Texture texture_lightning;
        sf::Sprite sprite_lightning;

        sf::SoundBuffer b_grom;
        sf::Sound grom;

        sf::SoundBuffer b_rain;
        sf::Sound rain;

        sf::Music music;
    public:
        background(char* back_path, char* road_path, char* light_path, char* rain_path, char* lightning_path, char* grom_s, char* rain_s, char* music_p)
        {
            texture_back.loadFromFile(back_path);
            sprite_back.setTexture(texture_back);

            texture_road.loadFromFile(road_path);
            sprite_road.setTexture(texture_road);

            texture_light.loadFromFile(light_path);
            sprite_light.setTexture(texture_light);

            texture_rain.loadFromFile(rain_path);
            sprite_rain.setTexture(texture_rain);

            texture_lightning.loadFromFile(lightning_path);
            sprite_lightning.setTexture(texture_lightning);

            b_grom.loadFromFile(grom_s);
            grom.setBuffer(b_grom);

            b_rain.loadFromFile(rain_s);
            rain.setBuffer(b_rain);

            music.openFromFile(music_p);
            music.setLoop(true);
            music.play();
        }

        void draw_back(sf::RenderWindow* window)
        {
            window->draw(sprite_back);

            sprite_road.setOrigin(0, -125);
            window->draw(sprite_road);
        }

        void draw_fore(sf::RenderWindow* window, int score)
        {
            sprite_light.setOrigin(0, -125);
            window->draw(sprite_light);
            if (score >= 2000)
            {
                if (score % 50 == 0)
                    rain.play();
                sprite_rain.setOrigin(100 - rand() % 400, 0);
                window->draw(sprite_rain);
            }
            if (score >= 3000 && score % 500 < 120)
            {
                if (score % 500 == 0)
                    grom.play();
                sprite_lightning.setColor(sf::Color(255, 255, 255, 255 - 2 * score % 500));
                window->draw(sprite_lightning);
            }
        }

        void draw_back_end(sf::RenderWindow* window)
        {
            rain.pause();
            window->draw(sprite_back);
        }
};

class man
{
    private:
        sf::Texture texture_men;
        sf::Sprite sprite_men;
        sf::Texture texture_men_sit;
        sf::Sprite sprite_men_sit;

        bool alive = 1;//1 пока жив

        const int x_len = 100;
        int y_len = 100;

        const int x = -100;
        int y = -390;

        bool is_sit = 0;//1 если сидит
        bool go_up = 0;//1 есил мужик летит вверх
        bool go_down = 0;//1 если мужик падает
        const int max_y = -90;//максимальная высота прыжка
        const int min_y = -390;//высота до которой падает
    public:
        man(char* man_path, char* man_sit_path)
        {
            texture_men.loadFromFile(man_path);
            sprite_men.setTexture(texture_men);

            texture_men_sit.loadFromFile(man_sit_path);
            sprite_men_sit.setTexture(texture_men_sit);
        }

        void draw_man(sf::RenderWindow* window)
        {
            if (is_sit)
            {
                sprite_men_sit.setOrigin(x, y);
                window->draw(sprite_men_sit);
                return;
            }

            if (y == max_y)//если достиг максимальной высоты начинает падать
            {
                go_up = 0;
                go_down = 1;
            }
            if (y == min_y)//достиг дороги - перестаёт падать
                go_down = 0;

            if (go_up)//если летит вверх увеличиваем y
                y += 10;
            if (go_down)//если падает уменьшаем y;
                y -= 5;

            sprite_men.setOrigin(x, y);
            window->draw(sprite_men);
        }

        void jump_men()
        {
            if (!go_up && !go_down && !is_sit)
                go_up = 1;
        }

        void sit_men(bool a)
        {
            if (!go_up && !go_down)
            {
                is_sit = a;
                if (is_sit)
                {
                    y = -440;
                    y_len = 50;
                }
                else
                {
                    y = -390;
                    y_len = 100;
                }
            }
        }

        bool if_alive()
        {
                return alive;
        }

        bool if_crash(const int x_obj, const int y_obj, const int x_len_obj, const int y_len_obj)
        {
            if (x < x_obj && x > x_obj - x_len_obj && y < y_obj && y > y_obj - y_len_obj)
            {
                alive = 0;
                return 1;
            }
            if (x - x_len < x_obj && x - x_len > x_obj - x_len_obj && y  < y_obj && y > y_obj - y_len_obj)
            {
                alive = 0;
                return 1;
            }
            if (x < x_obj && x > x_obj - x_len_obj && y - y_len < y_obj && y - y_len > y_obj - y_len_obj)
            {
                alive = 0;
                return 1;
            }
            if (x - x_len < x_obj && x - x_len > x_obj - x_len_obj && y - y_len < y_obj && y - y_len > y_obj - y_len_obj)
            {
                alive = 0;
                return 1;
            }

            return 0;
        }
};

class object
{
    private:
        sf::Sprite sprite_obj;

        sf::Texture texture_id_0;
        sf::Texture texture_id_1;
        sf::Texture texture_id_2;
        sf::Texture texture_id_3;

        int x_len = 250;
        int y_len = 140;

        int x = 0;
        int y = 0;

        int x_speed = 0;

        void spawn_obj(int id_obj)
        {
            switch (id_obj)
            {
                case 1:
                    sprite_obj.setTexture(texture_id_1);

                    x = -1000 - rand() % 700;
                    y = -410;

                    x_speed = 9;

                    break;
                case 2:
                    sprite_obj.setTexture(texture_id_2);

                    x = -1000 - rand() % 700;
                    y = -410;

                    x_speed = 9;

                    break;
                case 3:
                    sprite_obj.setTexture(texture_id_3);

                    x = -1000 - rand() % 700;
                    y = -270;

                    x_speed = 9;

                    break;
                default:
                    sprite_obj.setTexture(texture_id_0);

                    x = -1000 - rand() % 700;
                    y = -390;

                    x_speed = 9;
            }
        }
    public:
        object()
        {
            texture_id_0.loadFromFile("image/obj/id_0.png");
            texture_id_1.loadFromFile("image/obj/id_1.png");
            texture_id_2.loadFromFile("image/obj/id_2.png");
            texture_id_3.loadFromFile("image/obj/id_3.png");
            spawn_obj(0);
        }

        void draw_obj(sf::RenderWindow* window)
        {
            x += x_speed;
            sprite_obj.setOrigin(x, y);
            window->draw(sprite_obj);

            if (x > x_len)
                spawn_obj(rand() % 4);
        }

        int get_x(){
            return x;}
        int get_y(){
            return y;}
        int get_x_len(){
            return x_len;}
        int get_y_len(){
            return y_len;}

        void reset_pos()
        {
            spawn_obj(0);
        }
};
