#ifndef OGG_GRAPHIC_COMPONENT__GRID__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENT__GRID__HEADER_FILE_____
#include "graphic_components.h"

# ifdef __cplusplus
extern "C"{
# endif

    typedef struct  {
        ogg_com_startup startup;
        ogg_coord size;
    } ogg_grid_info;

    typedef struct {
        ogg_component com;
        ogg_com_ptr object;
    } ogg_grid_element;

    typedef struct {
        ogg_component com;
        ogg_coord size;
        ogg_grid_element ***sub;
    } ogg_grid;

    //ogg_grid_element* create_grid_element(ogg_com_ptr parent);

    //void destroy_grid_element(ogg_grid_element* grid_elem);

    //void paint_grid_element(ogg_grid_element* grid_elem);

    // grid utils
    /*
    * grid constructor
    */
    ogg_grid* create_grid(const ogg_grid_info* st);
    /*
    * grid destructor
    */
    void destroy_grid(ogg_grid* grid);

    void paint_grid(ogg_grid* grid);

    // ============= 
    void set_grid_elem(ogg_grid* grid, ogg_com_ptr com, ogg_coord pos);

    void destroy_grid_elem(ogg_grid* grid, ogg_coord pos);

    ogg_bool paint_grid_elem(ogg_grid* grid, ogg_coord pos);

# ifdef __cplusplus
}
# endif

#endif //OGG_GRAPHIC_COMPONENT__GRID__HEADER_FILE_____