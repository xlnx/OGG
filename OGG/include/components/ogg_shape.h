#ifndef OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____
#include "ogg_components.h"

    typedef struct {
        coordf* point;
        unsigned size;
    } ogg_shape_vertex;

    def_startup(ogg_shape) (
        ogg_shape_vertex* vertex;
    );

    def_startup_inh(ogg_rect, ogg_shape) (
    );

    def_component(ogg_shape) (
        ogg_shape_vertex* vertex;
    );

    def_component_inh(ogg_rect, ogg_shape)(
    );

    constructor(ogg_shape);

    constructor(ogg_rect);

    ogg_shape_vertex* vertex_list(unsigned n, ...);

    coordf vertex(float x, float y);

#endif //OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____