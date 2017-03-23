#include <GL/glut.h>
#include "components/ogg_components.h"

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

#  ifdef DEBUG
#    define destroy_sub_components(com_ptr)                                 \
    do {                                                                    \
        ogg_subcomponent* iter = ((ogg_component*)com_ptr)->sub->next;      \
        while (iter != 0) {                                                 \
            ogg_subcomponent* p = iter->next;                               \
            ogg_destroy(iter->object);                                      \
            iter = p;                                                       \
        }                                                                   \
        free(((ogg_component*)com_ptr)->sub);                               \
        alloc_memory--;                                                     \
    } while (0)
#  else
#    define destroy_sub_components(com_ptr)                                 \
    do {                                                                    \
        ogg_subcomponent* iter = ((ogg_component*)com_ptr)->sub->next;      \
        while (iter != 0) {                                                 \
            ogg_subcomponent* p = iter->next;                               \
            ogg_destroy(iter->object);                                      \
            iter = p;                                                       \
        }                                                                   \
        free(((ogg_component*)com_ptr)->sub);                               \
    } while (0)
#  endif

int window_width;
int window_height;

ogg_pec ogg_make_pec(float x, float y)
{
    ogg_pec pec = { x, y };
    return pec;
}

ogg_pec coord2pec(ogg_coord p)
{
    ogg_pec pix = { (float)p.x * 2 / window_width - 1,
        1 - (float)p.y * 2 / window_height };
    return pix;
}

ogg_coord pec2coord(ogg_pec p)
{
    ogg_coord pix = { (int)(window_width * (p.x + 1) / 2),
        (int)(window_height * (1 - p.y) / 2) };
    return pix;
}

ogg_pec pec_add_pec(ogg_pec a, ogg_pec b)
{
    a.x += b.x; a.y += b.y;
    return a;
}

ogg_pec pec_sub_pec(ogg_pec a, ogg_pec b)
{
    a.x -= b.x; a.y -= b.y;
    return a;
}

ogg_pec pec_add_coord(ogg_pec a, ogg_coord b)
{
    a.x += (float)b.x * 2 / window_width;
    a.y += (float)b.y * 2 / window_height;
    return a;
}

ogg_pec pec_sub_coord(ogg_pec a, ogg_coord b)
{
    a.x -= (float)b.x * 2 / window_width;
    a.y -= (float)b.y * 2 / window_height;
    return a;
}

ogg_pec get_real_pec(ogg_com_ptr com_ptr, ogg_pec pix)
{
    if (com_ptr) {
        ogg_anchor anchor;
        get_component_real_anchor(com_ptr, &anchor);
        switch (anchor.type) {
        case ogg_anchor_pec:
            pix.x = ((pix.x + 1) * anchor.pec.right - (pix.x - 1) * anchor.pec.left) / 2;
            pix.y = ((1 + pix.y) * anchor.pec.top + (1 - pix.y) * anchor.pec.bottom) / 2;
            break;
        case ogg_anchor_coord:
            pix.x = ((anchor.coord.right - anchor.coord.left) * (pix.x + 1) + 2 * anchor.coord.left) / window_width - 1;
            pix.y = 1 - ((anchor.coord.bottom - anchor.coord.top) * (1 - pix.y) + 2 * anchor.coord.top) / window_height;
        }
    }
    return pix;
}

void get_component_real_coord_anchor(ogg_com_ptr com_ptr, ogg_anchor* anchor)
{
    get_component_real_anchor(com_ptr, anchor);
    if (anchor->type == ogg_anchor_pec) {
        anchor->type = ogg_anchor_coord;
        float x1 = anchor->pec.left, x2 = anchor->pec.right,
            y1 = anchor->pec.top, y2 = anchor->pec.bottom;
        anchor->coord.left = (int)(window_width * (x1 + 1) / 2);
        anchor->coord.right = (int)(window_width * (x2 + 1) / 2);
        anchor->coord.top = (int)(window_height * (1 - y1) / 2);
        anchor->coord.bottom = (int)(window_height * (1 - y2) / 2);
    }
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
        /* anchor is the parent anchor */
        /* com is temporary anchor */
        switch (anchor->type){
        case ogg_anchor_pec:
            switch (com->anchor_type) {
            case ogg_anchor_pec: {              /* parent is pec and this is pec */
                float x1 = anchor->pec.left, x2 = anchor->pec.right,
                    y1 = anchor->pec.top, y2 = anchor->pec.bottom;
                anchor->pec.left =
                    ((com->pec.left + 1) * x2 - (com->pec.left - 1) * x1) / 2;
                anchor->pec.right = 
                    ((com->pec.right + 1) * x2 - (com->pec.right - 1) * x1) / 2;
                anchor->pec.top = 
                    ((1 + com->pec.top) * y1 + (1 - com->pec.top) * y2) / 2;
                    //((com->pec.top + 1) * y2 - (com->pec.top - 1) * y1) / 2;
                anchor->pec.bottom = 
                    //((com->pec.bottom + 1) * y2 - (com->pec.bottom - 1) * y1) / 2;
                    ((1 + com->pec.bottom) * y1 + (1 - com->pec.bottom) * y2) / 2;
            } break;
            case ogg_anchor_coord: {            /* parent is pec and this is coord */
                float x1 = anchor->pec.left, y1 = anchor->pec.top;
                anchor->coord.left = (int)(window_width * (x1 + 1) / 2 + com->coord.left);
                anchor->coord.right = (int)(window_width * (x1 + 1) / 2 + com->coord.right);
                anchor->coord.top = (int)(window_height * (1 - y1) / 2 + com->coord.top);
                anchor->coord.bottom = (int)(window_height * (1 - y1) / 2 + com->coord.bottom);
                anchor->type = ogg_anchor_coord;
            } break;
            } break;
        case ogg_anchor_coord:
            switch (com->anchor_type) {         /* parent is coord and this is pec */
            case ogg_anchor_pec: {
                int x1 = anchor->coord.left, x2 = anchor->coord.right,
                    y1 = anchor->coord.top, y2 = anchor->coord.bottom;
                anchor->coord.left += (int)((x2 - x1) * (com->pec.left + 1) / 2);
                anchor->coord.right += (int)((x2 - x1) * (com->pec.right + 1) / 2);
                anchor->coord.top += (int)((y2 - y1) * (1 - com->pec.top) / 2);
                anchor->coord.bottom += (int)((y2 - y1) * (1 - com->pec.bottom) / 2);
            } break;
            case ogg_anchor_coord: {            /* parent is coord and this is coord */
                anchor->coord.left += com->coord.left;
                anchor->coord.right += com->coord.right;
                anchor->coord.top += com->coord.top;
                anchor->coord.bottom += com->coord.bottom;
            } break;
            }
        }
    }
}

void set_component_anchor(ogg_com_ptr com_ptr, const ogg_anchor* anchor)
{
    ogg_component* com = (ogg_component*)com_ptr;
    switch (com->anchor_type = anchor->type) {
    case ogg_anchor_pec:
        com->anchor_type = ogg_anchor_pec;
        com->pec.left = anchor->pec.left / 50 - 1;
        com->pec.top = 1 - anchor->pec.top / 50;
        com->pec.right = anchor->pec.right / 50 - 1;
        com->pec.bottom = 1 - anchor->pec.bottom / 50; break;
    case ogg_anchor_coord:
        com->anchor_type = ogg_anchor_coord;
        com->coord.left = anchor->coord.left;
        com->coord.right = anchor->coord.right;
        com->coord.top = anchor->coord.top;
        com->coord.bottom = anchor->coord.bottom;
    }
}

#  define ogg_single_event(com_ptr, event_name, handled, args)                      \
    do {                                                                            \
        if ((!event_checker[event_name] ||                                          \
                event_checker[event_name]((ogg_component*)com_ptr, args)) &&        \
            com_ptr->vptr[event_name] != 0) {                                       \
            com_ptr->vptr[event_name](com_ptr, args, handled);                      \
        }                                                                           \
    } while (0)

extern const ogg_bool (*event_checker[OGG_EVENT_COUNT])(ogg_component*, va_list);

static void ogg_parent_handle_event(
        ogg_component* com_ptr,
        event event_name,
        ogg_handle_flag* handled, 
        va_list args)
{
    ogg_single_event(com_ptr, event_name, handled, args);
    ogg_subcomponent* iter = com_ptr->sub->next;
    while (!*handled && iter != 0) {
        ogg_parent_handle_event(iter->object, event_name, handled, args);
        iter = iter->next;
    }
}

static void ogg_child_handle_event(
        ogg_component* com_ptr,
        event event_name,
        ogg_handle_flag* handled, 
        va_list args)
{
    ogg_subcomponent* iter = com_ptr->sub->next;
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
    case OGG_CHILD_HANDLE_EVENT: 
        ogg_child_handle_event(com_ptr, event_name, &handled, args); break;
    case OGG_PARENT_HANDLE_EVENT:
        ogg_parent_handle_event(com_ptr, event_name, &handled, args); break;
    case OGG_SELF_HANDLE_EVENT:
        ogg_single_event(((ogg_component*)com_ptr), event_name, &handled, args); break;
    }
    va_end(args);
}

void ogg_destructor_ogg_component___(ogg_component* this)
{   /* leave a empty destructor of ogg_component here to ensure the macro works properly */
}

void ogg_destroy(ogg_com_ptr com_ptr)
{
    /* delete all child components */
    destroy_sub_components(com_ptr);
    /* destroy this component */
    ogg_single_event(((ogg_component*)com_ptr), OGG_DESTROY_EVENT, 0, 0);
    /* delete this object from parent */
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
                /* delete link node */
# ifdef DEBUG
                alloc_memory--;
# endif
                break;
            }
        }
    }
    /* free the momory of this object */
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

ogg_component_info ogg_default_info_ogg_component___(ogg_com_ptr parent)
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

#  undef ogg_single_event
