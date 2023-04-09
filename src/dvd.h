#pragma once

#include <libdragon.h>

#pragma pack(push, 1)
typedef struct dvd_object_t {
    int x;
    int y;
    int sw;
    int sy;
    int SX;
    int SY;
} dvd_object_t;
#pragma pack(pop)

dvd_object_t *create_dvdobject();
dvd_object_t *create_dvdobject_from_sprite(sprite_t *spr);
void update_dvdobject(dvd_object_t *obj, float delta);