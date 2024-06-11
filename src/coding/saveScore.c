#include "game.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SCORES 100

struct ScoreEntry {
    char name[100];
    int score;
};

int compareScores(const void *a, const void *b) {
    struct ScoreEntry *entryA = (struct ScoreEntry *)a;
    struct ScoreEntry *entryB = (struct ScoreEntry *)b;
    return entryB->score - entryA->score;
}

void showScore(sfRenderWindow *window) {
    FILE *fptr;
    struct ScoreEntry scores[MAX_SCORES];
    int scoreCount = 0;

    // Open the file in read mode
    fptr = fopen("scores.txt", "r");

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(fptr, "%s %d", scores[scoreCount].name, &scores[scoreCount].score) != EOF) {
        scoreCount++;
    }
    fclose(fptr);

    // Sort the scores array
    qsort(scores, scoreCount, sizeof(struct ScoreEntry), compareScores);

    sfFont *font = sfFont_createFromFile("coding/textures/zerovelo.ttf");
    sfText *text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 24);
    sfText_setColor(text, sfWhite);

    sfRenderWindow_clear(window, sfBlack);

    float yOffset = 10.0f;

    // Display the top 5 scores
    for (int i = 0; i < scoreCount && i < 5; i++) {
        char displayStr[150];
        snprintf(displayStr, sizeof(displayStr), "%d. %s %d", i + 1, scores[i].name, scores[i].score);

        sfText_setString(text, displayStr);
        sfText_setPosition(text, (sfVector2f){10, yOffset});
        sfRenderWindow_drawText(window, text, NULL);

        yOffset += 30.0f;
    }

    sfRenderWindow_display(window);

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            } else if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
                sfRenderWindow_close(window);
            }
        }
    }

    sfText_destroy(text);
    sfFont_destroy(font);
}

void addScore(const char *name, int score) {
    FILE *fptr;

    // Open a file in write mode
    fptr = fopen("scores.txt", "a"); // Use "a" to append to the file

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write the name and score to the file
    fprintf(fptr, "%s %d\n", name, score);

    // Close the file
    fclose(fptr);
}

void getPlayerName(char *playerName, int maxLen, sfRenderWindow *window) {
    sfEvent event;
    int index = 0;
    playerName[0] = '\0'; // Initialize the string

    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            } else if (event.type == sfEvtTextEntered) {
                if (event.text.unicode == '\b' && index > 0) { // Handle backspace
                    index--;
                    playerName[index] = '\0';
                } else if (event.text.unicode < 128 && index < maxLen - 1) {
                    playerName[index++] = (char)event.text.unicode;
                    playerName[index] = '\0';
                }
            } else if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
                return; // Return on Enter key press
            }
        }

        sfRenderWindow_clear(window, sfBlack);

        // Display current name
        sfFont *font = sfFont_createFromFile("coding/textures/zerovelo.ttf");
        sfText *text = sfText_create();
        sfText_setString(text, playerName);
        sfText_setFont(text, font);
        sfText_setCharacterSize(text, 24);
        sfText_setColor(text, sfWhite);
        sfText_setPosition(text, (sfVector2f){10, 10});
        sfRenderWindow_drawText(window, text, NULL);

        sfRenderWindow_display(window);

        sfText_destroy(text);
        sfFont_destroy(font);
    }
}
