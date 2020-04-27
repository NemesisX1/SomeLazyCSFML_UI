#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "create.c"

#define  MAX 7

typedef struct jam
{
    sfSprite *image[MAX];
    sfVector2f pos[MAX];
    int is_displayed[MAX];
    int ok;

    sfText *text[MAX];
    sfVector2f text_pos[MAX];
    sfRectangleShape *shape[MAX];

    sfRenderWindow *win;
    sfEvent event;
    bool running;
    sfSound *snd;
}jam_t;

static const char path[MAX][50] = {
"directory/augustin.png",
"directory/bahamas.jpg",
"directory/bali.jpg",
"directory/dubai.png",
"directory/hanoi.png",
"directory/patagonie.png",
"directory/rochmontain.jpg"
};

char name[MAX][50] = {
"Rio au Bresil",
"Les Bahamas",
"Bali (Indonesie)",
"Dubai (EAU)",
"Hanoi (Nepal)",
"Patagonie (Sud Amerique)",
"Les Montaignes Rocheuses (USA)"
};

/*UTILS FUNCTIONS*/
int max_element(int *tab, int len)
{
    int max = 0;
    int pos = 0;

    for (int i = 0; i < len; i++)
        if (tab[i] > max) {
            max = tab[i];
            pos = i;
        }
    return (pos );
}

/*UTILS FUNCTIONS*/

void init(jam_t *jam)
{
    jam->win = create_window(1200, 700, "Beautiful World !");
    jam->running = true;
    float x = 0, y = 50;
    float size = 40;

    for (int i = 0; i < MAX; i++, y += size + 10    ) {
        jam->is_displayed[i] = 0;
        jam->ok = 0;
        jam->image[i] = create_sprite(path[i], (sfVector2f){1 , 1});
        jam->shape[i] = sfRectangleShape_create();
        jam->text_pos[i] = (sfVector2f){20, y};

        sfSprite_setPosition(jam->image[i], (sfVector2f){300, 10});
        
        sfRectangleShape_setFillColor(jam->shape[i], sfBlue);
        sfRectangleShape_setOutlineThickness(jam->shape[i], 2);
        sfRectangleShape_setOutlineColor(jam->shape[i], sfColor_fromRGB(104, 97, 97));
        sfRectangleShape_setSize(jam->shape[i], (sfVector2f){250, size});
        sfRectangleShape_setPosition(jam->shape[i], jam->text_pos[i]);
        
        jam->text[i] =  create_text(name[i], "Moomycraft.ttf", jam->text_pos[i], 20);
        sfText_setColor(jam->text[i], sfWhite);
    }
}

void update(jam_t *jam)
{
    for (int i = 0 ; i < MAX; i++) {
        /*EVENTS*/
        if (mouse_on_rect(jam->shape[i], jam->win)
            && sfMouse_isButtonPressed(sfMouseLeft)) {
            jam->ok = 1;
            jam->is_displayed[i] += 1;
        }
        /*EVENTS*/

        /*EFFECTS*/
        if (mouse_on_rect(jam->shape[i], jam->win)) {
            sfRectangleShape_setFillColor(jam->shape[i], sfWhite);
            sfText_setColor(jam->text[i], sfBlue);
        } else {
            sfRectangleShape_setFillColor(jam->shape[i], sfBlue);
            sfText_setColor(jam->text[i], sfWhite);
        }
        /*EFFECTS*/
    }
}

void draw(jam_t *jam)
{
    int  max = max_element(jam->is_displayed, MAX);
    
    for (int i = 0; i < MAX; i++) {
        if (jam->ok == 1)
            sfRenderWindow_drawSprite(jam->win, jam->image[max], NULL);
        sfRenderWindow_drawRectangleShape(jam->win, jam->shape[i], NULL);
        sfRenderWindow_drawText(jam->win, jam->text[i], NULL);
    }
}

void destroy(jam_t *jam)
{
    for (int i = 0; i < MAX; i++) {
        sfSprite_destroy(jam->image[i]);
        sfText_destroy(jam->text[i]);
        sfRectangleShape_destroy(jam->shape[i]);
    }
}

void interactive_jam(jam_t *jam)
{
    init(jam);
    while (jam->running) {
        sfRenderWindow_clear(jam->win, sfColor_fromRGB(150, 144, 144));

        while (sfRenderWindow_pollEvent(jam->win, &jam->event))
                if (jam->event.type == sfEvtClosed)
                    jam->running = false;
        if (sfKeyboard_isKeyPressed(sfKeyEscape))
            jam->running = false;
        
        update(jam);
        draw(jam);

        sfRenderWindow_display(jam->win);
    }
    destroy(jam);
}

int main()
{
    jam_t jam;

    interactive_jam(&jam);
}