#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *tires;
    lv_obj_t *inverters;
    lv_obj_t *extra;
    lv_obj_t *obj0;
    lv_obj_t *obj0__lv_bat_voltage;
    lv_obj_t *obj0__hv_soc_est;
    lv_obj_t *obj0__sx_status_bar;
    lv_obj_t *obj0__dx_status_bar;
    lv_obj_t *obj0__sx_map;
    lv_obj_t *obj0__lc_ctrl;
    lv_obj_t *obj0__tc_ctrl;
    lv_obj_t *obj0__tv_ctrl;
    lv_obj_t *obj0__dx_map;
    lv_obj_t *current_time;
    lv_obj_t *last_time;
    lv_obj_t *target_time;
    lv_obj_t *front_left_temp;
    lv_obj_t *obj1;
    lv_obj_t *front_left_bar;
    lv_obj_t *obj2;
    lv_obj_t *front_right_temp;
    lv_obj_t *obj3;
    lv_obj_t *front_right_bar;
    lv_obj_t *obj4;
    lv_obj_t *rear_left_temp;
    lv_obj_t *obj5;
    lv_obj_t *rear_left_bar;
    lv_obj_t *obj6;
    lv_obj_t *rear_right_temp;
    lv_obj_t *obj7;
    lv_obj_t *rear_right_bar;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj9__lv_bat_voltage;
    lv_obj_t *obj9__hv_soc_est;
    lv_obj_t *obj9__sx_status_bar;
    lv_obj_t *obj9__dx_status_bar;
    lv_obj_t *obj9__sx_map;
    lv_obj_t *obj9__lc_ctrl;
    lv_obj_t *obj9__tc_ctrl;
    lv_obj_t *obj9__tv_ctrl;
    lv_obj_t *obj9__dx_map;
    lv_obj_t *front_left_temp_inv;
    lv_obj_t *obj10;
    lv_obj_t *front_left_inv_state;
    lv_obj_t *front_right_temp_inv;
    lv_obj_t *obj11;
    lv_obj_t *front_right_inv_state;
    lv_obj_t *rear_left_temp_inv;
    lv_obj_t *obj12;
    lv_obj_t *rear_left_inv_state;
    lv_obj_t *rear_right_temp_inv;
    lv_obj_t *obj13;
    lv_obj_t *rear_right_inv_state;
    lv_obj_t *obj14;
    lv_obj_t *obj14__lv_bat_voltage;
    lv_obj_t *obj14__hv_soc_est;
    lv_obj_t *obj14__sx_status_bar;
    lv_obj_t *obj14__dx_status_bar;
    lv_obj_t *obj14__sx_map;
    lv_obj_t *obj14__lc_ctrl;
    lv_obj_t *obj14__tc_ctrl;
    lv_obj_t *obj14__tv_ctrl;
    lv_obj_t *obj14__dx_map;
    lv_obj_t *obj15;
    lv_obj_t *obj15__lv_bat_voltage;
    lv_obj_t *obj15__hv_soc_est;
    lv_obj_t *obj15__sx_status_bar;
    lv_obj_t *obj15__dx_status_bar;
    lv_obj_t *obj15__sx_map;
    lv_obj_t *obj15__lc_ctrl;
    lv_obj_t *obj15__tc_ctrl;
    lv_obj_t *obj15__tv_ctrl;
    lv_obj_t *obj15__dx_map;
    lv_obj_t *cooling_sys_bar;
    lv_obj_t *cooling_sys_temp;
    lv_obj_t *throttle_perc;
    lv_obj_t *rear_brake_bar;
    lv_obj_t *front_brake_bar;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_TIRES = 2,
    SCREEN_ID_INVERTERS = 3,
    SCREEN_ID_EXTRA = 4,
    SCREEN_ID_COMMON_WIDGET = 5,
};

void create_screen_main();
void tick_screen_main();

void create_screen_tires();
void tick_screen_tires();

void create_screen_inverters();
void tick_screen_inverters();

void create_screen_extra();
void tick_screen_extra();

void create_user_widget_common_widget(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_common_widget(int startWidgetIndex);

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/