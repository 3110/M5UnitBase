#include "unit/ScrollUnit/ScrollUnit.hpp"

ScrollUnit scroll;

void setup(void) {
    scroll.begin(Wire);
}

void loop(void) {
    scroll.update();
}
