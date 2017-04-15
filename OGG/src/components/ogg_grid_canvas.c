//#include <GL/glew.h>
#include <GL/glut.h>
#include "components/ogg_grid_canvas.h"

handler(ogg_grid_canvas, OGG_PAINT_EVENT);

def_vtable(ogg_grid_canvas)(
    [OGG_PAINT_EVENT] = ogg_handler(ogg_grid_canvas, OGG_PAINT_EVENT)
);

//default_startup(ogg_grid_canvas)(
//    .size = { 1, 1 }
//)

def_constructor(ogg_grid_canvas, args)
{
    self->size = args->size;
    if (self->size.x > 0 && self->size.y > 0) {
        self->sub = (ogg_paint_unit*)calloc(self->size.x * self->size.y, sizeof(ogg_paint_unit));
#  ifdef DEBUG
    alloc_memory++;
#  endif
    } else {
        self->sub = 0;
    }
}

def_destructor(ogg_grid_canvas)
{
    free(self->sub);
#  ifdef DEBUG
    alloc_memory--;
#  endif
}

def_handler(ogg_grid_canvas, OGG_PAINT_EVENT)
{
    register ogg_paint_unit* p = self->sub,* end = p + self->size.x * self->size.y;
    ogg_anchor anchor;
    get_component_real_pec_anchor(self, &anchor);
    ogg_pec pix = { anchor.pec.left, anchor.pec.top };
    float dx = (anchor.pec.right - anchor.pec.left) / self->size.x,
        dy = -(anchor.pec.top - anchor.pec.bottom) / self->size.y;
    register int xcnt = 0;
    const int max = self->size.x;
    glBegin(GL_QUADS);
    for (; ++xcnt, p != end; ++p) {
        switch (p->type) {
        case ogg_rect_unit: {
            glColor3f(p->rect.color.R, p->rect.color.G, p->rect.color.B);
            glVertex2f(pix.x, pix.y);
            glVertex2f(pix.x + dx, pix.y);
            glVertex2f(pix.x + dx, pix.y + dy);
            glVertex2f(pix.x, pix.y + dy);
        } break;
        case ogg_bitmap_unit:{
        } break;
        }
        pix.x += dx; //pix.y += dy;
        if (xcnt == max) {
            pix.y += dy;
            pix.x = anchor.pec.left;
            xcnt = 0;
        }
    }
    glEnd();
    /*
    ogg_paint_unit* p = self->sub,* end = p + self->size.x * self->size.y;
    ogg_anchor anchor;
    get_component_real_pec_anchor(self, &anchor);
    ogg_pec pix = { anchor.pec.left, anchor.pec.top };
    float dx = (anchor.pec.right - anchor.pec.left) / self->size.x,
        dy = -(anchor.pec.top - anchor.pec.bottom) / self->size.y;
    typedef struct {
        GLfloat x1, y1, x2, y2, x3, y3, x4, y4;
    } grid_rect;
    grid_rect *vec = (grid_rect*)malloc(self->size.x * self->size.y * sizeof(grid_rect));
    GLuint vbo_id;
    glGenBuffersARB(1, &vbo_id);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id);
    register int idx, i;
    for (idx = i = 0; ++idx, p != end; ++i, ++p) {
        switch (p->type) {
        case ogg_rect_unit: {
            vec[i].x1 = pix.x; vec[i].y1 = pix.y;
            vec[i].x2 = pix.x + dx; vec[i].y2 = pix.y;
            vec[i].x3 = pix.x + dx; vec[i].y3 = pix.y + dy;
            vec[i].x4 = pix.x; vec[i].y4 = pix.y + dy;
        } break;
        case ogg_bitmap_unit:{
        } break;
        }
        pix.x += dx; //pix.y += dy;
        if (idx == self->size.x) {
            pix.y += dy;
            pix.x = anchor.pec.left;
            idx = 0;
        }
    }
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, self->size.x * self->size.y * sizeof(grid_rect),
			vec, GL_STATIC_DRAW_ARB);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, 0);
    for (i = 0, p = self->sub; p != end; i += 4, ++p) {
        switch (p->type) {
        case ogg_rect_unit: {
            glColor3f(p->rect.color.R, p->rect.color.G, p->rect.color.B);
            glDrawArrays(GL_TRIANGLE_FAN, i, 4);
        } break;
        case ogg_bitmap_unit:{
        } break;
        }
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    free(vec);
    */
}

void resize_canvas(ogg_com_ptr canvas, ogg_coord size)
{
    ogg_grid_canvas* self = canvas;
    if (size.x != self->size.x || size.y != self->size.y) {
        if (self->sub) {
            free(self->sub);
    #  ifdef DEBUG
        alloc_memeory--;
    #  endif
        }
        self->size = size;
        self->sub = (ogg_paint_unit*)calloc(size.x * size.y, sizeof(ogg_paint_unit));
#  ifdef DEBUG
    alloc_memory++;
#  endif
    }
}

void set_canvas_color(ogg_com_ptr self, ogg_coord pos, ogg_color color)
{
    ogg_paint_unit* ptr = &((ogg_grid_canvas*)self)->sub[pos.x + pos.y * ((ogg_grid_canvas*)self)->size.x];
    ptr->type = ogg_rect_unit;
    ptr->rect.color = color;
}

void paint_grid_canvas_elem(ogg_com_ptr canvas, ogg_coord pos)
{
    ogg_grid_canvas* self = canvas;
    ogg_anchor anchor;
    get_component_real_pec_anchor(self, &anchor);
    float dx = (anchor.pec.right - anchor.pec.left) / self->size.x,
        dy = -(anchor.pec.top - anchor.pec.bottom) / self->size.y;
    ogg_pec pix = { anchor.pec.left + pos.x * dx, anchor.pec.top + pos.y * dy };
    ogg_paint_unit* p = self->sub + pos.y * self->size.x + pos.x;
    switch (p->type) {
    case ogg_rect_unit: {
        glColor3f(p->rect.color.R, p->rect.color.G, p->rect.color.B);
        glBegin(GL_QUADS);
        glVertex2f(pix.x, pix.y);
        glVertex2f(pix.x + dx, pix.y);
        glVertex2f(pix.x + dx, pix.y + dy);
        glVertex2f(pix.x, pix.y + dy);
        glEnd();
    } break;
    case ogg_bitmap_unit:{
    } break;
    }
    ogg_flush_screen();
}
