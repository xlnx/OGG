#include <GL/glut.h>
#include "components/ogg_grid.h"

    def_vtable(ogg_grid_element)(
    );

    default_startup(ogg_grid_element)(
    )

    static def_constructor(ogg_grid_element, args)
    {
        this->object = 0;
    }

    static def_destructor(ogg_grid_element)
    {   /* do nothing */
    }

    /* GRID */

    handler(ogg_grid, OGG_PAINT_EVENT);

    static void destroy_grid(ogg_grid* this);

    static void set_grid_size_helper(ogg_grid* this, ogg_coord size);

    def_vtable(ogg_grid) (
        [OGG_PAINT_EVENT] = ogg_handler(ogg_grid, OGG_PAINT_EVENT)
    );

    default_startup(ogg_grid) (
        .size = { 1, 1 }
    )

    def_constructor(ogg_grid, args)
    {
        set_grid_size_helper(this, args->size);
    }

    def_destructor(ogg_grid)
    {
        destroy_grid(this);
    }

    def_handler(ogg_grid, OGG_PAINT_EVENT)
    {
        //glClear(GL_COLOR_BUFFER_BIT);
    }

    static void destroy_grid(ogg_grid* this)
    {
        unsigned i = 0;
        for (; i != this->size.y; ++i) {
            free(this->sub[i]);
# ifdef DEBUG
            alloc_memory--;
# endif
        }
        free(this->sub);
# ifdef DEBUG
        alloc_memory--;
# endif
    }

    static void set_grid_size_helper(ogg_grid* this, ogg_coord size)
    {
        ogg_coord pos = { 0, 0 };
        this->size.x = size.x;
        this->size.y = size.y;
        this->sub = (ogg_grid_element***)malloc(size.y * sizeof(ogg_grid_element**));
# ifdef DEBUG
        alloc_memory++;
# endif
        for (pos.y = 0; pos.y != size.y; ++pos.y) {
            this->sub[pos.y] = (ogg_grid_element**)calloc(size.x, sizeof(ogg_grid_element*));
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
                    .parent = (ogg_component*)this
                }
                )(this->sub[pos.y][pos.x]);
            }
        }
    }

    void set_grid_size(ogg_grid* this, ogg_coord size)
    {
        ogg_coord pos = { 0, 0 };
        for (pos.y = 0; pos.y != this->size.y; ++pos.y) {
            for (pos.x = 0; pos.x != this->size.x; ++pos.x) {
                ogg_destroy(get_grid_coord(this, pos));
            }
        }
        destroy_grid(this);
        set_grid_size_helper(this, size);
        ogg_send_event(this, OGG_PAINT_EVENT);
    }

    ogg_com_ptr get_grid_elem(ogg_grid* this, ogg_coord pos)
    {
        return this->sub[pos.y][pos.x]->object;
    }

    ogg_bool paint_grid_elem(ogg_grid* this, ogg_coord pos)
    {
        if (pos.x >= this->size.x || pos.y >= this->size.y) {
            return ogg_false;
        }
        ogg_send_event(this->sub[pos.y][pos.x], OGG_PAINT_EVENT);
        glFlush();
        return ogg_true;
    }

    ogg_com_ptr get_grid_coord(ogg_grid* this, ogg_coord pos)
    {
        return this->sub[pos.y][pos.x];
    }
