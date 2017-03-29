#include <GL/glut.h>
#include "components/ogg_shape.h"

    handler(ogg_shape, OGG_PAINT_EVENT);

    def_vtable(ogg_shape) (
        [OGG_PAINT_EVENT] = ogg_handler(ogg_shape, OGG_PAINT_EVENT)
    );

    default_startup(ogg_shape)(
        .color = OGG_BLUE,
        .vertex = 0
    )

    def_constructor(ogg_shape, args)
    {
        this->color = args->color;
        this->vertex = args->vertex;
    }

    def_destructor(ogg_shape)
    {
        free(this->vertex->point);
# ifdef DEBUG
        alloc_memory--;
# endif
        free(this->vertex);
# ifdef DEBUG
        alloc_memory--;
# endif
    }

    def_handler(ogg_shape, OGG_PAINT_EVENT)
    {
        glColor3f(this->color.R, this->color.G, this->color.B);
        glBegin(GL_POLYGON);
        unsigned i = 0;
        for (; i != this->vertex->size; ++i) {
            coordf pix = get_real_pec(this, this->vertex->point[i]);
            glVertex2f(pix.x, pix.y);
        }
        glEnd();
    }

    void set_shape_color(ogg_com_ptr this, ogg_color color)
    {
        ((ogg_shape*)this)->color = color;
        ogg_send_event(this, OGG_PAINT_EVENT);
    }


    def_vtable(ogg_rect) (
        [OGG_PAINT_EVENT] = ogg_handler(ogg_shape, OGG_PAINT_EVENT)
    );

    default_startup_inh(ogg_rect, ogg_shape)(
    )

    def_constructor(ogg_rect, args)
    {
        if (this->super.vertex) {
            free(this->super.vertex->point);
# ifdef DEBUG
            alloc_memory--;
# endif
            free(this->super.vertex);
# ifdef DEBUG
            alloc_memory--;
# endif
        }
        this->super.vertex = vertex_list(4,
            vertex(0, 0),
            vertex(0, 100),
            vertex(100, 100),
            vertex(100, 0)
        );
    }

    def_destructor(ogg_rect)
    {   /* don't need to do anything */
    }

