// @ts-ignore
import __native from "./build/Release/jsautogui.node";
import * as tween from "jstweening";
import {linear} from "jstweening";

const native = <NATIVE_API>__native;

type int32 = number;

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
    keys_press(key_data: Uint32Array): boolean;
};

const modifiers: string[] = [
    "accept", "add", "alt", "altleft", "altright", "apps", "backspace",
    "browserback", "browserfavorites", "browserforward", "browserhome",
    "browserrefresh", "browsersearch", "browserstop", "capslock", "clear",
    "convert", "ctrl", "ctrlleft", "ctrlright", "decimal", "del", "delete",
    "divide", "down", "end", "enter", "esc", "escape", "execute", "f1", "f10",
    "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19", "f2", "f20",
    "f21", "f22", "f23", "f24", "f3", "f4", "f5", "f6", "f7", "f8", "f9",
    "final", "hanguel", "hangul", "hanja", "help", "home", "insert", "junja",
    "kana", "kanji", "launchapp1", "launchapp2", "launchmail",
    "launchmediaselect", "left", "modechange", "multiply", "nexttrack",
    "nonconvert", "num0", "num1", "num2", "num3", "num4", "num5", "num6",
    "num7", "num8", "num9", "numlock", "pagedown", "pageup", "pause", "pgdn",
    "pgup", "playpause", "prevtrack", "print", "printscreen", "prntscrn",
    "prtsc", "prtscr", "return", "right", "scrolllock", "select", "separator",
    "shift", "shiftleft", "shiftright", "sleep", "space", "stop", "subtract", "tab",
    "up", "volumedown", "volumemute", "volumeup", "win", "winleft", "winright", "yen",
    "command", "option", "optionleft", "optionright"
] as const;

type TweenFunction = (t: number) => number;

type AllMouseButtons = "primary" | "secondary" | "left" | "right" | "middle";

const mouseButtons = ["left", "right", "middle"] as const;

const INT32_MIN = -2147483648;
const INT32_MAX = 2147483647;

function eType(a: any, t: string, n: string): void {
    if (typeof a !== t) throw new Error(`Expected ${n} to be a ${t}, instead got: ${typeof a}`);
}

function eInt32(a: number, n: string): void {
    eSize(a, INT32_MIN, INT32_MAX, n);
    if (a !== Math.floor(a)) throw new Error(`Expected ${n} to be an int32, instead got a float/double.`);
}

function eSize(a: number, min: number, max: number, n: string): void {
    eType(a, "number", n);
    if (a < min || a > max) throw new Error(`Expected ${n} to be between (${min}, ${max}).`);
}

function perm(s: string): never {
    throw new Error(`Couldn't ${s}, is the program lacking some permissions?`);
}

type Interval = ReturnType<typeof setInterval>;

function applyMovement(x1: number, y1: number, x2: number, y2: number, duration: number, tween: TweenFunction) {
    let interval = <Interval>null!;
    const prom = new Promise<void>((resolve) => {
        let t = 0;
        let last = performance.now();
        interval = setInterval(() => {
            const now = performance.now();
            t += now - last;
            last = now;
            if (t >= duration) {
                native.set_mouse_pos(x2, y2);
                clearInterval(interval);
                resolve();
            } else {
                const rt = t / duration;
                const tw = tween(rt);
                API.mouse.setPosition(x1 + (x2 - x1) * tw, y1 + (y2 - y1) * tw);
            }
        });
    });
    return {
        wait: () => prom,
        cancel: () => interval && clearInterval(interval)
    };
}

enum KeyPressMode {
    ASCII = 0,
    UNICODE = 1,
    SPECIAL = 2
}

function encodeKeyPress(key: number, mode: KeyPressMode, down: boolean, up: boolean): number {
    return key | ((mode & 0x3) << 16) | (down ? (1 << 19) : 0) | (up ? (1 << 20) : 0);
}

function encodeKeyPresses(keys: string[], down: boolean, up: boolean): number[] {
    return keys.map(k => {
        if (typeof k !== "string") throw new Error(`Expected key to be a string, instead got: ${typeof k}`);
        if (modifiers.includes(k)) {
            return encodeKeyPress(k as unknown as number, KeyPressMode.SPECIAL, down, up);
        } else if (k.length === 1) {
            return encodeKeyPress(k.charCodeAt(0), KeyPressMode.ASCII, down, up);
        } else if (k.length <= 4) {
            const c1 = k.charCodeAt(0) || 0;
            const c2 = k.charCodeAt(1) || 0;
            const c3 = k.charCodeAt(2) || 0;
            const c4 = k.charCodeAt(3) || 0;
            const encoded32 = (c1 << 24) | (c2 << 16) | (c3 << 8) | c4;
            return encodeKeyPress(encoded32, KeyPressMode.UNICODE, down, up);
        }
        throw new Error(`Unsupported key format: ${k}`);
    });
}

function keysPress(keys: string[], down: boolean, up: boolean): void {
    native.keys_press(new Uint32Array(encodeKeyPresses(keys, down, up)));
}

function hotkeyPress(keys: string[]): void {
    native.keys_press(new Uint32Array([
        ...encodeKeyPresses(keys, true, false),
        ...encodeKeyPresses(keys, false, true)
    ]));
}

function xyFix(x: number, y: number, min = 0) {
    x = Math.min(INT32_MAX, Math.max(min, Math.round(x)));
    y = Math.min(INT32_MAX, Math.max(min, Math.round(y)));
    return [x, y];
}

let callPause = 0;
let failSafe = false;
let failSafeInterval = <Interval>null!;

const API = {
    __native_do_not_use_this_it_might_crash_natively_if_misused: native,
    get FAIL_SAFE() {
        return failSafe;
    },
    set FAIL_SAFE(v) {
        eType(v, "boolean", "FAIL_SAFE");
        if (v === failSafe) return;
        clearInterval(failSafeInterval);
        if (v) {
            failSafeInterval = setInterval(() => {
                const pos = native.get_mouse_pos();
                if (!pos) return;
                if (pos.x < 3 && pos.y < 3) throw new Error("Failed safely. This behavior can be disabled by setting jsautogui.FAIL_SAFE to false.");
            }, 100);
            failSafe = true;
        } else {
            failSafe = false;
            failSafeInterval = <Interval>null!;
        }
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
            if (!native.set_mouse_x(v)) perm("set the x position of the mouse");
        },
        get y() {
            return this.position.y;
        },
        set y(v) {
            eInt32(v, "mouse.position.y");
            eSize(v, 0, INT32_MAX, "mouse.position.y");
            if (!native.set_mouse_y(v)) perm("set the y position of the mouse");
        },
        getPosition() {
            const pos = native.get_mouse_pos();
            if (!pos) perm("find the position of the mouse");
            const obj = {};
            Object.defineProperties(obj, {
                x: {
                    get: () => pos.x,
                    set: v => this.x = pos.x = v
                },
                y: {
                    get: () => pos.y,
                    set: v => this.y = pos.y = v
                }
            });
            return <{ x: number, y: number }>obj;
        },
        setPosition(x: number, y: number) {
            [x, y] = xyFix(x, y);
            if (!native.set_mouse_pos(x, y)) return perm("set the position of the mouse");
        },
        moveTo(x: number, y: number, duration = 0, tween: TweenFunction = linear) {
            [x, y] = xyFix(x, y);
            eInt32(duration, "duration");
            if (duration === 0) {
                this.setPosition(x, y);
                return {wait: () => null, cancel: () => null};
            }
            eType(tween, "function", "mouse.moveTo.tween");
            const start = native.get_mouse_pos();
            return applyMovement(start.x, start.y, x, y, duration, tween);
        },
        moveRel(dx: number, dy: number, duration = 0, tween: TweenFunction = linear) {
            [dx, dy] = xyFix(dx, dy, 0);
            eInt32(duration, "duration");
            if (duration === 0) {
                native.set_mouse_pos_rel(dx, dy) || perm("set the position of the mouse");
                return {wait: () => null, cancel: () => null};
            }
            const start = native.get_mouse_pos();
            const x0 = start.x, y0 = start.y;
            return applyMovement(x0, y0, x0 + dx, y0 + dx, duration, tween);
        },
        dragTo(x: number, y: number, button: AllMouseButtons = "primary", duration = 0, tween: TweenFunction = linear) {
            [x, y] = xyFix(x, y);
            this.down(button);
            const r = this.moveTo(x, y, duration, tween);
            if (r instanceof Promise) return r.then(() => this.up(button));
            this.up(button);
        },
        dragRel(dx: number, dy: number, button: AllMouseButtons = "primary", duration = 0, tween = linear) {
            [dx, dy] = xyFix(dx, dy, 0);
            this.down(button);
            const r = this.moveRel(dx, dy, duration, tween);
            if (r instanceof Promise) return r.then(() => this.up(button));
            this.up(button);
        },
        get isSwapped() {
            return native.is_mouse_swapped();
        },
        down(button: AllMouseButtons = "primary") {
            if (button === "primary") button = this.isSwapped ? "right" : "left";
            else if (button === "secondary") button = this.isSwapped ? "left" : "right";
            else if (mouseButtons.includes(button)) return (native as any)["mouse_" + button + "_down"]() || perm("press a button in mouse");
            throw new Error("Expected the button argument to be 'right', 'left', 'middle', 'primary', 'secondary'. Got: " + button);
        },
        up(button: AllMouseButtons = "primary") {
            if (button === "primary") button = this.isSwapped ? "right" : "left";
            if (button === "secondary") button = this.isSwapped ? "left" : "right";
            if (mouseButtons.includes(button)) return (native as any)["mouse_" + button + "_up"]() || perm("release a button in mouse");
            throw new Error("Expected the button argument to be 'right', 'left', 'middle', 'primary', 'secondary'. Got: " + button);
        },
        click(button: AllMouseButtons = "primary") {
            if (button === "primary") button = this.isSwapped ? "right" : "left";
            if (button === "secondary") button = this.isSwapped ? "left" : "right";
            if (mouseButtons.includes(button)) return (native as any)["click_" + button]() || perm("click a button in mouse");
            throw new Error("Expected the button argument to be 'right', 'left', 'middle', 'primary', 'secondary'. Got: " + button);
        },
        scroll(y = 0, x = 0) {
            [x, y] = xyFix(x, y, INT32_MIN);
            if (!native.mouse_scroll(x, y)) perm("scroll the wheel of mouse");
        },
        hscroll(x = 0, y = 0) {
            [x, y] = xyFix(x, y, INT32_MIN);
            if (!native.mouse_scroll(x, y)) perm("scroll the wheel of mouse");
        }
    },
    keyboard: {
        press(...keys: string[]) {
            keysPress(keys, true, true);
        },
        down(...keys: string[]) {
            keysPress(keys, true, false);
        },
        up(...keys: string[]) {
            keysPress(keys, false, true);
        },
        write(...texts: string[]) {
            for (const text of texts) {
                for (let i = 0; i < text.length; i++) this.press(text[i]);
            }
        },
        hotkey(...keys: string[]) {
            hotkeyPress(keys);
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
        includes(x: number, y: number) {
            eInt32(x, "x");
            eInt32(y, "y");
            const size = native.get_screen_size();
            return x >= 0 && y >= 0 && x < size.width && y < size.height;
        },
        contains(x: number, y: number) {
            return this.includes(x, y);
        }
    }
};

Object.assign(API, tween);

export = API as typeof API & typeof tween;