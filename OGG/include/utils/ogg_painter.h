#ifndef OGG_PAINTER__HEADER_FILE___
#define OGG_PAINTER__HEADER_FILE___

#include "../../dependency/freeglut/freeglut/include/GL/freeglut.h"
#include "ogg_utils.h"

typedef GLuint ogg_texture;

typedef struct {
    float x, y, r;
} ogg_painter_coord;

ogg_painter_coord make_painter_coord(float x, float y, float r);

typedef struct {
    unsigned int vertex_count;
    pointf *vertex;
} Togg_object, *ogg_object;

ogg_bool ogg_object_overlap(ogg_object, ogg_painter_coord, ogg_object, ogg_painter_coord);

void ogg_rotate_object(ogg_object, float r);

typedef struct {
    Togg_object object;
    ogg_texture texture;
    pointf *vertex;
} Togg_texture_object, *ogg_texture_object;

void ogg_paint_texture_object(ogg_texture_object self, ogg_painter_coord p);

#define ogg_rotate_texture_object(a, r) \
    (ogg_rotate_object((a), (r)))

#define ogg_texture_object_overlap(a, p1, b, p2) \
    (ogg_object_overlap(&(a)->object, (p1), &(b)->object), (p2))

//typedef struct {

//} Togg_anim_object, *ogg_anim_object;

#endif //OGG_PAINTER__HEADER_FILE___