#include "ogg_components.h"

void ogg_static_constructor_ogg_component___(ogg_com_ptr com_ptr, const ogg_component_info* cominfo)
{
    set_component_anchor(com_ptr, &cominfo->anchor);
    ogg_component* com = (ogg_component*)com_ptr;
    com->parent = cominfo->parent;
    com->sub = com->subrear = (ogg_subcomponent*)calloc(1, sizeof(ogg_subcomponent));
# ifdef DEBUG
    alloc_memory++;
# endif
    if (com->parent != 0) {
        com->parent->subrear->next = (ogg_subcomponent*)calloc(1, sizeof(ogg_subcomponent));
# ifdef DEBUG
        alloc_memory++;
# endif
        com->parent->subrear = com->parent->subrear->next;
        com->parent->subrear->object = com_ptr;
    }
}

static void destroy_sub_components(ogg_com_ptr com_ptr)
{
    ogg_subcomponent* iter = ((ogg_component*)com_ptr)->sub->next;
    while (iter != 0) {
        ogg_subcomponent* p = iter->next;
        ogg_destroy(iter->object);
        iter = p;
    }
    free(((ogg_component*)com_ptr)->sub);
# ifdef DEBUG
    alloc_memory--;
# endif
}

coordf get_real_coord(ogg_com_ptr com_ptr, coordf pix)
{
    if (com_ptr) {
        ogg_anchor anchor;
        get_component_real_anchor(com_ptr, &anchor);
        switch (anchor.type) {
        case ogg_anchor_pec:
            pix.x = ((pix.x + 1) * anchor.pec.right - (pix.x - 1) * anchor.pec.left) / 2;
            pix.y = ((pix.y + 1) * anchor.pec.bottom - (pix.y - 1) * anchor.pec.top) / 2;
            break;
        case ogg_anchor_coord:;
        }
    }
    return pix;
}

void get_component_real_anchor(ogg_com_ptr com_ptr, ogg_anchor* anchor)
{
    ogg_component* com = (ogg_component*)com_ptr;
    if (com->parent == 0) {
        memcpy(&anchor->pec, &com->pec, sizeof(ogg_pec_anchor));
        anchor->type = com->anchor_type;
    }
    else {
        get_component_real_anchor(com->parent, anchor);
        switch (anchor->type){
        case ogg_anchor_pec: {
            float x1 = anchor->pec.left, x2 = anchor->pec.right,
                y1 = anchor->pec.top, y2 = anchor->pec.bottom;
            anchor->pec.left =
                ((com->pec.left + 1) * x2 - (com->pec.left - 1) * x1) / 2;
            anchor->pec.right = 
                ((com->pec.right + 1) * x2 - (com->pec.right - 1) * x1) / 2;
            anchor->pec.top = 
                ((com->pec.top + 1) * y2 - (com->pec.top - 1) * y1) / 2;
            anchor->pec.bottom = 
                ((com->pec.bottom + 1) * y2 - (com->pec.bottom - 1) * y1) / 2; break;
        }
        case ogg_anchor_coord:;
        }
    }
}

void set_component_anchor(ogg_com_ptr com_ptr, const ogg_anchor* anchor)
{
    ogg_component* com = (ogg_component*)com_ptr;
    switch (com->anchor_type = anchor->type) {
    case ogg_anchor_pec:
        com->pec.left = anchor->pec.left / 50 - 1;
        com->pec.top = anchor->pec.top / 50 - 1;
        com->pec.right = anchor->pec.right / 50 - 1;
        com->pec.bottom = anchor->pec.bottom / 50 - 1; break;
    case ogg_anchor_coord:;
    }
}

static void ogg_single_event(ogg_com_ptr com_ptr, event event_name, ogg_handle_flag *handled, va_list args)
{
    if (((ogg_component*)com_ptr)->vptr[event_name] != 0) {
        ((ogg_component*)com_ptr)->vptr[event_name](com_ptr, args, handled);
    }
}

static void ogg_parent_handle_event(ogg_com_ptr com_ptr, event event_name, ogg_handle_flag *handled, va_list args)
{
    ogg_single_event(com_ptr, event_name, handled, args);
    ogg_subcomponent* iter = ((ogg_component*)com_ptr)->sub->next;
    while (!*handled && iter != 0) {
        ogg_parent_handle_event(iter->object, event_name, handled, args);
        iter = iter->next;
    }
}

static void ogg_child_handle_event(ogg_com_ptr com_ptr, event event_name, ogg_handle_flag *handled, va_list args)
{
    ogg_subcomponent* iter = ((ogg_component*)com_ptr)->sub->next;
    while (!*handled && iter != 0) {
        ogg_child_handle_event(iter->object, event_name, handled, args);
        iter = iter->next;
    }
    if (!*handled) {
        ogg_single_event(com_ptr, event_name, handled, args);
    }
}

void ogg_send_event(ogg_com_ptr com_ptr, event event_name, ...)
{
    va_list args; va_start(args, event_name);
    ogg_handle_flag handled = OGG_UNHANDLED;
    switch (ogg_event_type[event_name]) {
    case OGG_CHILD_HANDLE_EVENT: ogg_child_handle_event(com_ptr, event_name, &handled, args); break;
    case OGG_PARENT_HANDLE_EVENT: ogg_parent_handle_event(com_ptr, event_name, &handled, args); break;
    }
    va_end(args);
}

void ogg_destroy(ogg_com_ptr com_ptr)
{
    destroy_sub_components(com_ptr);
    ogg_single_event(com_ptr, OGG_DESTROY_EVENT, 0, 0);
    ogg_component* parent = ((ogg_component*)com_ptr)->parent;
    if (parent != 0) {
        ogg_subcomponent* p = parent->sub;
        while (p->next != 0) {
            ogg_subcomponent* last = p; p = p->next;
            if (p->object == com_ptr) {
                if (p->next == 0) {
                    ((ogg_component*)com_ptr)->parent->subrear = last;
                }
                last->next = p->next;
                free(p);
# ifdef DEBUG
                alloc_memory--;
# endif
                break;
            }
        }
    }
    free(com_ptr);
# ifdef DEBUG
    alloc_memory--;
# endif
}

ogg_coord coord(int x, int y)
{
    ogg_coord pos = { x, y };
    return pos;
}

ogg_component_info make_startup(ogg_com_ptr parent)
{
    ogg_component_info st = {
        .anchor = {
            .type = ogg_anchor_pec,
            .pec = {
                .top = 0,
                .bottom = 100,
                .left = 0,
                .right = 100
            }
        },
        .parent = parent
    };
    return st;
}
