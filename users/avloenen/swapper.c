#include "swapper.h"
// Made by Callum - little changes by me

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record,
    uint16_t alternative
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active) {
        if (keycode != alternative) { // keep cmd to switch between cmd-tab & cmd-grv
            unregister_code(cmdish);
            *active = false;
        }

    }
}

