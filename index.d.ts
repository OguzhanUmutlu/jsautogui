type MESSAGE_BOX = {
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

type WIN_KEYS = {
    'backspace': 0x08, // VK_BACK
    '\b': 0x08, // VK_BACK
    'super': 0x5B, // VK_LWIN
    'tab': 0x09, // VK_TAB
    '\t': 0x09, // VK_TAB
    'clear': 0x0c, // VK_CLEAR
    'enter': 0x0d, // VK_RETURN
    '\n': 0x0d, // VK_RETURN
    'return': 0x0d, // VK_RETURN
    'shift': 0x10, // VK_SHIFT
    'ctrl': 0x11, // VK_CONTROL
    'alt': 0x12, // VK_MENU
    'pause': 0x13, // VK_PAUSE
    'capslock': 0x14, // VK_CAPITAL
    'kana': 0x15, // VK_KANA
    'hanguel': 0x15, // VK_HANGUEL
    'hangul': 0x15, // VK_HANGUL
    'junja': 0x17, // VK_JUNJA
    'final': 0x18, // VK_FINAL
    'hanja': 0x19, // VK_HANJA
    'kanji': 0x19, // VK_KANJI
    'esc': 0x1b, // VK_ESCAPE
    'escape': 0x1b, // VK_ESCAPE
    'convert': 0x1c, // VK_CONVERT
    'nonconvert': 0x1d, // VK_NONCONVERT
    'accept': 0x1e, // VK_ACCEPT
    'modechange': 0x1f, // VK_MODECHANGE
    ' ': 0x20, // VK_SPACE
    'space': 0x20, // VK_SPACE
    'pgup': 0x21, // VK_PRIOR
    'pgdn': 0x22, // VK_NEXT
    'pageup': 0x21, // VK_PRIOR
    'pagedown': 0x22, // VK_NEXT
    'end': 0x23, // VK_END
    'home': 0x24, // VK_HOME
    'left': 0x25, // VK_LEFT
    'up': 0x26, // VK_UP
    'right': 0x27, // VK_RIGHT
    'down': 0x28, // VK_DOWN
    'select': 0x29, // VK_SELECT
    'print': 0x2a, // VK_PRINT
    'execute': 0x2b, // VK_EXECUTE
    'prtsc': 0x2c, // VK_SNAPSHOT
    'prtscr': 0x2c, // VK_SNAPSHOT
    'prntscrn': 0x2c, // VK_SNAPSHOT
    'printscreen': 0x2c, // VK_SNAPSHOT
    'insert': 0x2d, // VK_INSERT
    'del': 0x2e, // VK_DELETE
    'delete': 0x2e, // VK_DELETE
    'help': 0x2f, // VK_HELP
    'win': 0x5b, // VK_LWIN
    'winleft': 0x5b, // VK_LWIN
    'winright': 0x5c, // VK_RWIN
    'apps': 0x5d, // VK_APPS
    'sleep': 0x5f, // VK_SLEEP
    'num0': 0x60, // VK_NUMPAD0
    'num1': 0x61, // VK_NUMPAD1
    'num2': 0x62, // VK_NUMPAD2
    'num3': 0x63, // VK_NUMPAD3
    'num4': 0x64, // VK_NUMPAD4
    'num5': 0x65, // VK_NUMPAD5
    'num6': 0x66, // VK_NUMPAD6
    'num7': 0x67, // VK_NUMPAD7
    'num8': 0x68, // VK_NUMPAD8
    'num9': 0x69, // VK_NUMPAD9
    'multiply': 0x6a, // VK_MULTIPLY
    'add': 0x6b, // VK_ADD
    'separator': 0x6c, // VK_SEPARATOR  ??? Is this the numpad enter?
    'subtract': 0x6d, // VK_SUBTRACT
    '*': 0x6a,
    '+': 0x6b,
    '-': 0x6d,
    'decimal': 0x6e, // VK_DECIMAL
    'divide': 0x6f, // VK_DIVIDE
    'f1': 0x70, // VK_F1
    'f2': 0x71, // VK_F2
    'f3': 0x72, // VK_F3
    'f4': 0x73, // VK_F4
    'f5': 0x74, // VK_F5
    'f6': 0x75, // VK_F6
    'f7': 0x76, // VK_F7
    'f8': 0x77, // VK_F8
    'f9': 0x78, // VK_F9
    'f10': 0x79, // VK_F10
    'f11': 0x7a, // VK_F11
    'f12': 0x7b, // VK_F12
    'f13': 0x7c, // VK_F13
    'f14': 0x7d, // VK_F14
    'f15': 0x7e, // VK_F15
    'f16': 0x7f, // VK_F16
    'f17': 0x80, // VK_F17
    'f18': 0x81, // VK_F18
    'f19': 0x82, // VK_F19
    'f20': 0x83, // VK_F20
    'f21': 0x84, // VK_F21
    'f22': 0x85, // VK_F22
    'f23': 0x86, // VK_F23
    'f24': 0x87, // VK_F24
    'numlock': 0x90, // VK_NUMLOCK
    'scrolllock': 0x91, // VK_SCROLL
    'shiftleft': 0xa0, // VK_LSHIFT
    'shiftright': 0xa1, // VK_RSHIFT
    'ctrlleft': 0xa2, // VK_LCONTROL
    'ctrlright': 0xa3, // VK_RCONTROL
    'altleft': 0xa4, // VK_LMENU
    'altright': 0xa5, // VK_RMENU
    'browserback': 0xa6, // VK_BROWSER_BACK
    'browserforward': 0xa7, // VK_BROWSER_FORWARD
    'browserrefresh': 0xa8, // VK_BROWSER_REFRESH
    'browserstop': 0xa9, // VK_BROWSER_STOP
    'browsersearch': 0xaa, // VK_BROWSER_SEARCH
    'browserfavorites': 0xab, // VK_BROWSER_FAVORITES
    'browserhome': 0xac, // VK_BROWSER_HOME
    'volumemute': 0xad, // VK_VOLUME_MUTE
    'volumedown': 0xae, // VK_VOLUME_DOWN
    'volumeup': 0xaf, // VK_VOLUME_UP
    'nexttrack': 0xb0, // VK_MEDIA_NEXT_TRACK
    'prevtrack': 0xb1, // VK_MEDIA_PREV_TRACK
    'stop': 0xb2, // VK_MEDIA_STOP
    'playpause': 0xb3, // VK_MEDIA_PLAY_PAUSE
    'launchmail': 0xb4, // VK_LAUNCH_MAIL
    'launchmediaselect': 0xb5, // VK_LAUNCH_MEDIA_SELECT
    'launchapp1': 0xb6, // VK_LAUNCH_APP1
    'launchapp2': 0xb7, // VK_LAUNCH_APP2
};
type WIN_MODIFIERS = {
    '!': WIN_KEYS["shift"],
    '@': WIN_KEYS["altright"],
    '#': WIN_KEYS["altright"],
    '$': WIN_KEYS["altright"],
    '%': WIN_KEYS["shift"],
    '^': WIN_KEYS["shift"],
    '&': WIN_KEYS["shift"],
    '(': WIN_KEYS["shift"],
    ')': WIN_KEYS["shift"],
    '_': WIN_KEYS["shift"],
    '=': WIN_KEYS["shift"],
    '{': WIN_KEYS["altright"],
    '}': WIN_KEYS["altright"],
    '[': WIN_KEYS["altright"],
    ']': WIN_KEYS["altright"],
    '|': WIN_KEYS["altright"],
    '\\': WIN_KEYS["altright"],
    ':': WIN_KEYS["shift"],
    ';': WIN_KEYS["shift"],
    '\'': WIN_KEYS["shift"],
    '<': WIN_KEYS["shift"],
    '>': WIN_KEYS["shift"],
    '?': WIN_KEYS["shift"],
    '/': WIN_KEYS["altright"],
    '~': WIN_KEYS["altright"],
    '`': WIN_KEYS["altright"]
};

type KEY_NAMES = [
    "\t", "\n", "\r", " ", "!", '"', "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", "0", "1", "2",
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

declare class MessageBox {
    title: string;
    text: string;
    buttons: keyof MESSAGE_BOX["BUTTONS"];
    icon: keyof MESSAGE_BOX["ICON"];

    show(): MESSAGE_BOX["RESPONSES"][keyof MESSAGE_BOX["RESPONSES"]];
}

declare class PromptBox {
    show(): number;
}

type Buttons = ["primary", "secondary", "left", "right", "middle"];

type int32 = number;
type int64 = number;
type NATIVE_API = {
    set_pause(pause: int32): void;
    get_screen_size(): { width: int32, height: int32 };
    set_mouse_pos_rel(dx: int32, dy: int32): boolean;
    set_mouse_pos(x: int32, y: int32): boolean;
    set_mouse_x(x: int32): boolean;
    set_mouse_y(y: int32): boolean;
    get_mouse_pos(): { x: int32, y: int32 };
    mouse_is_left_down(): boolean;
    mouse_is_right_down(): boolean;
    mouse_is_middle_down(): boolean;
    click_left(): boolean;
    click_right(): boolean;
    click_middle(): boolean;
    mouse_left_down(): boolean;
    mouse_right_down(): boolean;
    mouse_middle_down(): boolean;
    mouse_left_up(): boolean;
    mouse_right_up(): boolean;
    mouse_middle_up(): boolean;
    is_mouse_swapped(): boolean;
    mouse_scroll(x: int32, y: int32): boolean;
    press_key(is_ascii: boolean, key: int32): boolean;
    key_down(is_ascii: boolean, key: int32): boolean;
    key_up(is_ascii: boolean, key: int32): boolean;
    show_message_box(text: string, caption: string, flags: int32): int32;
};

type PUBLIC_API = {
    __native: NATIVE_API;
    MESSAGE_BOX: MESSAGE_BOX;
    WIN_KEYS: WIN_KEYS;
    WIN_MODIFIERS: WIN_MODIFIERS;
    KEY_NAMES: KEY_NAMES;
    get FAIL_SAFE(): boolean;
    set FAIL_SAFE(v);
    get PAUSE(): number;
    set PAUSE(v);
    mouse: {
        get position(): {
            get x(): number;
            get y(): number;
            set x(v);
            set y(v);
        };
        set position(v: {
            x: number;
            y: number;
        });
        get x(): number;
        get y(): number;
        set x(v);
        set y(v);
        setPosition(v: {
            x: number;
            y: number;
        }): void;
        getPosition(point: true): {
            get x(): number;
            get y(): number;
            set x(v);
            set y(v);
        },
        getPosition(point?: boolean): {
            get x(): number;
            get y(): number;
            set x(v: never);
            set y(v: never);
        },
        moveTo(x: number, y: number, duration?: number, tween?: Function, deltaTime?: number): void;
        moveRel(dx: number, dy: number, duration?: number, tween?: Function, deltaTime?: number): void;
        dragTo(x: number, y: number, button?: Buttons[number], duration?: number, tween?: Function, deltaTime?: number): void;
        dragRel(x: number, y: number, button?: Buttons[number], duration?: number, tween?: Function, deltaTime?: number): void;
        get isSwapped(): boolean;
        down(button?: Buttons[number]): void;
        up(button?: Buttons[number]): void;
        click(button?: Buttons[number]): void;
        scroll(x?: number, y?: number): void;
    },
    keyboard: {
        press(...keys: KEY_NAMES[]): void;
        down(...keys: KEY_NAMES[]): void;
        up(...keys: KEY_NAMES[]): void;
        write(...texts: string[]): void;
        hotkey(...keys: KEY_NAMES[]): void;
    },
    screen: {
        get size(): {
            width: number;
            height: number;
        };
        get width(): number;
        get height(): number;
        set width(v: never);
        set height(v: never);
        includes(x: number, y: number): boolean;
        contains(x: number, y: number): boolean;
    },
    MessageBox: typeof MessageBox;
    PromptBox: typeof PromptBox;
    alert(text: string, title?: string): MESSAGE_BOX["RESPONSES"][keyof MESSAGE_BOX["RESPONSES"]];
    confirm(text: string, title?: string): boolean;
};

declare const __: PUBLIC_API;
export = __;