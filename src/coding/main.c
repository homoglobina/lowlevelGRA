#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "game.h"





int main()
{

    // Create the window
    sfVideoMode mode = {WIDTH, HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "TOP GUN", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    
    
    
    // Call the functions to load the texture and create the sprites
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


        // Clear the window
        sfRenderWindow_clear(window, sfBlue);


        // Draw the sprite onto the window
        drawEnemy(window, &adam);
        drawPlayer(window);


        // Display the window contents
        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
    return 0;
}
