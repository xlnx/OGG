#ifndef OGG_GRPHIC_EVENTS__HEADER_FILE____
#define OGG_GRPHIC_EVENTS__HEADER_FILE____

# define OGG_EVENT_COUNT         (2)

# define OGG_DESTROY_EVENT       (0)
# define OGG_PAINT_EVENT         (1)

# define OGG_CHILD_HANDLE_EVENT  (0)
# define OGG_PARENT_HANDLE_EVENT (1)

static ogg_event_type[OGG_EVENT_COUNT] = {
    OGG_CHILD_HANDLE_EVENT,      // OGG_DESTROY_EVENT
    OGG_PARENT_HANDLE_EVENT,     // OGG_PAINT_EVENT
};

#endif //OGG_GRPHIC_EVENTS__HEADER_FILE____