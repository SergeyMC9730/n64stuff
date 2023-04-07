#include <libdragon.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

static volatile uint32_t animcounter = 0;

void update_counter( int ovfl )
{
    fprintf(stderr, "TEST %ld\n", animcounter);
    animcounter++;
}

int main(void) {
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_OFF);
    dfs_init(DFS_DEFAULT_LOCATION);
    rdp_init();
    controller_init();
    timer_init();

    new_timer(TIMER_TICKS(1000000 / 30), TF_CONTINUOUS, update_counter);

    while(1) {
        static display_context_t disp = 0;
        while( !(disp = display_lock()) );
        graphics_fill_screen( disp, 0xFFFFFFFF );
        graphics_set_color( 0x0, 0xFFFFFFFF );
        graphics_draw_box(disp, 100, 100, 50, 50, (uint32_t)rand());
        graphics_draw_text( disp, 20, 20, "good" );
        display_show(disp);
    }

    return 0;
}