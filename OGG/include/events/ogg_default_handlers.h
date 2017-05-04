#ifndef OGG_GRAPHIC_DEFAULT_EVENTS__HEADER_FILE____
#define OGG_GRAPHIC_DEFAULT_EVENTS__HEADER_FILE____

# define ogg_default_handler(EVENT) ogg_default_##EVENT##_handler

static ogg_bool is_child_of(ogg_com_ptr child, ogg_com_ptr parent)
{
    ogg_component* ptr = child;
    while (ptr != parent && ptr) {
        ptr = ptr->parent;
    }
    return ptr != 0;
}

static void ogg_default_handler(OGG_PAINT_EVENT)(void)
{
    ogg_clear_screen(ogg_active_form()->color);
    ogg_send_event(ogg_active_form(), OGG_PAINT_EVENT);
    ogg_flush_screen();
}

static void ogg_default_handler(OGG_KEYBOARD_EVENT)(unsigned char key, int x, int y)
{
    ogg_send_event(ogg_active_form(), OGG_KEYBOARD_EVENT, key, x, y);
}

static void ogg_default_handler(OGG_SPECIAL_KEY_EVENT)(int key, int x, int y)
{
    ogg_send_event(ogg_active_form(), OGG_SPECIAL_KEY_EVENT, key, x, y);
}

static void ogg_default_handler(OGG_MOUSE_EVENT)(int button, int state, int x, int y)
{
    application->is_top_level = ogg_true;
    ogg_send_event(ogg_active_form(), OGG_MOUSE_EVENT, button, state, x, y);
}

static void ogg_default_handler(OGG_MOUSE_DRAG_EVENT)(int x, int y)
{
    application->is_top_level = ogg_true;
    ogg_send_event(ogg_active_form(), OGG_MOUSE_DRAG_EVENT, 
        x - application->last_drag_pc.x, y - application->last_drag_pc.y);
}

static void ogg_default_handler(OGG_MOUSE_MOVE_EVENT)(int x, int y)
{
    application->is_top_level = ogg_true;
    ogg_send_event(ogg_active_form(), OGG_MOUSE_MOVE_EVENT, x, y);
}

static void ogg_default_handler(OGG_MOUSE_ENTRY_EVENT)(int state)
{
    application->is_top_level = ogg_true;
    ogg_send_event(ogg_active_form(), OGG_MOUSE_ENTRY_EVENT, state);
}

static void ogg_default_handler(OGG_TIMER_EVENT)(int value)
{
    ogg_send_event(ogg_active_form(), OGG_TIMER_EVENT);
    glutTimerFunc(OGG_TIME_INTERVAL, ogg_default_handler(OGG_TIMER_EVENT), value);
}

static void ogg_default_handler(OGG_RESHAPE_EVENT)(int width, int height)
{
    ogg_get_active_form()->position.width = width;
    ogg_get_active_form()->position.height = height;
    glViewport(0, 0, width, height);
    ogg_send_event(ogg_active_form(), OGG_RESHAPE_EVENT, width, height);
}

static def_checker(OGG_DESTROY_EVENT)
{
    if (application->focused_component == self) {
        application->focused_component = 0;
    }
    if (application->current_component == self) {
        ogg_send_event(application->current_component, OGG_LOSE_FOCUS_EVENT);
        application->current_component = ogg_active_form();
    }
    return ogg_true;
}

static def_checker(OGG_KEYBOARD_EVENT)
{
    return is_child_of(application->current_component, self);
}

static def_checker(OGG_SPECIAL_KEY_EVENT)
{
    return is_child_of(application->current_component, self);
}

static def_checker(OGG_MOUSE_EVENT)
{
    ogg_anchor anchor;
    get_component_real_coord_anchor(self, &anchor);
    if (x >= anchor.coord.left && x <= anchor.coord.right &&
            y >= anchor.coord.top && y <= anchor.coord.bottom)
    {
        if (application->is_top_level) {
            application->is_top_level = ogg_false;
            if (application->current_component != self) {
                if (application->current_component != 0)
                    ogg_send_event(application->current_component, OGG_LOSE_FOCUS_EVENT);
                application->current_component = self;
                ogg_send_event(self, OGG_FOCUS_EVENT);
            }
            if (application->focused_component != self) {
                if (application->focused_component)
                    ogg_send_event(application->focused_component, OGG_MOUSE_LEAVE_EVENT);
                application->focused_component = self;
                ogg_send_event(self, OGG_MOUSE_ENTER_EVENT);
            }
            if (application->mouse_state != state) {
                application->mouse_state = state;
                ogg_send_event(self, state == GLUT_DOWN ?
                    OGG_MOUSE_DOWN_EVENT : OGG_MOUSE_UP_EVENT,
                    button, x, y
                );
            }
        }
        return state == GLUT_UP;
    }
    return ogg_false;
}

static def_checker(OGG_MOUSE_DRAG_EVENT)
{
    ogg_anchor anchor;
    get_component_real_coord_anchor(self, &anchor);
    int x = application->last_drag_pc.x + dx, y = application->last_drag_pc.y + dy;
    if (x >= anchor.coord.left && x <= anchor.coord.right &&
            y >= anchor.coord.top && y <= anchor.coord.bottom)
    {
        if (application->is_top_level) {
        application->is_top_level = ogg_false;
            if (application->focused_component != self) {
                if (application->focused_component)
                    ogg_send_event(application->focused_component, OGG_MOUSE_LEAVE_EVENT);
                application->focused_component = self;
                ogg_send_event(self, OGG_MOUSE_ENTER_EVENT);
            }
        }
        if (!application->is_dragging) {
            if (application->mouse_state == GLUT_DOWN) {
                application->is_dragging = ogg_true;
                application->last_drag_pc.x += x;
                application->last_drag_pc.y += y;
                ogg_send_event(self, OGG_MOUSE_DRAG_BEGIN_EVENT);
            }
        } else {
            if (application->mouse_state == GLUT_UP) {
                application->is_dragging = ogg_false;
                ogg_send_event(self, OGG_MOUSE_DRAG_END_EVENT);
                application->last_drag_pc.x = application->last_drag_pc.y = 0;
            }
        }
        return ogg_true;
    }
    else return ogg_false;
}

static def_checker(OGG_MOUSE_MOVE_EVENT)
{
    ogg_anchor anchor;
    get_component_real_coord_anchor(self, &anchor);
    if (x >= anchor.coord.left && x <= anchor.coord.right &&
            y >= anchor.coord.top && y <= anchor.coord.bottom)
    {
        if (application->is_top_level) {
            application->is_top_level = ogg_false;
            if (application->focused_component != self) {
                if (application->focused_component)
                    ogg_send_event(application->focused_component, OGG_MOUSE_LEAVE_EVENT);
                application->focused_component = self;
                ogg_send_event(self, OGG_MOUSE_ENTER_EVENT);
            }
        }
        return ogg_true;
    }
    return ogg_false;
}

static def_checker(OGG_MOUSE_ENTRY_EVENT)
{
    if (state == GL_LEFT) {
        if (application->focused_component) {
            ogg_send_event(application->focused_component, OGG_MOUSE_LEAVE_EVENT);
            application->focused_component = 0;
        }
        application->is_dragging = ogg_false;
    }
    return ogg_true;
}

static def_checker(OGG_TIMER_EVENT)
{
    return is_child_of(application->current_component, self);
}

ogg_bool (*const event_checker[OGG_EVENT_COUNT])(ogg_component*, va_list) = {
    [OGG_DESTROY_EVENT] = ogg_checker(OGG_DESTROY_EVENT),
    [OGG_PAINT_EVENT] = 0,
    [OGG_KEYBOARD_EVENT] = ogg_checker(OGG_KEYBOARD_EVENT),
    [OGG_SPECIAL_KEY_EVENT] = ogg_checker(OGG_SPECIAL_KEY_EVENT),
    [OGG_MOUSE_EVENT] = ogg_checker(OGG_MOUSE_EVENT),
    [OGG_MOUSE_DRAG_EVENT] = ogg_checker(OGG_MOUSE_DRAG_EVENT),
    [OGG_MOUSE_MOVE_EVENT] = ogg_checker(OGG_MOUSE_MOVE_EVENT),
    [OGG_MOUSE_ENTRY_EVENT] = ogg_checker(OGG_MOUSE_ENTRY_EVENT),
    [OGG_RESHAPE_EVENT] = 0,
    [OGG_MOUSE_LEAVE_EVENT] = 0,
    [OGG_MOUSE_ENTER_EVENT] = 0,
    [OGG_MOUSE_DOWN_EVENT] = 0,
    [OGG_MOUSE_UP_EVENT] = 0,
    [OGG_MOUSE_DRAG_BEGIN_EVENT] = 0,
    [OGG_MOUSE_DRAG_END_EVENT] = 0,
    [OGG_FOCUS_EVENT] = 0,
    [OGG_TIMER_EVENT] = ogg_checker(OGG_TIMER_EVENT),
    [OGG_LOSE_FOCUS_EVENT] = 0,
    [OGG_CREATE_SUB_COMPONENT_EVENT] = 0,
    [OGG_DESTROY_SUB_COMPONENT_EVENT] = 0,
    [OGG_ACCESS_EVENT] = 0,
    [OGG_CAN_ADD_CHILD] = 0,
};

#endif //OGG_GRAPHIC_DEFAULT_EVENTS__HEADER_FILE____
