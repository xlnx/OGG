#ifndef OGG_GRAPHIC_COMPONENT__GRID__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENT__GRID__HEADER_FILE_____
#include "ogg_components.h"

    def_startup(ogg_grid_element) (
    );

    def_component(ogg_grid_element) (
        ogg_com_ptr object;
    );

    def_startup(ogg_grid) (
        ogg_coord size;
    );

    def_component(ogg_grid) (
        ogg_coord size;
        ogg_grid_element*** sub;
    );

    void set_grid_size(ogg_grid* self, ogg_coord size);

    ogg_com_ptr get_grid_elem(ogg_grid* grid, ogg_coord pos);

    ogg_com_ptr get_grid_coord(ogg_grid* grid, ogg_coord pos);

    ogg_bool paint_grid_elem(ogg_grid* grid, ogg_coord pos);

#endif //OGG_GRAPHIC_COMPONENT__GRID__HEADER_FILE_____