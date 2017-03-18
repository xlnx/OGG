#include "graphic_component_grid.h"

# ifdef __cplusplus
extern "C"{
# endif

    static ogg_grid_element* create_grid_element(ogg_grid* parent, ogg_coord pos);

    static void destroy_grid_element(ogg_grid_element* grid_elem);

    static void paint_grid_element(ogg_grid_element* grid_elem);

    static ogg_event_handler ogg_grid_elem_vtable[] = {
        destroy_grid_element, // OGG_DESTROY_EVENT
        paint_grid_element    // OGG_PAINT_EVENT
    };

    static ogg_grid_element* create_grid_element(ogg_grid* parent, ogg_coord pos)
    {
        ogg_grid_element* grid_elem = (ogg_grid_element*)malloc(sizeof(ogg_grid_element));
        ogg_anchor anchor = {
            .type = ogg_anchor_pec,
            .pec = {
                .left = (float)pos.x * 100 / parent->size.x,
                .right = (float)(pos.x + 1) * 100 / parent->size.x,
                .top = (float)pos.y * 100 / parent->size.y,
                .bottom = (float)(pos.y + 1) * 100 / parent->size.y
            }
        };
        ogg_component_info info = {
            .anchor = &anchor,
            .parent = (ogg_component*)parent,
            .vptr = ogg_grid_elem_vtable
        };
        create_component(grid_elem, &info);
        grid_elem->object = 0;
        return grid_elem;
    }

    static void destroy_grid_element(ogg_grid_element* grid_elem)
    {
        if (grid_elem->object != 0) {
            destroy_component(grid_elem->object);
        }
        free(grid_elem);
    }

    static void paint_grid_element(ogg_grid_element* grid_elem)
    {
        if (grid_elem->object != 0) {
            ogg_send_event(grid_elem->object, OGG_PAINT_EVENT);
        }
    }

    static ogg_event_handler ogg_grid_vtable[] = {
        destroy_grid, // OGG_DESTROY_EVENT
        paint_grid    // OGG_PAINT_EVENT
    };

    ogg_grid* create_grid(const ogg_grid_info* st)
    {
        ogg_grid *grid = (ogg_grid*)malloc(sizeof(ogg_grid));
        ogg_component_info info = {
            .anchor = &st->startup.anchor,
            .parent = st->startup.parent,
            .vptr = ogg_grid_vtable
        };
        create_component(grid, &info);
        grid->size.x = st->size.x;
        grid->size.y = st->size.y;
        ogg_coord pos = { 0, 0 };
        grid->sub = (ogg_grid_element***)malloc(st->size.y * sizeof(ogg_grid_element**));
        for (pos.y = 0; pos.y != st->size.y; ++pos.y) {
            grid->sub[pos.y] = (ogg_grid_element**)calloc(st->size.x, sizeof(ogg_grid_element*));
            for (pos.x = 0; pos.x != st->size.x; ++pos.x) {
                grid->sub[pos.y][pos.x] = create_grid_element(grid, pos);
            }
        }
        return grid;
    }

    void destroy_grid(ogg_grid* grid)
    {
        unsigned i = 0, j;
        for (; i != grid->size.y; ++i) {
            for (j = 0; j != grid->size.x; ++j) {
                destroy_component(&grid->sub[i][j]);
            }
            free(grid->sub[i]);
        }
        free(grid->sub);
        free(grid);
    }

    void paint_grid(ogg_grid* grid)
    {
        ogg_coord pos;
        glClear(GL_COLOR_BUFFER_BIT);
        for (pos.x = 0; pos.x != grid->size.x; ++pos.x) {
            for (pos.y = 0; pos.y != grid->size.y; ++pos.y) {
                paint_grid_elem(grid, pos);
            }
        }
    }

    void set_grid_elem(ogg_grid* grid, ogg_com_ptr com, ogg_coord pos)
    {
        grid->sub[pos.y][pos.x]->object = com;
        ((ogg_component*)com)->parent = (ogg_component*)grid->sub[pos.y][pos.x];
    }

    void destroy_grid_elem(ogg_grid* grid, ogg_coord pos)
    {
        if (grid->sub[pos.y][pos.x]->object != 0)
            destroy_component(&grid->sub[pos.y][pos.x]->object);
    }

    ogg_bool paint_grid_elem(ogg_grid* grid, ogg_coord pos)
    {
        if (pos.x >= grid->size.x || pos.y >= grid->size.y) {
            return ogg_false;
        }
        ogg_send_event(grid->sub[pos.y][pos.x], OGG_PAINT_EVENT);
        return ogg_true;
    }

# ifdef __cplusplus
}
#endif
