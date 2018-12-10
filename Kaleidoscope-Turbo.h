#include <stdint.h>
#include "Kaleidoscope.h"
#include "Kaleidoscope-Ranges.h"

#define Key_Turbo ((Key) { .raw = kaleidoscope::ranges::SAFE_START })

namespace kaleidoscope {
    namespace plugin {
        class Turbo : public kaleidoscope::Plugin {
            public:
                Turbo() {}
                static uint16_t interval;
                static uint16_t flash_interval;
                static bool toggle;
                static bool flash;
                static cRGB activeColor;
                EventHandlerResult onSetup();
                EventHandlerResult onLayerChange();
                EventHandlerResult onKeyswitchEvent(Key &key, byte row, byte col, uint8_t key_state);
                EventHandlerResult afterEachCycle();
            private:
                void initKeyPositions();
                static bool enable;
                static uint32_t start_time;
                static uint32_t flash_start_time;
                static byte keyPositions[4];
                static uint16_t numKeys;
        };
    }
}

extern kaleidoscope::plugin::Turbo Turbo;
