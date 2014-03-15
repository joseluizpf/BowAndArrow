#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

void fechaAllegro(void)
{
    remove_timer();
    remove_mouse();
    remove_sound();
    remove_keyboard();
    allegro_exit();
}
