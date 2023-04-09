#include <libdragon.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <debug.h>
#include "dvd.h"
#include "time.h"

#define volatime volatile

static volatile uint32_t col = 0;
static volatile uint32_t fps = 60;

#pragma pack(push, 1)

void plat64wait(int ms) {
    ms *= 10;
    uint32_t expected = SystemUptime.milliseconds + ms;
    while(1) {
        if(SystemUptime.milliseconds == expected) return;
        col++;
    }
}

int main(void) {
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    
    timer_init();
    timer_link_t *t = new_timer(TIMER_TICKS(1000000 / 10000), TF_CONTINUOUS, __time_update);

    dfs_init(DFS_DEFAULT_LOCATION);
    rdp_init();
    controller_init();
    debug_init_isviewer();

    char *data = (char *)malloc(128);

    int fp0 = dfs_open("/taskbar00.sprite");
    sprite_t *hellospr = (sprite_t *)malloc(dfs_size(fp0));
    dfs_read(hellospr, dfs_size(fp0), 1, fp0);
    debugf("fp: %d | size: %d | addr: %lX\n", fp0, dfs_size(fp0), (uint32_t)hellospr);
    debugf("size: %d %d\n", hellospr->width, hellospr->height);
    debugf("data: %s\n", hellospr->data);
    dfs_close(fp0);

    // dvd_object_t *dobj = create_dvdobject_from_sprite(hellospr);
    // dvd_object_t *dobj1 = create_dvdobject_from_sprite(hellospr); dobj1->x = rand() % 60; dobj1->y = rand() % 60;
    // dvd_object_t *dobj2 = create_dvdobject_from_sprite(hellospr); dobj2->x = rand() % 60; dobj2->y = rand() % 60;
    // dvd_object_t *dobj3 = create_dvdobject_from_sprite(hellospr); dobj3->x = rand() % 60; dobj3->y = rand() % 60;

    int x = 0;
    int y = 0;

    float delta = 1000.f / fps / 1000.f;
    
    debugf("\nuptime before render: %f\n", SystemUptime.seconds);

    while(1) {
        static display_context_t disp = 0;
        while( !(disp = display_lock()) );

        graphics_fill_screen( disp, 0xFFFFFFFF );
        graphics_set_color( 0x0, 0xFFFFFFFF );

        sprintf(data, "uptime: %f\n", SystemUptime.seconds);
        graphics_draw_text( disp, 20, 20, (const char *)data );

        rdp_sync(SYNC_PIPE);
        rdp_set_default_clipping();
        rdp_enable_texture_copy();

        rdp_attach(disp);
        rdp_sync(SYNC_PIPE);
        
        rdp_load_texture(0, 0, MIRROR_DISABLED, hellospr);
        rdp_draw_sprite(0, 0, 0, MIRROR_DISABLED);
        
        rdp_detach();
        display_show(disp);

        plat64wait(1000 / fps);
    }

    return 0;
}