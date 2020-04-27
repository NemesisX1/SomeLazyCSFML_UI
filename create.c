#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

int mouse_on_text(sfText *text, sfRenderWindow *window)
{
    sfFloatRect rect = sfText_getGlobalBounds(text);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);

    if (mouse.x > rect.left && mouse.x < rect.left + rect.width
        && mouse.y > rect.top && mouse.y < rect.top + rect.height)
        return (1);
    return (0);
}

int mouse_on_rect(sfRectangleShape *sprite, sfRenderWindow *window)
{
    sfFloatRect rect = sfRectangleShape_getGlobalBounds(sprite);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);

    if (mouse.x > rect.left && mouse.x < rect.left + rect.width
        && mouse.y > rect.top && mouse.y < rect.top + rect.height)
        return (1);
    return (0);
}

int mouse_on_sprite(sfSprite *sprite, sfRenderWindow *window)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(sprite);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);

    if (mouse.x > rect.left && mouse.x < rect.left + rect.width
        && mouse.y > rect.top && mouse.y < rect.top + rect.height)
        return (1);
    return (0);
}

sfRenderWindow *create_window(unsigned int width,
          unsigned int height, char const *title)
{
    sfRenderWindow *Window;
    sfVideoMode mode;

    mode.width = width;
    mode.height = height;
    mode.bitsPerPixel = 30;
    Window = sfRenderWindow_create(mode, title, sfResize | sfClose, NULL);
    return Window;
}

sfSprite *create_sprite(char const *path, sfVector2f size)
{
    sfSprite *sprite;
    sfTexture *texture = sfTexture_createFromFile(path, NULL);

    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setScale(sprite, size);
    return sprite;
}

sfText *create_text(char *string, char *police, sfVector2f pos, unsigned int size)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile(police);

    sfText_setString(text, string);
    sfText_setFont(text, font);
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, pos);
    sfText_setCharacterSize(text, size);
    return text;
}

sfSound *create_sound(char *path, int loop, float volume, int play)
{
    sfSound *sound = sfSound_create();
    sfSoundBuffer *buffer = sfSoundBuffer_createFromFile(path);

    sfSound_setBuffer(sound, buffer);
    sfSound_setVolume(sound, volume);
    if (loop == 1)
        sfSound_setLoop(sound, sfTrue);
    else
        sfSound_setLoop(sound, sfFalse);
    if (play == 1)
        sfSound_play(sound);
    return sound;
}