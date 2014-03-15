#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_X 800
#define MAX_Y 600
#define V_MAX_X 0
#define V_MAX_Y 0
#define COLOR_BITS 32
#define VIDEO_CARD GFX_AUTODETECT_WINDOWED
#define DIGI_CARD DIGI_AUTODETECT
#define MIDI_CARD MIDI_AUTODETECT

int abreAllegro(void)
{
    int retorno = 1;

    allegro_init();

    install_keyboard();
    install_mouse();

    install_timer();

    srand((unsigned)time(NULL));

    set_color_depth(COLOR_BITS);
    if (set_gfx_mode(VIDEO_CARD, MAX_X, MAX_Y, V_MAX_X, V_MAX_Y) < 0)
    {
        if (set_gfx_mode(GFX_AUTODETECT, MAX_X, MAX_Y, V_MAX_X, V_MAX_Y) < 0)
        {
            allegro_message("Erro ao inicializar o modo grafico");
            retorno = 0;
        }
    }

    if (COLOR_BITS == 32)	set_alpha_blender(); // instala o canal alpha (funciona apenas em 32 bits)

    if (install_sound(DIGI_CARD, MIDI_CARD, NULL) < 0)
    {
        if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) < 0)
        {
            allegro_message("Erro ao inicializar o som");
            retorno = 0;
        }
    }

    return retorno;
}
