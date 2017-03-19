#ifndef OGG_GRAPHIC_COMPONENT__GRID__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENT__GRID__HEADER_FILE_____
#include "graphic_components.h"

    def_component (
        ogg_com_ptr object;
    ) ogg_grid_element;

    def_startup (
        ogg_coord size;
    ) ogg_grid_info;

    def_component (
        ogg_coord size;
        ogg_grid_element ***sub;
    ) ogg_grid;

    /* construct a grid */
    ogg_grid* create_grid(const ogg_grid_info* st);

    ogg_com_ptr get_grid_elem(ogg_grid* grid, ogg_coord pos);

    ogg_bool paint_grid_elem(ogg_grid* grid, ogg_coord pos);

    ogg_com_startup make_grid_startup(ogg_grid* grid, ogg_coord pos);

#endif //OGG_GRAPHIC_COMPONENT__GRID__HEADER_FILE_____