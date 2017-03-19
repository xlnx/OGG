#ifndef OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____
#include "graphic_components.h"

    typedef struct {
        coordf* point;
        unsigned size;
    } ogg_shape_vertex;

    def_startup (
        ogg_shape_vertex* vertex;
    ) ogg_shape_info;

    def_component (
        ogg_shape_vertex* vertex;
    ) ogg_shape;

    def_startup(
    ) ogg_rect_info;

    def_component_inh(ogg_shape,

    ) ogg_rect;

    //void create_shape_dest(ogg_shape* shape, const ogg_shape_info* st);

    ogg_shape* create_shape(const ogg_shape_info* st);

    //void create_rect_dest(ogg_rect* rect, const ogg_rect_info* st);

    ogg_rect* create_rect(const ogg_rect_info* st);

    ogg_shape_vertex* vertex_list(unsigned n, ...);

    coordf vertex(float x, float y);

#endif //OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____