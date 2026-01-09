#include "utils.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>

#define TEST(name) std::cout << "\n=== Testing: " << name << " ===" << std::endl
#define PASS(msg) std::cout << "[PASS] " << msg << std::endl
#define FAIL(msg) std::cout << "[FAIL] " << msg << std::endl
#define INFO(msg) std::cout << "[INFO] " << msg << std::endl

void sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void test_screen_size() {
    TEST("f_get_screen_size()");

    ScreenPoint size = f_get_screen_size();

    if (size.invalid) {
        FAIL("Screen size returned invalid");
        return;
    }

    INFO("Screen width: " << size.x);
    INFO("Screen height: " << size.y);

    if (size.x > 0 && size.y > 0) {
        PASS("Screen size is valid");
    } else {
        FAIL("Screen size values are not positive");
    }
}

void test_cursor_position() {
    TEST("f_get_cursor_position()");

    ScreenPoint pos = f_get_cursor_position();

    if (pos.invalid) {
        FAIL("Cursor position returned invalid");
        return;
    }

    INFO("Cursor X: " << pos.x);
    INFO("Cursor Y: " << pos.y);
    PASS("Got cursor position");
}

void test_set_cursor_position() {
    TEST("f_set_cursor_position()");

    ScreenPoint original = f_get_cursor_position();

    int targetX = 100, targetY = 100;
    bool result = f_set_cursor_position(targetX, targetY);

    if (!result) {
        FAIL("f_set_cursor_position returned false");
        return;
    }

    sleep_ms(50);

    ScreenPoint newPos = f_get_cursor_position();
    INFO("Target: (" << targetX << ", " << targetY << ")");
    INFO("Actual: (" << newPos.x << ", " << newPos.y << ")");

    if (std::abs(newPos.x - targetX) <= 5 && std::abs(newPos.y - targetY) <= 5) {
        PASS("Cursor moved to target position");
    } else {
        FAIL("Cursor position mismatch");
    }

    f_set_cursor_position(static_cast<int>(original.x), static_cast<int>(original.y));
}

void test_mouse_state() {
    TEST("Mouse button state functions");

    bool leftDown = f_is_mouse_left_down();
    bool rightDown = f_is_mouse_right_down();
    bool middleDown = f_is_mouse_middle_down();

    INFO("Left button down: " << (leftDown ? "yes" : "no"));
    INFO("Right button down: " << (rightDown ? "yes" : "no"));
    INFO("Middle button down: " << (middleDown ? "yes" : "no"));

    PASS("Mouse state functions executed");
}

void test_mouse_swapped() {
    TEST("f_is_mouse_swapped()");

    bool swapped = f_is_mouse_swapped();
    INFO("Mouse buttons swapped: " << (swapped ? "yes" : "no"));
    PASS("Mouse swap check executed");
}

void test_mouse_clicks() {
    TEST("Mouse click functions (simulated - be careful!)");

    INFO("Testing left click...");
    bool leftResult = f_click_left();
    INFO("f_click_left() returned: " << (leftResult ? "true" : "false"));
    sleep_ms(100);

    INFO("Testing right click...");
    bool rightResult = f_click_right();
    INFO("f_click_right() returned: " << (rightResult ? "true" : "false"));
    sleep_ms(100);

    INFO("Testing middle click...");
    bool middleResult = f_click_middle();
    INFO("f_click_middle() returned: " << (middleResult ? "true" : "false"));

    if (leftResult && rightResult && middleResult) {
        PASS("All click functions returned true");
    } else {
        FAIL("Some click functions failed");
    }
}

void test_mouse_down_up() {
    TEST("Mouse down/up functions");

    INFO("Testing left mouse down...");
    bool leftDown = f_mouse_left_down();
    sleep_ms(50);
    bool leftUp = f_mouse_left_up();
    INFO("Left down: " << leftDown << ", up: " << leftUp);

    INFO("Testing right mouse down...");
    bool rightDown = f_mouse_right_down();
    sleep_ms(50);
    bool rightUp = f_mouse_right_up();
    INFO("Right down: " << rightDown << ", up: " << rightUp);

    INFO("Testing middle mouse down...");
    bool middleDown = f_mouse_middle_down();
    sleep_ms(50);
    bool middleUp = f_mouse_middle_up();
    INFO("Middle down: " << middleDown << ", up: " << middleUp);

    if (leftDown && leftUp && rightDown && rightUp && middleDown && middleUp) {
        PASS("All mouse down/up functions returned true");
    } else {
        FAIL("Some mouse down/up functions failed");
    }
}

void test_mouse_scroll() {
    TEST("f_mouse_scroll()");

    INFO("Scrolling up...");
    bool scrollUp = f_mouse_scroll(0, 3);
    sleep_ms(100);

    INFO("Scrolling down...");
    bool scrollDown = f_mouse_scroll(0, -3);
    sleep_ms(100);

    INFO("Scrolling right...");
    bool scrollRight = f_mouse_scroll(3, 0);
    sleep_ms(100);

    INFO("Scrolling left...");
    bool scrollLeft = f_mouse_scroll(-3, 0);

    INFO("Scroll results - up: " << scrollUp << ", down: " << scrollDown
        << ", right: " << scrollRight << ", left: " << scrollLeft);

    PASS("Mouse scroll tests completed");
}

void test_keys_ascii() {
    TEST("f_keys_press() - ASCII mode");

    KeyPressInfo singleKey[] = {
        {true, true, KeyPressMode::ASCII, 'a'}
    };

    bool result = f_keys_press(singleKey, 1);
    INFO("Single key 'a': " << (result ? "success" : "failed"));
    sleep_ms(50);

    KeyPressInfo multipleKeys[] = {
        {true, true, KeyPressMode::ASCII, 'h'},
        {true, true, KeyPressMode::ASCII, 'e'},
        {true, true, KeyPressMode::ASCII, 'l'},
        {true, true, KeyPressMode::ASCII, 'l'},
        {true, true, KeyPressMode::ASCII, 'o'}
    };

    result = f_keys_press(multipleKeys, 5);
    INFO("Multiple keys 'hello': " << (result ? "success" : "failed"));
    sleep_ms(50);

    KeyPressInfo numbers[] = {
        {true, true, KeyPressMode::ASCII, '1'},
        {true, true, KeyPressMode::ASCII, '2'},
        {true, true, KeyPressMode::ASCII, '3'}
    };

    result = f_keys_press(numbers, 3);
    INFO("Numbers '123': " << (result ? "success" : "failed"));

    PASS("ASCII key press tests completed");
}

void test_keys_special() {
    TEST("f_keys_press() - SPECIAL mode");

    KeyPressInfo enterKey[] = {
        {true, true, KeyPressMode::SPECIAL, 36} // Example: Enter on some systems
    };

    bool result = f_keys_press(enterKey, 1);
    INFO("Enter key: " << (result ? "success" : "failed"));
    sleep_ms(50);

    KeyPressInfo shiftDown[] = {
        {true, false, KeyPressMode::SPECIAL, 56} // Shift down only
    };

    result = f_keys_press(shiftDown, 1);
    INFO("Shift down: " << (result ? "success" : "failed"));
    sleep_ms(50);

    KeyPressInfo shiftUp[] = {
        {false, true, KeyPressMode::SPECIAL, 56} // Shift up only
    };

    result = f_keys_press(shiftUp, 1);
    INFO("Shift up: " << (result ? "success" : "failed"));

    PASS("Special key press tests completed");
}

void test_keys_unicode() {
    TEST("f_keys_press() - UNICODE mode");

    KeyPressInfo unicodeChar[] = {
        {true, true, KeyPressMode::UNICODE, 0x00E9} // é
    };

    bool result = f_keys_press(unicodeChar, 1);
    INFO("Unicode 'é' (U+00E9): " << (result ? "success" : "failed"));
    sleep_ms(50);

    KeyPressInfo emojiChar[] = {
        {true, true, KeyPressMode::UNICODE, 0x263A} // ☺
    };

    result = f_keys_press(emojiChar, 1);
    INFO("Unicode '☺' (U+263A): " << (result ? "success" : "failed"));

    PASS("Unicode key press tests completed");
}

void test_modifier_combinations() {
    TEST("Modifier key combinations");

    KeyPressInfo ctrlA[] = {
        {true, false, KeyPressMode::SPECIAL, 59}, // Ctrl down (macOS: 59, Linux varies)
        {true, true, KeyPressMode::ASCII, 'a'},   // 'a' press and release
        {false, true, KeyPressMode::SPECIAL, 59}  // Ctrl up
    };

    bool result = f_keys_press(ctrlA, 3);
    INFO("Ctrl+A combination: " << (result ? "success" : "failed"));

    PASS("Modifier combination tests completed");
}

void run_interactive_tests() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "INTERACTIVE TESTS (will simulate input!)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "These tests will actually move the mouse and type." << std::endl;
    std::cout << "Starting in 3 seconds..." << std::endl;

    sleep_ms(3000);

    test_mouse_clicks();
    sleep_ms(200);

    test_mouse_down_up();
    sleep_ms(200);

    test_mouse_scroll();
    sleep_ms(200);

    test_keys_ascii();
    sleep_ms(200);

    test_keys_special();
    sleep_ms(200);

    test_keys_unicode();
    sleep_ms(200);

    test_modifier_combinations();
}

void run_safe_tests() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "SAFE TESTS (read-only, no input simulation)" << std::endl;
    std::cout << "========================================" << std::endl;

    test_screen_size();
    test_cursor_position();
    test_mouse_state();
    test_mouse_swapped();
}

int main(int argc, char* argv[]) {
    std::cout << "jsautogui Test Suite" << std::endl;
    std::cout << "====================" << std::endl;

    bool interactive = false;
    bool cursor_test = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--interactive") == 0 || strcmp(argv[i], "-i") == 0) {
            interactive = true;
        }
        if (strcmp(argv[i], "--cursor") == 0 || strcmp(argv[i], "-c") == 0) {
            cursor_test = true;
        }
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  -h, --help         Show this help message" << std::endl;
            std::cout << "  -i, --interactive  Run interactive tests (simulates mouse/keyboard)" << std::endl;
            std::cout << "  -c, --cursor       Run cursor movement test" << std::endl;
            std::cout << "\nWithout options, only safe read-only tests are run." << std::endl;
            return 0;
        }
    }

    run_safe_tests();

    if (cursor_test) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "CURSOR MOVEMENT TEST" << std::endl;
        std::cout << "========================================" << std::endl;
        test_set_cursor_position();
    }

    if (interactive) {
        run_interactive_tests();
    } else {
        std::cout << "\n[INFO] Skipping interactive tests. Use --interactive to run them." << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "Test suite completed!" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
