#ifndef OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____
#include "graphic_components.h"

    typedef struct {
        coordf* point;
        unsigned size;
    } ogg_shape_vertex;

    typedef struct {
        ogg_com_startup startup;
        ogg_shape_vertex* vertex;
    } ogg_shape_info;

    typedef struct {
        ogg_component com;
        ogg_shape_vertex* vertex;
    } ogg_shape;

    ogg_shape* create_shape(const ogg_shape_info* st);

    ogg_shape_vertex* vertex_list(unsigned n, ...);

    coordf vertex(float x, float y);

#endif //OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____