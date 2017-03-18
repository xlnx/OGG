#include "graphic_component_shape.h"

# ifdef __cplusplus
extern "C"{
# endif

    static ogg_event_handler ogg_shape_vtable[] = {
        destroy_shape, // OGG_DESTROY_EVENT
        paint_shape    // OGG_PAINT_EVENT
    };

    ogg_shape* create_shape(const ogg_shape_info* st)
    {
        ogg_shape *shape = (ogg_shape*)malloc(sizeof(ogg_shape));
        ogg_component_info info = {
            .anchor = &st->startup.anchor,
            .parent = st->startup.parent,
            .vptr = ogg_shape_vtable
        };
        create_component(shape, &info);
        shape->vertex = st->vertex;
        return shape;
    }

    void destroy_shape(ogg_shape* shape)
    {
        free(shape->vertex->point);
        free(shape->vertex);
        free(shape);
    }

    void paint_shape(ogg_shape* shape)
    {
        glBegin(GL_POLYGON);
        unsigned i = 0;
        for (; i != shape->vertex->size; ++i) {
            coordf pix = get_real_coord(shape, shape->vertex->point[i]);
            glVertex2f(pix.x, pix.y);
        }
        glEnd();
        glFlush();
    }

    ogg_shape_vertex* vertex_list(unsigned n, ...)
    {
        va_list argp;
        va_start(argp, n);
        ogg_shape_vertex* vertex = (ogg_shape_vertex*)malloc(sizeof(ogg_shape_vertex));
        vertex->size = n;
        vertex->point = (coordf*)calloc(n, sizeof(coordf));
        int i = 0;
        for (; i != n; ++i) {
            memcpy(&vertex->point[i], &va_arg(argp, coordf), sizeof(coordf));
            vertex->point[i].x = vertex->point[i].x / 50 - 1;
            vertex->point[i].y = vertex->point[i].y / 50 - 1;
        }
        va_end(argp);
        return vertex;
    }

    coordf vertex(float x, float y)
    {
        coordf pos = { x, y };
        return pos;
    }

# ifdef __cplusplus
}
# endif
