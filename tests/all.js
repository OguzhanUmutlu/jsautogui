const { keyboard } = require("..");
const { mouse, screen } = require("../index");
const wait = (t = 5) => new Promise(r => setTimeout(r, t * 1000));

(async () => {
    process.stdin.resume();
    process.stdin.setRawMode(true);
    console.log("Do not touch anything on your keyboard or move your mouse until the experiment ends.");
    console.log("Experiment starts in 5 seconds...");

    await wait();
    mouse.click("left");
    console.log("Left clicked.");
    await wait();

    mouse.click("right");
    console.log("Right clicked.");

    await wait();
    mouse.click("middle");
    console.log("Middle clicked.");

    await wait();
    mouse.down("left");
    console.log("Right down.");

    await wait();
    mouse.up("left");
    console.log("Right up.");

    await wait();
    const { width, height } = screen.size;
    console.log("Screen size is " + width + "X" + height);

    await wait();
    mouse.moveTo(Math.floor(width / 2), Math.floor(height / 2));
    console.log("Your mouse should now be centered.");

    await wait();
    mouse.dragRel(50, 50, "left");
    console.log("Mouse has been dragged(while the mouse is pressing down) 12 pixels to the right bottom corner.");

    await wait();
    console.log("Mouse is now at: " + mouse.x + ", " + mouse.y);
    console.log("Mouse functions are now done! Congrats!");

    await wait();
    keyboard.press("a");
    console.log("\nYou should see an 'a' key above this sentence. (You typed it)");

    await wait();
    keyboard.down("a");
    console.log("\nNow it should spam 'a's because it's pressed down and not back to up.");

    await wait();
    keyboard.up("a");
    console.log("\n'a's should now have stopped");

    await wait();
    keyboard.write("Hello, world!");
    console.log("\nYou should now see a 'Hello, world!' text above this sentence. (You typed it)");

    await wait();
    keyboard.hotkey("control", "a");
    keyboard.hotkey("control", "c");
    keyboard.hotkey("control", "v");
    keyboard.hotkey("control", "v");

    console.log("\nYou should now have pasted the whole terminal input back to here.");

    console.log("Everything is checked!");
    process.exit();
})();