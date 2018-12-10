#include "Kaleidoscope-Turbo.h"
#include "Kaleidoscope-LEDControl.h"

namespace kaleidoscope {
    namespace plugin {
        uint16_t Turbo::interval = 50;
        uint16_t Turbo::flash_interval = 69;
        bool Turbo::toggle = false;
        bool Turbo::flash = true;
        cRGB Turbo::activeColor = (cRGB) { 0x00, 0x00, 0xff };

        bool Turbo::enable = false;
        uint32_t Turbo::start_time = 0;
        uint32_t Turbo::flash_start_time = 0;
        byte Turbo::keyPositions[4];
        uint16_t Turbo::numKeys = 0;

        void Turbo::initKeyPositions() {
            numKeys = 0;
            for (byte r = 0; r < ROWS; r++) {
                for (byte c = 0; c < COLS; c++) {
                    if (Layer.lookupOnActiveLayer(r, c) == Key_Turbo) {
                        keyPositions[numKeys++] = r * COLS + c;
                    }
                }
            }
        }

        EventHandlerResult Turbo::onSetup() {
            Turbo::initKeyPositions();
            return EventHandlerResult::OK;
        }

        EventHandlerResult Turbo::onLayerChange() {
            Turbo::initKeyPositions();
            return EventHandlerResult::OK;
        }

        EventHandlerResult Turbo::onKeyswitchEvent(Key &key, byte row, byte col, uint8_t key_state) {
            if (key != Key_Turbo) return EventHandlerResult::OK;
            enable = toggle ? (keyIsPressed(key_state) ? enable : !enable) : keyIsPressed(key_state);
            if (!enable) {
                for (uint16_t i = 0; i < numKeys; i++) {
                    LEDControl::refreshAt(keyPositions[i] / COLS, keyPositions[i] % COLS);
                }
            }
            return EventHandlerResult::EVENT_CONSUMED;
        }

        EventHandlerResult Turbo::afterEachCycle() {
            if (enable) {
                if (Kaleidoscope.millisAtCycleStart() - start_time > interval) {
                    kaleidoscope::hid::sendKeyboardReport();
                    start_time = Kaleidoscope.millisAtCycleStart();
                }

                if (flash) {
                    if (Kaleidoscope.millisAtCycleStart() - flash_start_time > flash_interval * 2) {
                        for (uint16_t i = 0; i < numKeys; i++) {
                            LEDControl::setCrgbAt(keyPositions[i] / COLS, keyPositions[i] % COLS, activeColor);
                        }
                        flash_start_time = Kaleidoscope.millisAtCycleStart();
                    } else if (Kaleidoscope.millisAtCycleStart() - flash_start_time > flash_interval) {
                        for (uint16_t i = 0; i < numKeys; i++) {
                            LEDControl::setCrgbAt(keyPositions[i] / COLS, keyPositions[i] % COLS, {0, 0, 0});
                        }
                    }
                    LEDControl::syncLeds();
                } else {
                    for (uint16_t i = 0; i < numKeys; i++) {
                        LEDControl::setCrgbAt(keyPositions[i] / COLS, keyPositions[i] % COLS, activeColor);
                    }
                }
            }
            return EventHandlerResult::OK;
        }
    }
}

kaleidoscope::plugin::Turbo Turbo;
