#include "graphic_components.h"

# ifdef __cplusplus
extern "C"{
# endif

void create_component(ogg_com_ptr com_ptr, const ogg_component_info* cominfo)
{
    set_component_anchor(com_ptr, cominfo->anchor);
    ogg_component* com = (ogg_component*)com_ptr;
    com->parent = cominfo->parent;
    com->vptr = cominfo->vptr;
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

void ogg_send_event(ogg_com_ptr com_ptr, unsigned event_name)
{
    ((ogg_component*)com_ptr)->vptr[event_name](com_ptr);
}

void destroy_component(ogg_com_ptr* com_ptr)
{
    ogg_send_event(*com_ptr, OGG_DESTROY_EVENT);
    *com_ptr = 0;
}

ogg_coord coord(int x, int y)
{
    ogg_coord pos = { x, y };
    return pos;
}

ogg_com_startup ogg_make_startup(ogg_com_ptr parent)
{
    ogg_com_startup st = {
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

# ifdef __cplusplus
}
# endif