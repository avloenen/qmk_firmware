RGBLIGHT_ENABLE    = no
RGB_MATRIX_ENABLE  = WS2812
MOUSEKEY_ENABLE    = no
NKRO_ENABLE        = yes
OLED_DRIVER_ENABLE = yes
EXTRAKEY_ENABLE    = yes
TAP_DANCE_ENABLE   = no

EXTRAFLAGS += -flto
SRC += ../../../../users/avloenen/oneshot.c
SRC += ../../../../users/avloenen/swapper.c