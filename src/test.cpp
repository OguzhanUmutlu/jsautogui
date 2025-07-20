#include "utils.h"

int main() {
    KeyPressInfo presses[] = {
        {true, true, KeyPressMode::ASCII, 'a'}
    };

    f_keys_press(presses, 1);
    return 0;
}
