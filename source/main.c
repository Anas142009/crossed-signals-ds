
#include <nds.h>
#include <stdio.h>

/* Crossed Signals - Dual-screen prototype */

static PrintConsole topScreen;
static PrintConsole bottomScreen;

static void draw_top(int scene, int chosen) {
    consoleSelect(&topScreen);
    consoleClear();

    iprintf("CROSSED SIGNALS\n");
    iprintf("------------------------------\n\n");

    if (scene == 0) {
        iprintf("    THE EMPTY COURTROOM\n\n");
        iprintf("  .------------------------.\n");
        iprintf("  |      JUDGE'S BENCH     |\n");
        iprintf("  '------------------------'\n\n");
        iprintf("    o                  o\n");
        iprintf("      EMPTY SEATS\n\n");
        iprintf("  RECORDING LIGHT: [ RED ]\n\n");
        iprintf("  CASE STATUS: UNKNOWN\n");
    } else if (scene == 1) {
        iprintf("      COURTROOM / LIVE\n\n");
        iprintf("  The courtroom is deserted.\n\n");
        iprintf("  RECORDING LIGHT: [ RED ]\n\n");
        iprintf("  INCOMING SIGNAL: UNKNOWN\n\n");
        iprintf("  A voice addresses Apollo.\n");
    } else {
        iprintf("      COURTROOM / LIVE\n\n");
        iprintf("  INVESTIGATION LOG\n\n");

        if (chosen == 0) {
            iprintf("  Topic: Unknown speaker\n\n");
            iprintf("  MONITOR: JUNPEI\n");
        } else {
            iprintf("  Object: Red light\n\n");
            iprintf("  NONARY RESEARCH\n");
            iprintf("  LIVE LINK: ACTIVE\n");
        }

        iprintf("\n  STATUS: INVESTIGATION\n");
    }
}

static void draw_bottom(int scene, int selected, int chosen) {
    consoleSelect(&bottomScreen);
    consoleClear();

    if (scene == 0) {
        iprintf("APOLLO: Where am I?\n\n");
        iprintf("Every seat is empty.\n");
        iprintf("The recording light is on.\n\n");
        iprintf("A voice whispers:\n");
        iprintf("\"Don't trust a memory you\n");
        iprintf("haven't made.\"\n\n");
        iprintf("Press A to continue.");
    } else if (scene == 1) {
        iprintf("A young man's voice answers.\n");
        iprintf("It seems to know Apollo.\n\n");
        iprintf("What should Apollo do?\n\n");

        iprintf("%s Ask who is speaking\n\n",
                selected == 0 ? ">" : " ");

        iprintf("%s Examine the red light\n\n",
                selected == 1 ? ">" : " ");

        iprintf("UP/DOWN then A to choose.\n");
        iprintf("B: Return to opening.");
    } else {
        if (chosen == 0) {
            iprintf("APOLLO: Who is this?\n\n");
            iprintf("VOICE: Someone who remembers\n");
            iprintf("a door you haven't opened.\n\n");
            iprintf("The monitor displays:\n");
            iprintf("JUNPEI\n\n");
        } else {
            iprintf("Apollo studies the red light.\n\n");
            iprintf("It isn't connected to the\n");
            iprintf("courtroom recording system.\n\n");
            iprintf("NONARY RESEARCH / LIVE LINK\n\n");
        }

        iprintf("Press START to replay.");
    }
}

int main(void) {
    /* Configure the two DS displays. */
    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);

    consoleInit(&topScreen, 0,
                BgType_Text4bpp, BgSize_T_256x256,
                31, 0, true, true);

    consoleInit(&bottomScreen, 0,
                BgType_Text4bpp, BgSize_T_256x256,
                31, 0, false, true);

    int scene = 0;
    int selected = 0;
    int chosen = 0;

    while (1) {
        scanKeys();
        int down = keysDown();

        if (scene == 0) {
            if (down & KEY_A)
                scene = 1;
        } else if (scene == 1) {
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
            if (down & KEY_START) {
                scene = 0;
                selected = 0;
            }
        }

        draw_top(scene, chosen);
        draw_bottom(scene, selected, chosen);

        swiWaitForVBlank();
    }

    return 0;
}
