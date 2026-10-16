
#include <nds.h>
#include <stdio.h>

/* Crossed Signals - DS prototype */

static void draw_intro(void) {
    consoleClear();
    iprintf("CROSSED SIGNALS\n");
    iprintf("DS PROTOTYPE 0.0.1\n\n");
    iprintf("THE EMPTY COURTROOM\n\n");
    iprintf("Every seat is empty.\n");
    iprintf("Yet the recording light is on.\n\n");
    iprintf("VOICE: Apollo... don't trust\n");
    iprintf("the memory you haven't made.\n\n");
    iprintf("Press A to continue.");
}

static void draw_choice(int selected) {
    consoleClear();
    iprintf("CROSSED SIGNALS\n\n");
    iprintf("A young man's voice answers.\n");
    iprintf("It seems to know Apollo.\n\n");
    iprintf("What should Apollo do?\n\n");
    iprintf("%s Ask who is speaking\n\n",
        selected == 0 ? ">" : " ");
    iprintf("%s Examine the red light\n\n",
        selected == 1 ? ">" : " ");
    iprintf("UP/DOWN then A to choose.");
}

static void draw_result(int choice) {
    consoleClear();
    iprintf("CROSSED SIGNALS\n\n");

    if (choice == 0) {
        iprintf("APOLLO: Who is this?\n\n");
        iprintf("VOICE: Someone who remembers\n");
        iprintf("a door you haven't opened.\n\n");
        iprintf("The monitor displays:\nJUNPEI\n");
    } else {
        iprintf("Apollo studies the red light.\n\n");
        iprintf("It isn't connected to the\n");
        iprintf("courtroom recording system.\n\n");
        iprintf("NONARY RESEARCH / LIVE LINK\n");
    }

    iprintf("\nPress START to replay.");
}

int main(void) {
    consoleDemoInit();

    int scene = 0;
    int selected = 0;
    int chosen = 0;

    while (1) {
        scanKeys();
        int down = keysDown();

        if (scene == 0) {
            draw_intro();
            if (down & KEY_A)
                scene = 1;
        } else if (scene == 1) {
            draw_choice(selected);

            if (down & KEY_UP)
                selected = 0;
            if (down & KEY_DOWN)
                selected = 1;

            if (down & KEY_A) {
                chosen = selected;
                scene = 2;
            }

            if (down & KEY_B)
                scene = 0;
        } else {
            draw_result(chosen);
            if (down & KEY_START) {
                scene = 0;
                selected = 0;
            }
        }

        swiWaitForVBlank();
    }


return 0;
}
