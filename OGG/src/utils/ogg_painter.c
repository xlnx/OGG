#include "utils/ogg_painter.h"
#include <math.h>

ogg_painter_coord make_painter_coord(float x, float y, float r)
{
    ogg_painter_coord result = { x, y, r };
    return result;
}

void ogg_paint_texture_object(ogg_texture_object self, ogg_painter_coord p)
{
    float cosf = (float)cos(p.r), sinf = (float)sin(p.r);
    glBindTexture(GL_TEXTURE_2D, self->texture);
    glBegin(GL_QUADS);
    int i;
    for (i = 0; i != self->object.vertex_count; ++i)
    {
        glTexCoord2f(self->vertex[i].x, self->vertex[i].y);
        glVertex2f(
            p.x + self->object.vertex[i].x * cosf - self->object.vertex[i].y * sinf,
            p.y + self->object.vertex[i].x * sinf + self->object.vertex[i].y * cosf);
    }
    glEnd();
}

void ogg_rotate_object(ogg_object self, float r)
{
    int i; float cosf = (float)cos(r), sinf = (float)sin(r);
    for (i = 0; i != self->vertex_count; ++i)
    {
        float tmp = self->vertex[i].x * cosf - self->vertex[i].y * sinf;
        self->vertex[i].y = self->vertex[i].x * sinf + self->vertex[i].y * cosf;
        self->vertex[i].x = tmp;
    }
}

static ogg_bool is_intersect(pointf a1, pointf b1, pointf a2, pointf b2)
{
    return
        fabs(a1.x + b1.x - a2.x - b2.x) <= fabs(b1.x - a1.x) + fabs(b2.x - a2.x)
        &&
        fabs(a1.y + b1.y - a2.y - b2.y) <= fabs(b1.y - a1.y) + fabs(b2.y - a2.y)
        &&
        outer_productf(sub_pointf(a1, a2), sub_pointf(b2, a2)) *
            outer_productf(sub_pointf(b1, a2), sub_pointf(b2, a2)) <= 0
        &&
        outer_productf(sub_pointf(a2, a1), sub_pointf(b1, a1)) *
            outer_productf(sub_pointf(b2, a1), sub_pointf(b1, a1)) <= 0;
}

#define MAX_VERTEX_COUNT (2048)

ogg_bool ogg_object_overlap(ogg_object a, ogg_painter_coord p1, ogg_object b, ogg_painter_coord p2)
{
    static pointf va[MAX_VERTEX_COUNT], vb[MAX_VERTEX_COUNT];
    {
        memcpy(va, a->vertex, (a->vertex_count + 1) * sizeof(pointf));
        va[a->vertex_count] = va[0];
        int i; float cosf = (float)cos(p1.r), sinf = (float)sin(p1.r);
        for (i = 0; i != a->vertex_count + 1; ++i)
        {
            float tmp = p1.x + va[i].x * cosf - va[i].y * sinf;
            va[i].y = p1.y + va[i].x * sinf + va[i].y * cosf;
            va[i].x = tmp;
        }
    }
    {
        memcpy(vb, b->vertex, (b->vertex_count) * sizeof(pointf));
        int i; float cosf = (float)cos(p2.r), sinf = (float)sin(p2.r);
        for (i = 0; i != b->vertex_count; ++i)
        {
            float tmp = p2.x + vb[i].x * cosf - vb[i].y * sinf;
            vb[i].y = p2.y + vb[i].x * sinf + vb[i].y * cosf;
            vb[i].x = tmp;
        }
    }
    int i, j;
    for (i = 0; i != a->vertex_count; ++i)
    {
        pointf v = { -(va[i + 1].y - va[i].y), (va[i + 1].x - va[i].x) };       // foreach narritor v
        float min1 = inner_productf(va[0], v), max1 = min1;
        for (j = 1; j != a->vertex_count; ++j)      // figure out the projection of convexhull1 on v
        {
            float inner_p = inner_productf(va[j], v);
            max1 = max(inner_p, max1); min1 = min(inner_p, min1);
        }
        float min2 = inner_productf(vb[0], v), max2 = min2;
        for (j = 1; j != b->vertex_count; ++j)      // figure out the projection of convexhull2 on v
        {
            float inner_p = inner_productf(vb[j], v);
            max2 = max(inner_p, max2); min2 = min(inner_p, min2);
        }
        if (max1 < min2 || min1 > max2)         // if these two projection segments not overlap then the convexhull don't overlap
        {
            return ogg_false;
        }
    }
    return ogg_true;
}
