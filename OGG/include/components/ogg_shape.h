#ifndef OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____
#include "ogg_components.h"

    typedef struct {
        coordf* point;
        unsigned size;
    } ogg_shape_vertex;

    typedef struct {
        float R, G, B;
    } ogg_color;

    def_startup(ogg_shape) (
        ogg_color color;
        ogg_shape_vertex* vertex;
    );

    def_startup_inh(ogg_rect, ogg_shape) (
    );

    def_component(ogg_shape) (
        ogg_color color;
        ogg_shape_vertex* vertex;
    );

    def_component_inh(ogg_rect, ogg_shape)(
    );

    void set_color(ogg_com_ptr this, ogg_color color);

    ogg_shape_vertex* vertex_list(unsigned n, ...);

    coordf vertex(float x, float y);

    static const ogg_color OGG_RED = {
        255.0/255.0, 0.0, 0.0
    };
    static const ogg_color OGG_GREEN = {
        0.0, 255.0/255.0, 0.0
    };
    static const ogg_color OGG_BLUE = {
        0.0, 0.0, 255.0/255.0
    };

#endif //OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____