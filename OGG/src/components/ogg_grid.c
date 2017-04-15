#include <GL/glut.h>
#include "components/ogg_grid.h"

    def_vtable(ogg_grid_element)(
    );

    //default_startup(ogg_grid_element)(
    //)

    def_constructor(ogg_grid_element, args)
    {
        self->object = 0;
    }

    def_destructor(ogg_grid_element)
    {   /* do nothing */
    }

    /* GRID */

    handler(ogg_grid, OGG_PAINT_EVENT);

    static void destroy_grid(ogg_grid* self);

    static void set_grid_size_helper(ogg_grid* self, ogg_coord size);

    def_vtable(ogg_grid) (
        [OGG_PAINT_EVENT] = ogg_handler(ogg_grid, OGG_PAINT_EVENT)
    );

    //default_startup(ogg_grid) (
    //    .size = { 1, 1 }
    //)

    def_constructor(ogg_grid, args)
    {
        set_grid_size_helper(self, args->size);
    }

    def_destructor(ogg_grid)
    {
        destroy_grid(self);
    }

    def_handler(ogg_grid, OGG_PAINT_EVENT)
    {
        //glClear(GL_COLOR_BUFFER_BIT);
    }

    static void destroy_grid(ogg_grid* self)
    {
        unsigned i = 0;
        for (; i != self->size.y; ++i) {
            free(self->sub[i]);
# ifdef DEBUG
            alloc_memory--;
# endif
        }
        free(self->sub);
# ifdef DEBUG
        alloc_memory--;
# endif
    }

    static void set_grid_size_helper(ogg_grid* self, ogg_coord size)
    {
        ogg_coord pos = { 0, 0 };
        self->size.x = size.x;
        self->size.y = size.y;
        self->sub = (ogg_grid_element***)malloc(size.y * sizeof(ogg_grid_element**));
# ifdef DEBUG
        alloc_memory++;
# endif
        for (pos.y = 0; pos.y != size.y; ++pos.y) {
            self->sub[pos.y] = (ogg_grid_element**)calloc(size.x, sizeof(ogg_grid_element*));
# ifdef DEBUG
            alloc_memory++;
# endif
            for (pos.x = 0; pos.x != size.x; ++pos.x) {
                ogg_create(ogg_grid_element)(
                    .ogg_component = {
                    .anchor = {
                        .type = ogg_anchor_pec,
                        .pec = {
                            .left = (float)pos.x * 100 / size.x,
                            .right = (float)(pos.x + 1) * 100 / size.x,
                            .top = (float)pos.y * 100 / size.y,
                            .bottom = (float)(pos.y + 1) * 100 / size.y
                        }
                    },
                    .parent = (ogg_component*)self
                }
                )(self->sub[pos.y][pos.x]);
            }
        }
    }

    void set_grid_size(ogg_grid* self, ogg_coord size)
    {
        ogg_coord pos = { 0, 0 };
        for (pos.y = 0; pos.y != self->size.y; ++pos.y) {
            for (pos.x = 0; pos.x != self->size.x; ++pos.x) {
                ogg_destroy(get_grid_coord(self, pos));
            }
        }
        destroy_grid(self);
        set_grid_size_helper(self, size);
        ogg_send_event(self, OGG_PAINT_EVENT);
    }

    ogg_com_ptr get_grid_elem(ogg_grid* self, ogg_coord pos)
    {
        return self->sub[pos.y][pos.x]->object;
    }

    ogg_bool paint_grid_elem(ogg_grid* self, ogg_coord pos)
    {
        if (pos.x >= self->size.x || pos.y >= self->size.y) {
            return ogg_false;
        }
        ogg_send_event(self->sub[pos.y][pos.x], OGG_PAINT_EVENT);
        ogg_flush_screen();
        return ogg_true;
    }

    ogg_com_ptr get_grid_coord(ogg_grid* self, ogg_coord pos)
    {
        return self->sub[pos.y][pos.x];
    }
