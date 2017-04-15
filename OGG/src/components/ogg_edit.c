#include <GL/glut.h>
#include "components/ogg_edit.h"

extern handler(ogg_shape, OGG_PAINT_EVENT);

handler(ogg_edit, OGG_PAINT_EVENT);

handler(ogg_edit, OGG_KEYBOARD_EVENT);

handler(ogg_edit, OGG_SPECIAL_KEY_EVENT);

handler(ogg_edit, OGG_TIMER_EVENT);

handler(ogg_edit, OGG_LOSE_FOCUS_EVENT);

handler(ogg_edit, OGG_RESHAPE_EVENT);

def_vtable(ogg_edit)(
    [OGG_PAINT_EVENT] = ogg_handler(ogg_edit, OGG_PAINT_EVENT),
    [OGG_KEYBOARD_EVENT] = ogg_handler(ogg_edit, OGG_KEYBOARD_EVENT),
    [OGG_SPECIAL_KEY_EVENT] = ogg_handler(ogg_edit, OGG_SPECIAL_KEY_EVENT),
    [OGG_TIMER_EVENT] = ogg_handler(ogg_edit, OGG_TIMER_EVENT),
    [OGG_LOSE_FOCUS_EVENT] = ogg_handler(ogg_edit, OGG_LOSE_FOCUS_EVENT),
    [OGG_RESHAPE_EVENT] = ogg_handler(ogg_edit, OGG_RESHAPE_EVENT),
);

//default_startup_inh(ogg_edit, ogg_rect)(
//    .color = OGG_WHITE
//)

def_constructor(ogg_edit, args)
{
    memset(&self->text.content, 0, sizeof(self->text.content));
    self->text.color = args->color;
    ((ogg_shape*)self)->color = OGG_WHITE;
    self->caret = self->offset = 0;
    self->caret_visible = ogg_false;
    self->insert_mode = ogg_true;
}

def_destructor(ogg_edit)
{   /* do nothing */
}

extern int window_width;
extern int window_height;

static int get_edit_width(ogg_edit* self)
{
    ogg_anchor anchor;
    get_component_real_coord_anchor(self, &anchor);
    return (anchor.coord.right - anchor.coord.left) / 8 - 1;
}

static void adjust_offset(ogg_edit* self)
{
    const int width = get_edit_width(self),
            length = strlen(self->text.content);
    if (self->caret >= width + self->offset) {
        self->offset = self->caret - width + 1;
    } else if (self->caret < self->offset) {
        self->offset = self->caret;
    } else if (length < self->offset + width - 1) {
        self->offset = max(0, length - width + 1);
    }
}

static void paint_caret(ogg_edit* self)
{
    if (self->caret_visible) {
        glColor3f(self->text.color.R, self->text.color.G, self->text.color.B);
    } else {
        glColor3f(OGG_WHITE.R, OGG_WHITE.G, OGG_WHITE.B);
    }
    ogg_pec pec = { -1, 0 };
    int cur_pos = self->caret - self->offset;
    ogg_pec pix = pec_add_coord(get_real_pec(self, pec),
        coord(4 + cur_pos * 8, -8));
    float dx = self->insert_mode ?
        (float)(0.5 * 4 / window_width)
        :
        (float)(4.0 * 4 / window_width),
        dy = (float)(8.0 * 4 / window_height);
    glBegin(GL_QUADS);
    glVertex2f(pix.x, pix.y);
    glVertex2f(pix.x + dx, pix.y);
    glVertex2f(pix.x + dx, pix.y + dy);
    glVertex2f(pix.x, pix.y + dy);
    glEnd();
    if (!self->caret_visible) {
        ogg_paint_char(self->text.content[self->caret], self->text.color,
            pec_add_coord(pix, coord(0, 4)));
    }
    ogg_flush_screen();
}

def_handler(ogg_edit, OGG_PAINT_EVENT)
{
    ogg_handler(ogg_shape, OGG_PAINT_EVENT)((ogg_shape*)self, 0, handled);
    coordf pix = { -1, 0 };
    pix = pec_add_coord(get_real_pec(self, pix), coord(4, -4));
    int width = get_edit_width(self);
    ogg_paint_string_len(self->text.content + self->offset, width, self->text.color, pix);
    paint_caret(self);
}

def_handler(ogg_edit, OGG_KEYBOARD_EVENT)
{
    if ((key < 32 && key != '\b')|| key > 127) {
        return;
    }
    switch (key) {
    case '\b': if (self->caret != 0){
        int ptr = self->caret--, length = strlen(self->text.content);
        for (; ptr != length + 1; ++ptr) {
            self->text.content[ptr - 1] = self->text.content[ptr];
        }
    } break;
    case 127: {
        if ((glutGetModifiers() & GLUT_ACTIVE_CTRL) && self->caret != 0) {
            int ptr = self->caret, det = 1, length = strlen(self->text.content);
            for (; det != self->caret; ++det) {
                if (self->text.content[self->caret - det] == ' ')
                    break;
            }
            self->caret -= det;
            for (; ptr != length + det; ++ptr) {
                self->text.content[ptr - det] = self->text.content[ptr];
            }
        } else {
            int ptr = self->caret;
            for (; self->text.content[ptr]; ++ptr) {
                self->text.content[ptr] = self->text.content[ptr + 1];
            }
        }
    } break;
    default: {
        if (self->insert_mode) {
            int ptr = strlen(self->text.content);
            for (; ptr != self->caret; --ptr) {
                self->text.content[ptr] = self->text.content[ptr - 1];
            }
            self->text.content[self->caret++] = key;
        } else {
            self->text.content[self->caret++] = key;
        }
    } break;
    }
    *handled = ogg_true;
    adjust_offset(self);
    ogg_send_event(self, OGG_PAINT_EVENT);
    ogg_flush_screen();
}

def_handler(ogg_edit, OGG_TIMER_EVENT)
{
    self->caret_visible = !self->caret_visible;
    paint_caret(self);
}

def_handler(ogg_edit, OGG_SPECIAL_KEY_EVENT)
{
    switch (key) {
    case GLUT_KEY_LEFT: if (self->caret > 0) {
        --self->caret;
    } break;
    case GLUT_KEY_RIGHT: if (self->text.content[self->caret]){
        ++self->caret;
    } break;
    case GLUT_KEY_INSERT: {
        self->insert_mode = !self->insert_mode;
    } break;
    case GLUT_KEY_HOME: {
        self->caret = 0;
    } break;
    case GLUT_KEY_END: {
        self->caret = strlen(self->text.content);
    } break;
    default: return;
    }
    *handled = ogg_true;
    self->caret_visible = ogg_true;
    adjust_offset(self);
    ogg_send_event(self, OGG_PAINT_EVENT);
    ogg_flush_screen();
}

def_handler(ogg_edit, OGG_LOSE_FOCUS_EVENT)
{
    self->caret_visible = ogg_false;
    paint_caret(self);
}

def_handler(ogg_edit, OGG_RESHAPE_EVENT)
{
    adjust_offset(self);
    ogg_send_event(self, OGG_PAINT_EVENT, 0);
    ogg_flush_screen();
}

char* ogg_edit_get_text(ogg_edit* edit)
{
    return edit->text.content;
}
