#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *current_time;
    lv_obj_t *last_time;
    lv_obj_t *target_time;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_COMMON_WIDGET = 2,
};

void create_screen_main();
void tick_screen_main();

void create_user_widget_common_widget(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_common_widget(int startWidgetIndex);

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/