#include "dvd.h"
#include <stdlib.h>
#include <debug.h>

dvd_object_t *create_dvdobject() {
    dvd_object_t *d = (dvd_object_t *)malloc(sizeof(dvd_object_t));
    d->SX = 1;
    d->SY = 1;
    d->sw = 0;
    d->sy = 0;
    d->x = 0;
    d->y = 0;
    return d;
}

dvd_object_t *create_dvdobject_from_sprite(sprite_t *spr) {
    dvd_object_t *d = create_dvdobject();
    d->sw = spr->width;
    d->sy = spr->height;
    return d;
}
void update_dvdobject(dvd_object_t *obj, float delta) {
    //debugf("x: %d y: %d sx: %d sy: %d ys: (%d %d) xs: (%d %d)\n", obj->x, obj->y, obj->SX, obj->SY, (obj->x + obj->sw >= 640), (obj->x <= 0), (obj->y + obj->sy >= 480), (obj->y <= 0));
    if((obj->x + obj->sw >= 640) || (obj->x <= 0)) {
        obj->SX = -obj->SX;
        obj->x += (640 - (obj->x + obj->sy));
    }
    if((obj->y + obj->sy >= 480) || (obj->y <= 0)) {
        obj->SY = -obj->SY;
        obj->y += (480 - (obj->y + obj->sy));
    }
    obj->x += obj->SX * delta * 60.f;
    obj->y += obj->SY * delta * 60.f;
}