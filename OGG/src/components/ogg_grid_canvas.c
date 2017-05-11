//#include <GL/glew.h>
#include <stdio.h>
#include <GL/glut.h>
#include "components/ogg_grid_canvas.h"

handler(ogg_grid_canvas, OGG_PAINT_EVENT);

def_vtable(ogg_grid_canvas)(
    [OGG_PAINT_EVENT] = ogg_handler(ogg_grid_canvas, OGG_PAINT_EVENT)
);

//default_startup(ogg_grid_canvas)(
//    .size = { 1, 1 }
//)

def_constructor(ogg_grid_canvas, parent != 0)
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
    if (!self->size.x || !self->size.y) {
        return;
    }
    register ogg_paint_unit* p = self->sub,* end = p + self->size.x * self->size.y;
    ogg_anchor anchor;
    get_component_real_pec_anchor(self, &anchor);
    ogg_pec pix = { anchor.pec.left, anchor.pec.top };
    float dx = (anchor.pec.right - anchor.pec.left) / self->size.x,
        dy = -(anchor.pec.top - anchor.pec.bottom) / self->size.y;
    ogg_anchor anchor_c;
    get_component_real_coord_anchor(self, &anchor_c);
    int dx_c = (anchor_c.coord.right - anchor_c.coord.left) / self->size.x,
        dy_c = -(anchor_c.coord.top - anchor_c.coord.bottom) / self->size.y;
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
            glEnd();
            glRasterPos2f(pix.x, pec_sub_coord(pix, coord(0, dy_c)).y);
            glDrawPixels(p->bitmap.size.x, p->bitmap.size.y,
                GL_BGR_EXT, GL_UNSIGNED_BYTE, p->bitmap.data);
            glBegin(GL_QUADS);
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

void set_canvas_bitmap(ogg_com_ptr self, ogg_coord pos, ogg_bitmap data)
{
    ogg_paint_unit* ptr = &((ogg_grid_canvas*)self)->sub[pos.x + pos.y * ((ogg_grid_canvas*)self)->size.x];
    ptr->type = ogg_bitmap_unit;
    ptr->bitmap = data;
}

ogg_bitmap load_bitmap(const char *fname)
{
    ogg_bitmap result = { 0 };
    FILE *pfile = fopen(fname, "rb");
    if (pfile == 0) return result;

    int offset, flength;
    fseek(pfile, 0x000A, SEEK_SET);
    fread(&offset, sizeof(offset), 1, pfile);
    fseek(pfile, 0x0012, SEEK_SET);
    fread(&result.size.x, sizeof(result.size.x), 1, pfile);
    fread(&result.size.y, sizeof(result.size.y), 1, pfile);
    fseek(pfile, 0x001C, SEEK_SET);
    unsigned char bit_count;
    fread(&bit_count, sizeof(unsigned char), 1, pfile);
    fseek(pfile, 0x0022, SEEK_SET);
    fread(&flength, sizeof(flength), 1, pfile);

    switch(bit_count) {
    case 1: {
    } break;
    case 4: {
        unsigned int *table = (unsigned int *)malloc((1 << 4) * sizeof(unsigned int));
        fseek(pfile, 0x0036, SEEK_SET);
        fread(table, 4, 1 << 4, pfile);
        result.data = (GLubyte*)malloc(flength * 6);
        GLubyte *buffer = (GLubyte*)malloc(flength);
        fseek(pfile, offset, SEEK_SET);
        fread(buffer, flength, 1, pfile);
        register int i;
        for (i = 0; i != flength; ++i) {
            memcpy((GLubyte *)result.data + 6 * i + 3, table + ((unsigned int)buffer[i] & 0xF), 3);
            memcpy((GLubyte *)result.data + 6 * i, table + (((unsigned int)buffer[i] & 0xF0) >> 4), 3);
        }
        free(buffer);
        free(table);
    } break;
    case 8: {
        unsigned int *table = (unsigned int *)malloc((1 << 8) * sizeof(unsigned int));
        fseek(pfile, 0x0036, SEEK_SET);
        fread(table, 4, 1 << 8, pfile);
        result.data = (GLubyte*)malloc(flength * 3);
        GLubyte *buffer = (GLubyte*)malloc(flength);
        fseek(pfile, offset, SEEK_SET);
        fread(buffer, flength, 1, pfile);
        register int i;
        for (i = 0; i != flength; ++i) {
            memcpy((GLubyte *)result.data + 3 * i, table + (unsigned int)buffer[i], 3);
        }
        free(buffer);
        free(table);
    } break;
    case 24: {
        result.data = (GLubyte*)malloc(flength);
        fseek(pfile, offset, SEEK_SET);
        fread(result.data, flength, 1, pfile);
    } break;
    case 32: {
    } break;
    default: {
    }
    }
    fclose(pfile);
    return result;
}

void paint_grid_canvas_elem(ogg_com_ptr canvas, ogg_coord pos)
{
    ogg_grid_canvas* self = canvas;
    if (!self->size.x || !self->size.y) {
        return;
    }
    ogg_anchor anchor;
    get_component_real_pec_anchor(self, &anchor);
    float dx = (anchor.pec.right - anchor.pec.left) / self->size.x,
        dy = -(anchor.pec.top - anchor.pec.bottom) / self->size.y;
    ogg_pec pix = { anchor.pec.left + pos.x * dx, anchor.pec.top + pos.y * dy };
    ogg_anchor anchor_c;
    get_component_real_coord_anchor(self, &anchor_c);
    int dx_c = (anchor_c.coord.right - anchor_c.coord.left) / self->size.x,
        dy_c = -(anchor_c.coord.top - anchor_c.coord.bottom) / self->size.y;
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
        glEnd();
        glRasterPos2f(pix.x, pec_sub_coord(pix, coord(0, dy_c)).y);
        glDrawPixels(p->bitmap.size.x, p->bitmap.size.y,
            GL_BGR_EXT, GL_UNSIGNED_BYTE, p->bitmap.data);
        glBegin(GL_QUADS);
    } break;
    }
    ogg_flush_screen();
}
