#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "game.h"

int main()
{

    // Create the window
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "TOP GUN", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    // Call the function to load the texture and create the sprite
    player();


    struct enemyStruct adam;
    enemy(&adam);

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

        sfRenderWindow_clear(window, sfBlue);

        // Draw the sprite onto the window
        drawPlayer(window);
        drawEnemy(window, &adam);


        // Display the window contents
        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
    return 0;
}
