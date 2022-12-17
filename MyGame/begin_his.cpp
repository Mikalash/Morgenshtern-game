#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

void wait_event(sf::RenderWindow* window)
{
    sf::Event event;

    while (1)
        if (window->pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Space)
                    break;
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return;
            }
        }
}

void print_pic(sf::RenderWindow* window, char* path_pic)
{
    sf::Texture texture;
    sf::Sprite sprite;

    texture.loadFromFile(path_pic);
    sprite.setTexture(texture);
    window->draw(sprite);
    window->display();
}

void start_his(sf::RenderWindow* window)
{
    sf::Texture texture;
    sf::Sprite sprite;

    print_pic(window, "image/begin/pic1.png");
    wait_event(window);

    print_pic(window, "image/begin/pic2.png");
    wait_event(window);

    print_pic(window, "image/begin/pic3.png");
    wait_event(window);

    print_pic(window, "image/begin/pic4.png");
    wait_event(window);

    print_pic(window, "image/begin/pic5.png");
    wait_event(window);

    print_pic(window, "image/begin/pic6.png");
    wait_event(window);

    print_pic(window, "image/begin/pic7.png");
    wait_event(window);

    print_pic(window, "image/begin/pic8.png");
    wait_event(window);

    print_pic(window, "image/begin/pic9.png");
    wait_event(window);
}
