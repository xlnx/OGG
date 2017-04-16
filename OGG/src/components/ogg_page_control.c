#include <GL/glut.h>
#include "components/ogg_page_control.h"

handler(ogg_page_control, OGG_PAINT_EVENT);
handler(ogg_page_control, OGG_CREATE_SUB_COMPONENT_EVENT);
handler(ogg_page_control, OGG_DESTROY_SUB_COMPONENT_EVENT);
handler(ogg_page_control, OGG_CAN_ADD_CHILD);

def_vtable(ogg_page_control)(
    using_handler(ogg_page_control, OGG_PAINT_EVENT),
    using_handler(ogg_page_control, OGG_CREATE_SUB_COMPONENT_EVENT),
    using_handler(ogg_page_control, OGG_DESTROY_SUB_COMPONENT_EVENT),
    using_handler(ogg_page_control, OGG_CAN_ADD_CHILD),
);

handler(ogg_tab_page, OGG_ACCESS_EVENT);
handler(ogg_tab_page, OGG_PAINT_EVENT);

def_vtable(ogg_tab_page)(
    using_handler(ogg_tab_page, OGG_PAINT_EVENT),
    using_handler(ogg_tab_page, OGG_ACCESS_EVENT),
);

def_constructor(ogg_page_control, parent != 0)
{
    self->page_count = 0;
    self->est_page_size = 2;
    self->active_page = -1;
    self->sub_pages = calloc(self->est_page_size, sizeof(ogg_com_ptr));
}

def_destructor(ogg_page_control)
{
    free(self->sub_pages);
}

def_handler(ogg_page_control, OGG_PAINT_EVENT)
{
    int i = 0;
    inherited(ogg_page_control, OGG_PAINT_EVENT);
    ogg_pec pec = { -1, 1 }, pet = { -1, 0.9f } , diff = { 0.4f, 0 };
    pec = get_real_pec(self, pec); 
    pet = pec_sub_coord(get_real_pec(self, pet), coord(-8, 4));
    ogg_pec det[] = {
        { 0, 0 }, { 0.4f, 0 }, { 0.4f, -0.2f }, { 0, -0.2f }
    };
    for (; i != self->page_count; ++i) {
        if (i == self->active_page) {
            ogg_color color = ((ogg_shape*)self->sub_pages[i])->color;
            glColor3f(color.R, color.G, color.B);
        } else {
            ogg_color color = ((ogg_shape*)self)->color;
            glColor3f(color.R, color.G, color.B);
        }
        glBegin(GL_QUADS);
        int j = 0;
        for (; j != 4; ++j) {
            ogg_pec pix = pec_add_pec(pec, det[j]);
            glVertex2f(pix.x, pix.y);
        }
        glEnd();
        ogg_paint_string(((ogg_tab_page*)self->sub_pages[i])->title, OGG_RED, pet);
        pec = pec_add_pec(pec, diff); pet = pec_add_pec(pet, diff);
    }
}

def_handler(ogg_page_control, OGG_CREATE_SUB_COMPONENT_EVENT)
{
    if (self->page_count == self->est_page_size) {
        ogg_com_ptr* mem = calloc(self->est_page_size *= 2, sizeof(ogg_com_ptr));
        memcpy(mem, self->sub_pages, sizeof(ogg_com_ptr) * self->page_count);
        free(self->sub_pages);
        self->sub_pages = mem;
    }
    if (!~self->active_page) {
        self->active_page = self->page_count;
    }
    self->sub_pages[self->page_count++] = sub;
    ogg_anchor anchor = {
        .type = ogg_anchor_pec,
        .pec = {
            .top_left = {
                0, 10
            },
            .bottom_right = {
                100, 100
            }
        }
    };
    set_component_anchor(sub, &anchor);
}

def_handler(ogg_page_control, OGG_DESTROY_SUB_COMPONENT_EVENT)
{
    int i = 0;
    for (; i != self->page_count; ++i) {
        if (self->sub_pages[i] == sub) {
            if (i <= self->active_page) {
                self->active_page--;
            }
            for (++i; i != self->page_count; ++i) {
                self->sub_pages[i - 1] = self->sub_pages[i];
            }
            self->page_count--; break;
        }
    }
}

def_handler(ogg_page_control, OGG_CAN_ADD_CHILD)
{
    *accept = vptr == ogg_tab_page_vtable;
}


def_constructor(ogg_tab_page, ((ogg_component*)parent)->vptr == ogg_page_control_vtable)
{
    self->title = args->title;
}

def_destructor(ogg_tab_page)
{
}

def_handler(ogg_tab_page, OGG_PAINT_EVENT)
{
    inherited(ogg_tab_page, OGG_PAINT_EVENT);
}

def_handler(ogg_tab_page, OGG_ACCESS_EVENT)
{
    ogg_page_control* p = (ogg_page_control*)(((ogg_component*)self)->parent);
    *access = self == p->sub_pages[p->page_count];
}
