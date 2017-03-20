#include "graphic_component_shape.h"

    void destroy_shape(ogg_shape* shape);

    void paint_shape(ogg_shape* shape);

    def_vtable(ogg_shape) (
        destroy_shape, // OGG_DESTROY_EVENT
        paint_shape    // OGG_PAINT_EVENT
    );

    def_constructor(ogg_shape, args)
    {
        this->vertex = args->vertex;
    }

    def_vtable(ogg_rect) (
        destroy_shape, // OGG_DESTROY_EVENT
        paint_shape    // OGG_PAINT_EVENT
    );

    def_constructor(ogg_rect, args)
    {
        this->super.vertex = vertex_list(4,
            vertex(0, 0),
            vertex(0, 100),
            vertex(100, 100),
            vertex(100, 0)
        );
    }

    void destroy_shape(ogg_shape* shape)
    {
        free(shape->vertex->point);
# ifdef DEBUG
        alloc_memory--;
# endif
        free(shape->vertex);
# ifdef DEBUG
        alloc_memory--;
# endif
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
# ifdef DEBUG
        alloc_memory++;
# endif
        vertex->size = n;
        vertex->point = (coordf*)calloc(n, sizeof(coordf));
# ifdef DEBUG
        alloc_memory++;
# endif
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
