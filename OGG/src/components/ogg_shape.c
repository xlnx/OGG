#include <GL/glut.h>
#include "components/ogg_shape.h"

    handler(ogg_shape, OGG_PAINT_EVENT);

    def_vtable(ogg_shape) (
        [OGG_PAINT_EVENT] = ogg_handler(ogg_shape, OGG_PAINT_EVENT)
    );

    //default_startup(ogg_shape)(
    //    .color = OGG_BLUE,
    //    .vertex = 0
    //)

    def_constructor(ogg_shape, parent != 0)
    {
        self->color = args->color;
        self->vertex = args->vertex;
    }

    def_destructor(ogg_shape)
    {
        free(self->vertex->point);
# ifdef DEBUG
        alloc_memory--;
# endif
        free(self->vertex);
# ifdef DEBUG
        alloc_memory--;
# endif
    }

    def_handler(ogg_shape, OGG_PAINT_EVENT)
    {
        glColor3f(self->color.R, self->color.G, self->color.B);
        glBegin(GL_POLYGON);
        unsigned i = 0;
        for (; i != self->vertex->size; ++i) {
            coordf pix = get_real_pec(self, self->vertex->point[i]);
            glVertex2f(pix.x, pix.y);
        }
        glEnd();
    }

    void set_shape_color(ogg_com_ptr self, ogg_color color)
    {
        ((ogg_shape*)self)->color = color;
        ogg_send_event(self, OGG_PAINT_EVENT);
    }


    def_vtable(ogg_rect) (
        [OGG_PAINT_EVENT] = ogg_handler(ogg_shape, OGG_PAINT_EVENT)
    );

    /*default_startup_inh(ogg_rect, ogg_shape)(
    )*/

    def_constructor(ogg_rect, parent != 0)
    {
        if (self->super.vertex) {
            free(self->super.vertex->point);
# ifdef DEBUG
            alloc_memory--;
# endif
            free(self->super.vertex);
# ifdef DEBUG
            alloc_memory--;
# endif
        }
        self->super.vertex = vertex_list(4,
            vertex(0, 0),
            vertex(0, 100),
            vertex(100, 100),
            vertex(100, 0)
        );
    }

    def_destructor(ogg_rect)
    {   /* don't need to do anything */
    }

