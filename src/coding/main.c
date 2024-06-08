#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <game.h>

int main()
{
    sfVideoMode mode = {800, 600, 64};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Gra", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    sfCircleShape* shape = sfCircleShape_create();
    sfCircleShape_setRadius(shape, 200.f);
    sfCircleShape_setFillColor(shape, sfBlue);

    while (sfRenderWindow_isOpen(window))
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawCircleShape(window, shape, NULL);
        sfRenderWindow_display(window);
    }

    sfCircleShape_destroy(shape);
    sfRenderWindow_destroy(window);
    return 0;
}
