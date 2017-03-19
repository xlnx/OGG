#include "graphic_component_shape.h"

    void destroy_shape(ogg_shape* shape);

    void paint_shape(ogg_shape* shape);

    static ogg_event_handler ogg_shape_vtable[OGG_EVENT_COUNT] = {
        destroy_shape, // OGG_DESTROY_EVENT
        paint_shape    // OGG_PAINT_EVENT
    };

    void create_shape_dest(ogg_shape* shape, const ogg_shape_info* st)
    {
        ogg_component_info info = {
            .anchor = &st->startup.anchor,
            .parent = st->startup.parent,
            .vptr = ogg_shape_vtable
        };
        create_component(shape, &info);
        shape->vertex = st->vertex;
    }

    ogg_shape* create_shape(const ogg_shape_info* st)
    {
        ogg_shape *shape = (ogg_shape*)malloc(sizeof(ogg_shape));
# ifdef DEBUG
        alloc_memory++;
# endif
        create_shape_dest(shape, st);
        return shape;
    }

    void create_rect_dest(ogg_rect* rect, const ogg_rect_info* st)
    {
        ogg_component_info info = {
            .anchor = &st->startup.anchor,
            .parent = st->startup.parent,
            .vptr = ogg_shape_vtable
        };
        create_component(rect, &info);
        rect->super.vertex = vertex_list(4,
            vertex(0, 0),
            vertex(0, 100),
            vertex(100, 100),
            vertex(100, 0)
        );
    }

    ogg_rect* create_rect(const ogg_rect_info* st)
    {
        ogg_rect *rect = (ogg_rect*)malloc(sizeof(ogg_rect));
# ifdef DEBUG
        alloc_memory++;
# endif
        create_rect_dest(rect, st);
        return rect;
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
