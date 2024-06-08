#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "game.h"

int main()
{

    // Create the window
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "SFML TUTORIAL", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    // Call the function to load the texture and create the sprite
    player();

    while (sfRenderWindow_isOpen(window))
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }


        // Exit
        if (sfKeyboard_isKeyPressed(1))
            sfRenderWindow_close(window);

        sfRenderWindow_clear(window, sfBlack);

        // Draw the sprite onto the window
        draw(window);


        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
    return 0;
}
