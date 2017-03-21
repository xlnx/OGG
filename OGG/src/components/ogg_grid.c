#include <GL/glut.h>
#include "components/ogg_grid.h"

    static ogg_event_handler ogg_grid_element_vtable[OGG_EVENT_COUNT] = { 0 };

    def_startup(ogg_grid_element) (
    );
    default_startup(ogg_grid_element) (
    )

    static def_constructor(ogg_grid_element, args)
    {
        this->object = 0;
    }

    /* GRID */

    static void destroy_grid(ogg_grid* grid);

    static void paint_grid(ogg_grid* grid);

    def_vtable(ogg_grid) (
        [OGG_DESTROY_EVENT] = destroy_grid,
        [OGG_PAINT_EVENT] = paint_grid
    );

    default_startup(ogg_grid) (
        .size = { 1, 1 }
    )

    def_constructor(ogg_grid, args)
    {
        this->size.x = args->size.x;
        this->size.y = args->size.y;
        ogg_coord pos = { 0, 0 };
        this->sub = (ogg_grid_element***)malloc(args->size.y * sizeof(ogg_grid_element**));
# ifdef DEBUG
        alloc_memory++;
# endif
        for (pos.y = 0; pos.y != args->size.y; ++pos.y) {
            this->sub[pos.y] = (ogg_grid_element**)calloc(args->size.x, sizeof(ogg_grid_element*));
# ifdef DEBUG
            alloc_memory++;
# endif
            for (pos.x = 0; pos.x != args->size.x; ++pos.x) {
                ogg_create(ogg_grid_element)(
                    .ogg_component = {
                        .anchor = {
                            .type = ogg_anchor_pec,
                            .pec = {
                                .left = (float)pos.x * 100 / args->size.x,
                                .right = (float)(pos.x + 1) * 100 / args->size.x,
                                .top = (float)pos.y * 100 / args->size.y,
                                .bottom = (float)(pos.y + 1) * 100 / args->size.y
                            }
                        },
                        .parent = (ogg_component*)this
                    }
                )(this->sub[pos.y][pos.x]);
            }
        }
    }

    static void destroy_grid(ogg_grid* grid)
    {
        unsigned i = 0;
        for (; i != grid->size.y; ++i) {
            free(grid->sub[i]);
# ifdef DEBUG
            alloc_memory--;
# endif
        }
        free(grid->sub);
# ifdef DEBUG
        alloc_memory--;
# endif
    }

    void paint_grid(ogg_grid* grid)
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    ogg_com_ptr get_grid_elem(ogg_grid* grid, ogg_coord pos)
    {
        return grid->sub[pos.y][pos.x]->object;
    }

    ogg_bool paint_grid_elem(ogg_grid* grid, ogg_coord pos)
    {
        if (pos.x >= grid->size.x || pos.y >= grid->size.y) {
            return ogg_false;
        }
        ogg_send_event(grid->sub[pos.y][pos.x], OGG_PAINT_EVENT);
        glFlush();
        return ogg_true;
    }

    ogg_com_ptr get_grid_coord(ogg_grid* grid, ogg_coord pos)
    {
        return grid->sub[pos.y][pos.x];
    }
