const gui = require("../index");

function TEST(name) {
    console.log(`\n=== Testing: ${name} ===`);
}

function PASS(msg) {
    console.log(`[PASS] ${msg}`);
}

function FAIL(msg) {
    console.log(`[FAIL] ${msg}`);
}

function INFO(msg) {
    console.log(`[INFO] ${msg}`);
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function test_screen_size() {
    TEST("screen.size");

    const size = gui.screen.size;

    INFO(`Screen width: ${size.width}`);
    INFO(`Screen height: ${size.height}`);

    if (size.width > 0 && size.height > 0) {
        PASS("Screen size is valid");
    } else {
        FAIL("Screen size values are not positive");
    }
}

function test_cursor_position() {
    TEST("mouse.getPosition()");

    const pos = gui.mouse.getPosition();

    INFO(`Cursor X: ${pos.x}`);
    INFO(`Cursor Y: ${pos.y}`);
    PASS("Got cursor position");
}

function test_mouse_state() {
    TEST("Mouse button state (isSwapped)");

    const swapped = gui.mouse.isSwapped;
    INFO(`Mouse buttons swapped: ${swapped ? "yes" : "no"}`);
    PASS("Mouse swap check executed");
}

function test_screen_helpers() {
    TEST("Screen helper functions");

    const center = gui.screen.center;
    INFO(`Screen center: (${center.x}, ${center.y})`);

    const includes = gui.screen.includes(100, 100);
    INFO(`Screen includes (100, 100): ${includes}`);

    const includesNegative = gui.screen.includes(-1, -1);
    INFO(`Screen includes (-1, -1): ${includesNegative}`);

    PASS("Screen helper functions executed");
}

async function test_set_cursor_position() {
    TEST("mouse.setPosition()");

    const original = gui.mouse.getPosition();

    const targetX = 100, targetY = 100;
    gui.mouse.setPosition(targetX, targetY);

    await sleep(50);

    const newPos = gui.mouse.getPosition();
    INFO(`Target: (${targetX}, ${targetY})`);
    INFO(`Actual: (${newPos.x}, ${newPos.y})`);

    if (Math.abs(newPos.x - targetX) <= 5 && Math.abs(newPos.y - targetY) <= 5) {
        PASS("Cursor moved to target position");
    } else {
        FAIL("Cursor position mismatch");
    }

    gui.mouse.setPosition(original.x, original.y);
}

async function test_mouse_clicks() {
    TEST("Mouse click functions (simulated - be careful!)");

    INFO("Testing left click...");
    gui.mouse.click("left");
    await sleep(100);

    INFO("Testing right click...");
    gui.mouse.click("right");
    await sleep(100);

    INFO("Testing middle click...");
    gui.mouse.click("middle");
    await sleep(100);

    PASS("All click functions executed");
}

async function test_mouse_down_up() {
    TEST("Mouse down/up functions");

    INFO("Testing left mouse down/up...");
    gui.mouse.down("left");
    await sleep(50);
    gui.mouse.up("left");

    INFO("Testing right mouse down/up...");
    gui.mouse.down("right");
    await sleep(50);
    gui.mouse.up("right");

    INFO("Testing middle mouse down/up...");
    gui.mouse.down("middle");
    await sleep(50);
    gui.mouse.up("middle");

    PASS("All mouse down/up functions executed");
}

async function test_mouse_scroll() {
    TEST("mouse.scroll()");

    INFO("Scrolling up...");
    gui.mouse.scroll(3, 0);
    await sleep(100);

    INFO("Scrolling down...");
    gui.mouse.scroll(-3, 0);
    await sleep(100);

    INFO("Scrolling right...");
    gui.mouse.hscroll(3, 0);
    await sleep(100);

    INFO("Scrolling left...");
    gui.mouse.hscroll(-3, 0);

    PASS("Mouse scroll tests completed");
}

async function test_keys_ascii() {
    TEST("keyboard.press() - ASCII mode");

    INFO("Pressing single key 'a'...");
    gui.keyboard.press("a");
    await sleep(50);

    INFO("Pressing multiple keys 'hello'...");
    gui.keyboard.write("hello");
    await sleep(50);

    INFO("Pressing numbers '123'...");
    gui.keyboard.write("123");

    PASS("ASCII key press tests completed");
}

async function test_keys_special() {
    TEST("keyboard.press() - SPECIAL mode");

    INFO("Pressing Enter key...");
    gui.keyboard.press("enter");
    await sleep(50);

    INFO("Pressing Shift down only...");
    gui.keyboard.down("shift");
    await sleep(50);

    INFO("Pressing Shift up...");
    gui.keyboard.up("shift");

    PASS("Special key press tests completed");
}

async function test_keys_unicode() {
    TEST("keyboard.write() - Unicode");

    INFO("Typing Unicode 'é'...");
    gui.keyboard.write("é");
    await sleep(50);

    INFO("Typing Unicode '☺'...");
    gui.keyboard.write("☺");

    PASS("Unicode key press tests completed");
}

async function test_modifier_combinations() {
    TEST("Modifier key combinations");

    INFO("Pressing Ctrl+A combination...");
    gui.keyboard.hotkey("ctrl", "a");

    PASS("Modifier combination tests completed");
}

function run_safe_tests() {
    console.log("\n========================================");
    console.log("SAFE TESTS (read-only, no input simulation)");
    console.log("========================================");

    test_screen_size();
    test_cursor_position();
    test_mouse_state();
    test_screen_helpers();
}

async function run_interactive_tests() {
    console.log("\n========================================");
    console.log("INTERACTIVE TESTS (will simulate input!)");
    console.log("========================================");
    console.log("These tests will actually move the mouse and type.");
    console.log("Starting in 3 seconds...");

    await sleep(3000);

    await test_mouse_clicks();
    await sleep(200);

    await test_mouse_down_up();
    await sleep(200);

    await test_mouse_scroll();
    await sleep(200);

    await test_keys_ascii();
    await sleep(200);

    await test_keys_special();
    await sleep(200);

    await test_keys_unicode();
    await sleep(200);

    await test_modifier_combinations();
}

async function run_cursor_test() {
    console.log("\n========================================");
    console.log("CURSOR MOVEMENT TEST");
    console.log("========================================");

    await test_set_cursor_position();
}

async function main() {
    console.log("jsautogui Test Suite (JavaScript)");
    console.log("==================================");

    const args = process.argv.slice(2);
    const interactive = args.includes("--interactive") || args.includes("-i");
    const cursorTest = args.includes("--cursor") || args.includes("-c");
    const help = args.includes("--help") || args.includes("-h");

    if (help) {
        console.log(`Usage: node test.js [options]`);
        console.log("Options:");
        console.log("  -h, --help         Show this help message");
        console.log("  -i, --interactive  Run interactive tests (simulates mouse/keyboard)");
        console.log("  -c, --cursor       Run cursor movement test");
        console.log("\nWithout options, only safe read-only tests are run.");
        return;
    }

    run_safe_tests();

    if (cursorTest) {
        await run_cursor_test();
    }

    if (interactive) {
        await run_interactive_tests();
    } else {
        console.log("\n[INFO] Skipping interactive tests. Use --interactive to run them.");
    }

    console.log("\n========================================");
    console.log("Test suite completed!");
    console.log("========================================");
}

main().catch(console.error);
