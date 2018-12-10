#include <Kaleidoscope.h>
#include <Kaleidoscope-MouseKeys.h>
#include <Kaleidoscope-Macros.h>
#include <Kaleidoscope-LEDControl.h>
#include <Kaleidoscope-LEDEffect-SolidColor.h>
#include <Kaleidoscope-LEDEffect-Rainbow.h>

#include "Kaleidoscope-Turbo.h"

enum { MACRO_ANY };

enum { PRIMARY, FUNCTION };

KEYMAPS(
    [PRIMARY] = KEYMAP_STACKED
    (___,          Key_1,         Key_2,     Key_3,      Key_4, Key_5, Key_LEDEffectNext,
     Key_Backtick, Key_Quote,     Key_Comma, Key_Period, Key_P, Key_Y, Key_Tab,
     Key_PageUp,   Key_A,         Key_O,     Key_E,      Key_U, Key_I,
     Key_PageDown, Key_Semicolon, Key_Q,     Key_J,      Key_K, Key_X, Key_Escape,

     Key_LeftShift, Key_Backspace, Key_LeftControl, Key_LeftGui,
     ShiftToLayer(FUNCTION),

     M(MACRO_ANY), Key_6, Key_7, Key_8, Key_9, Key_0, Key_PrintScreen,
     Key_Enter,    Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
                   Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
     Key_Turbo,    Key_B, Key_M, Key_W, Key_V, Key_Z, Key_Equals,

     Key_LeftAlt, Key_RightControl, Key_Spacebar, Key_RightShift,
     ShiftToLayer(FUNCTION)),


    [FUNCTION] = KEYMAP_STACKED
    (___,      Key_F1,     Key_F2,      Key_F3,     Key_F4,        Key_F5,           ___,
     Key_Tab,  ___,        Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE,
     Key_Home, Key_mouseL, Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
     Key_End,  ___,        Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,

     ___, Key_Delete, ___, ___,
     ___,

     Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
     Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                                 Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
     Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,

     ___, ___, Key_Enter, ___,
     ___)
    )

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
    switch (macroIndex) {
        case MACRO_ANY:
            if (keyIsPressed(keyState)) {
                Key key = (Key) { (uint8_t) (Key_A.keyCode + random(36)), KEY_FLAGS };
                kaleidoscope::hid::pressKey(key);
                delay(20);
            }
            break;
    }

    return MACRO_NONE;
}

static kaleidoscope::LEDSolidColor solidCat(181, 123, 60);

KALEIDOSCOPE_INIT_PLUGINS(
    LEDControl,
    solidCat,
    LEDRainbowWaveEffect,
    LEDOff,
    Macros,
    MouseKeys,
    Turbo
);

void setup() {
    Kaleidoscope.setup();

    Turbo.interval = 10;
    Turbo.toggle = true;
    Turbo.activeColor = CRGB(0xff, 0xff, 0x00);

    LEDRainbowWaveEffect.brightness(150);

    solidCat.activate();
}

void loop() {
    Kaleidoscope.loop();
}
