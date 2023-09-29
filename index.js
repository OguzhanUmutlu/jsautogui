/*** @type {Record<string, Function>} */
const native = require("./build/Release/jsautogui");
const os = require("os");
const platform = os.platform();

const eType = (a, t, n) => {
    if (typeof a !== t) {
        const e = new Error("Expected " + n + " to be a " + t + ", instead got: " + typeof a);
        throw e;
    }
};
const eInt32 = (a, n) => {
    eType(a, "number", n);
    if (a < INT32_MIN || a > INT32_MAX) {
        const e = new Error("Expected " + n + " to be a valid int32.");
        throw e;
    }
    if (a !== Math.floor(a)) {
        const e = new Error("Expected " + n + " to be an int32, instead got a float/double.");
        throw e;
    }
};
const eSize = (a, min, max, n) => {
    eType(a, "number", n);
    if (a < min || a > max) {
        const e = new Error("Expected " + n + " to be between (" + min + ", " + max + ").");
        throw e;
    }
};
const perm = s => {
    const e = new Error("Couldn't " + s + ", is the program lacking some permissions?");
    throw e;
};

const INT32_MIN = -2147483648;
const INT32_MAX = 2147483647;

let callPause = 0;
let failSafe = false;
let failSafeInterval;

const MESSAGE_BOX = {
    ICON: {
        hand: 0x00000010,
        question: 0x00000020,
        exclamation: 0x00000030,
        asterisk: 0x00000040,
        user: 0x00000080,
        warning: 0x00000030,
        error: 0x00000010,
        information: 0x00000040,
        stop: 0x00000010
    },
    BUTTONS: {
        ok: 0x00000000,
        ok_cancel: 0x00000001,
        abort_retry_ignore: 0x00000002,
        yes_no_cancel: 0x00000003,
        yes_no: 0x00000004,
        retry_cancel: 0x00000005,
        cancel_try_continue: 0x00000006
    },
    BUTTON_STYLE: {
        def1: 0x00000000,
        def2: 0x00000100,
        def3: 0x00000200,
        def4: 0x00000300
    },
    TYPE: {
        appl_modal: 0x00000000,
        system_modal: 0x00001000,
        task_modal: 0x00002000,
        help: 0x00003000
    },
    ACTIONS: {
        no_focus: 0x00008000,
        set_foreground: 0x00010000,
        default_desktop_only: 0x00020000,
        top_most: 0x00040000,
        right: 0x00080000,
        rtl_reading: 0x00100000,
    },
    RESPONSES: {
        ok: 1,
        cancel: 2,
        abort: 3,
        retry: 4,
        ignore: 5,
        yes: 6,
        no: 7,
        try: 10,
        continue: 11,
        1: "ok",
        2: "cancel",
        3: "abort",
        4: "retry",
        5: "ignore",
        6: "yes",
        7: "no",
        10: "try",
        11: "continue"
    }
};

let KEYS = {};
if (platform === "win32") {
    const WIN_KEYS = require("./data/win-keys");
    KEYS = {
        ...WIN_KEYS,
        "!": WIN_KEYS.shift,
        "@": WIN_KEYS.altright,
        "#": WIN_KEYS.altright,
        "$": WIN_KEYS.altright,
        "%": WIN_KEYS.shift,
        "^": WIN_KEYS.shift,
        "&": WIN_KEYS.shift,
        "(": WIN_KEYS.shift,
        ")": WIN_KEYS.shift,
        "_": WIN_KEYS.shift,
        "=": WIN_KEYS.shift,
        "{": WIN_KEYS.altright,
        "}": WIN_KEYS.altright,
        "[": WIN_KEYS.altright,
        "]": WIN_KEYS.altright,
        "|": WIN_KEYS.altright,
        "\\": WIN_KEYS.altright,
        ":": WIN_KEYS.shift,
        ";": WIN_KEYS.shift,
        "\"": WIN_KEYS.shift,
        "<": WIN_KEYS.shift,
        ">": WIN_KEYS.shift,
        "?": WIN_KEYS.shift,
        "/": WIN_KEYS.altright,
        "~": WIN_KEYS.altright,
        "`": WIN_KEYS.altright
    };
} else if (platform === "linux") {
    KEYS = require("./data/x11-keys");
} else {
    // KEYS = {...require("./data/osx-keys"), ...require("./data/osx-modifiers")}
}

const KEY_NAMES = [
    "\t", "\n", "\r", " ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", "0", "1", "2",
    "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`", "a", "b", "c",
    "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
    "{", "|", "}", "~", "accept", "add", "alt", "altleft", "altright", "apps", "backspace", "browserback",
    "browserfavorites", "browserforward", "browserhome", "browserrefresh", "browsersearch", "browserstop", "capslock",
    "clear", "convert", "ctrl", "ctrlleft", "ctrlright", "decimal", "del", "delete", "divide", "down", "end", "enter",
    "esc", "escape", "execute", "f1", "f10", "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19", "f2", "f20",
    "f21", "f22", "f23", "f24", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "final", "fn", "hanguel", "hangul", "hanja",
    "help", "home", "insert", "junja", "kana", "kanji", "launchapp1", "launchapp2", "launchmail", "launchmediaselect",
    "left", "modechange", "multiply", "nexttrack", "nonconvert", "num0", "num1", "num2", "num3", "num4", "num5", "num6",
    "num7", "num8", "num9", "numlock", "pagedown", "pageup", "pause", "pgdn", "pgup", "playpause", "prevtrack", "print",
    "printscreen", "prntscrn", "prtsc", "prtscr", "return", "right", "scrolllock", "select", "separator", "shift",
    "shiftleft", "shiftright", "sleep", "space", "stop", "subtract", "tab", "up", "volumedown", "volumemute",
    "volumeup", "win", "winleft", "winright", "yen", "command", "option", "optionleft", "optionright"
];

function linear(dx, dy, steps) {
    const stepVector = {x: dx / steps, y: dy / steps};
    return function (_step) {
        API.mouse.moveRel(stepVector.x, stepVector.y);
    };
}

class MessageBox {
    title = "";
    text = "";
    buttons = "ok";
    icon = "";

    show() {
        let flags = 0;
        const btn = MESSAGE_BOX.BUTTONS[this.buttons];
        const icon = MESSAGE_BOX.ICON[this.icon];
        if (btn) flags |= btn;
        if (icon) flags |= icon;
        return MESSAGE_BOX.RESPONSES[native.show_message_box(this.title, this.text, flags)];
    };
}

class PromptBox {
    show() {
        return native.show_prompt();
    };
}

const API = {
    __native: native,
    MESSAGE_BOX,
    KEY_NAMES,
    get FAIL_SAFE() {
        return failSafe;
    },
    set FAIL_SAFE(v) {
        eType(v, "boolean", "FAIL_SAFE");
        if (v === failSafe) return;
        clearInterval(failSafeInterval);
        if (v === true) failSafeInterval = setInterval(() => {
            const pos = native.get_mouse_pos();
            if (!pos) return;
            if (pos.x < 3 && pos.y < 3) throw new Error("Failed safely. This has been enabled by setting the .FAIL_SAFE value to true.");
        }, 100);
    },
    get PAUSE() {
        return callPause;
    },
    set PAUSE(v) {
        eInt32(v, "PAUSE");
        eSize(v, 0, INT32_MAX, "PAUSE");
        callPause = v;
        native.set_pause(v);
    },
    mouse: {
        LinearTween: linear,
        get position() {
            return this.getPosition();
        },
        set position(v) {
            this.setPosition(v.x, v.y);
        },
        get x() {
            return this.position.x;
        },
        set x(v) {
            eInt32(v, "mouse.position.x");
            eSize(v, 0, INT32_MAX, "mouse.position.x");
            if (!native.set_mouse_x(v)) return perm("set the x position of the mouse");
        },
        get y() {
            return this.position.y;
        },
        set y(v) {
            eInt32(v, "mouse.position.y");
            eSize(v, 0, INT32_MAX, "mouse.position.y");
            if (!native.set_mouse_y(v)) return perm("set the y position of the mouse");
        },
        getPosition(point = true) {
            const pos = native.get_mouse_pos();
            if (!pos) return perm("find the position of the mouse");
            if (!point) return pos;
            const obj = {};
            Object.defineProperties(obj, {
                x: {
                    get: () => pos.x,
                    set: v => this.x = v
                },
                y: {
                    get: () => pos.y,
                    set: v => this.y = v
                }
            });
            return obj;
        },
        setPosition(x, y) {
            eInt32(x, "mouse.position.x");
            eInt32(y, "mouse.position.y");
            eSize(x, 0, INT32_MAX, "mouse.position.x");
            eSize(y, 0, INT32_MAX, "mouse.position.y");
            if (!native.set_mouse_pos(x, y)) return perm("set the position of the mouse");
        },
        moveTo(x, y, duration = 0, tween = linear, deltaTime = 50) {
            eInt32(x, "x");
            eInt32(y, "y");
            eSize(x, 0, INT32_MAX, "x");
            eSize(y, 0, INT32_MAX, "y");
            eInt32(duration, "duration");
            eInt32(deltaTime, "deltaTime");
            if (duration === 0) return native.set_mouse_pos(x, y);
            eType(tween, "function");
            const start = native.get_mouse_pos();
            return this.moveRel(x - start.x, y - start.y, duration, tween, deltaTime);
        },
        moveRel(dx, dy, duration = 0, tween = linear, deltaTime = 50) {
            eInt32(dx, "x");
            eInt32(dy, "y");
            eInt32(duration, "duration");
            eInt32(deltaTime, "deltaTime");
            if (duration === 0) return native.set_mouse_pos_rel(dx, dy) || perm("set the position of the mouse");
            if (deltaTime > duration) deltaTime = duration;
            const start = native.get_mouse_pos();
            const steps = Math.ceil(duration / deltaTime);
            const tweenInit = tween(dx, dy, steps);
            let step = 0;
            return new Promise(r => {
                const intervalId = setInterval(() => {
                    duration -= deltaTime;
                    if (duration <= 0) {
                        if (duration !== 0) native.set_mouse_pos(start.x, start.y);
                        r();
                        return clearInterval(intervalId);
                    }
                    tweenInit(step);
                    step++;
                }, deltaTime);
            });
        },
        dragTo(x, y, button = "primary", duration = 0, tween = linear, deltaTime = 50) {
            this.down(button);
            const r = this.moveTo(x, y, duration, tween, deltaTime);
            if (r instanceof Promise) return r.then(() => this.up(button));
            this.up(button);
        },
        dragRel(x, y, button = "primary", duration = 0, tween = linear, deltaTime = 50) {
            this.down(button);
            const r = this.moveRel(x, y, duration, tween, deltaTime);
            if (r instanceof Promise) return r.then(() => this.up(button));
            this.up(button);
        },
        get isSwapped() {
            return native.is_mouse_swapped();
        },
        down(button = "primary") {
            if (button === "primary") button = this.isSwapped ? "right" : "left";
            if (button === "secondary") button = this.isSwapped ? "left" : "right";
            if (button === "right") return native.mouse_right_down() || perm("press a button in mouse");
            if (button === "left") return native.mouse_left_down() || perm("press a button in mouse");
            if (button === "middle") return native.mouse_middle_down() || perm("press a button in mouse");
            throw new Error("Expected the button argument to be 'right', 'left', 'middle', 'primary', 'secondary'. Got: " + button);
        },
        up(button = "primary") {
            if (button === "primary") button = this.isSwapped ? "right" : "left";
            if (button === "secondary") button = this.isSwapped ? "left" : "right";
            if (button === "right") return native.mouse_right_up() || perm("release a button in mouse");
            if (button === "left") return native.mouse_left_up() || perm("release a button in mouse");
            if (button === "middle") return native.mouse_middle_up() || perm("release a button in mouse");
            throw new Error("Expected the button argument to be 'right', 'left', 'middle', 'primary', 'secondary'. Got: " + button);
        },
        click(button = "primary") {
            if (button === "primary") button = this.isSwapped ? "right" : "left";
            if (button === "secondary") button = this.isSwapped ? "left" : "right";
            if (button === "right") return native.click_right() || perm("press a button in mouse");
            if (button === "left") return native.click_left() || perm("press a button in mouse");
            if (button === "middle") return native.click_middle() || perm("press a button in mouse");
            throw new Error("Expected the button argument to be 'right', 'left', 'middle', 'primary', 'secondary'. Got: " + button);
        },
        scroll(x = 0, y = 0) {
            eInt32(x, "x");
            eInt32(y, "y");
            if (!native.mouse_scroll(x, y)) perm("scroll the wheel of mouse");
        }
    },
    keyboard: {
        __native(key, fn) {
            if (KEYS[key]) native[fn](false, KEYS[key]);
            else {
                /*const modifier = WIN_MODIFIERS[key];
                if (modifier) native.key_down(false, modifier) || perm("press a key of keyboard");
                native[fn](true, key.charCodeAt(0));
                if (modifier) native.key_up(false, modifier) || perm("press a key of keyboard");*/
                native[fn](true, key.charCodeAt(0));
                // todo: fix modifiers
            }
        },
        press(...keys) {
            for (const key of keys) this.__native(key, "press_key");
        },
        down(...keys) {
            for (const key of keys) this.__native(key, "key_down");
        },
        up(...keys) {
            for (const key of keys) this.__native(key, "key_up");
        },
        write(...texts) {
            for (const text of texts) {
                for (let i = 0; i < text.length; i++) this.press(text[i]);
            }
        },
        hotkey(...keys) {
            this.down(...keys);
            this.up(...keys);
        }
    },
    screen: {
        get size() {
            return native.get_screen_size();
        },
        get width() {
            return this.size.width;
        },
        get height() {
            return this.size.height;
        },
        get center() {
            const s = this.size;
            return {x: Math.floor(s.width / 2), y: Math.floor(s.height / 2)};
        },
        includes(x, y) {
            eInt32(x, "x");
            eInt32(y, "y");
            const size = native.get_screen_size();
            return x >= 0 && y >= 0 && x < size.width && y < size.height;
        },
        contains(x, y) {
            return this.includes(x, y);
        }
    },
    MessageBox,
    PromptBox,
    alert(text, title = "Alert") {
        return native.show_message_box(text, title, MESSAGE_BOX.ICON.warning | MESSAGE_BOX.BUTTONS.ok);
    },
    confirm(text, title = "Confirm") {
        return native.show_message_box(text, title, MESSAGE_BOX.ICON.warning | MESSAGE_BOX.BUTTONS.yes_no) === MESSAGE_BOX.RESPONSES.yes;
    }
};

module.exports = API;
API.default = API;