#include <GL/glut.h>
#include "utils/ogg_utils.h"
#include <gl/freeglut.h>

# ifndef INST__GEOMETRY_SYSTEM__FLOAT__F___
#  define INST__GEOMETRY_SYSTEM__FLOAT__F___
inst_geometry_system(float, f);
# endif

# ifndef INST__GEOMETRY_SYSTEM__INT__I___
#  define INST__GEOMETRY_SYSTEM__INT__I___
inst_geometry_system(int, i)
# endif

void ogg_clear_screen(ogg_color color)
{
    glClearColor(color.R, color.G, color.B, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ogg_flush_screen(void)
{
    glFlush();//glutSwapBuffers();
}

void ogg_paint_char(char chr, ogg_color color, coordf pix)
{
    glColor3f(color.R, color.G, color.B);
    glRasterPos2f(pix.x, pix.y);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, chr);
}

void ogg_paint_string(const char* p, ogg_color color, coordf pix)
{
    glColor3f(color.R, color.G, color.B);
    glRasterPos2f(pix.x, pix.y);
    for (; *p != 0; ++p)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
}

void ogg_paint_string_len(const char* p, int len, ogg_color color, coordf pix)
{
    glColor3f(color.R, color.G, color.B);
    glRasterPos2f(pix.x, pix.y);
    const char* end = p + len;
    for (; *p != 0 && p != end; ++p)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
}

ogg_color ogg_make_color(int R, int G, int B)
{
    ogg_color color = { (float)R / 255, (float)G / 255, (float)B / 255 };
    return color;
}

ogg_vertex* vertex_list(unsigned n, ...)
{
    va_list argp;
    va_start(argp, n);
    ogg_vertex* vertex = (ogg_vertex*)malloc(sizeof(ogg_vertex));
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
        vertex->point[i] = va_arg(argp, coordf);
        vertex->point[i].x = vertex->point[i].x / 50 - 1;
        vertex->point[i].y = 1 - vertex->point[i].y / 50;
    }
    va_end(argp);
    return vertex;
}

coordf vertex(float x, float y)
{
    coordf pos = { x, y };
    return pos;
}
