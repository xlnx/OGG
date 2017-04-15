#ifndef OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____
#include "ogg_components.h"

    def_startup(ogg_shape) (
        ogg_color color;
        ogg_vertex* vertex;
    );

    def_startup_inh(ogg_rect, ogg_shape) (
    );

    def_component(ogg_shape) (
        ogg_color color;
        ogg_vertex* vertex;
    );

    def_component_inh(ogg_rect, ogg_shape)(
    );

    void set_shape_color(ogg_com_ptr self, ogg_color color);

#endif //OGG_GRAPHIC_COMPONENTS__SHAPE__HEADER_FILE_____