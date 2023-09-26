# JSAutoGui

> JSAutoGUI is an npm package for node.js. Inspired by pyautogui from python. (but noticably faster and better)

# How to contribute/fork/edit?

To alter the C++ codes this project has you have to include some libraries.

#### First start by cloning this project to your local machine by using this command line:

```git clone https://github.com/OguzhanUmutlu/jsautogui.git```

Which should create a `jsautogui` folder into the cd you are in, in your terminal.

#### For anything to work you will need to install Node.js: https://nodejs.org/en/download

#### Then install node-gyp for node's addon api to be integrated by using the following command file:

```
npm install -g node-gyp
```

I am using VSC for editing the C++ editing and Intellij for JS editing.

So the rest of the instructions will depend on VSC. (You can contribute to this README by adding more editor instructions!)

#### Install the `C/C++ Extension Pack` in the Extensions tab which is located in the left of the VSC editor.

Press `CTRL SHIFT P` in VSC to open up the command palette then type in `C/C++: Edit Configurations (JSON)` and press `Enter`.

Now you should have the configuration file created at `.vscode/c_cpp_properties.json`.

Now you can add the required paths by putting them in the `includePath`.

Now since you have `node` installed you should have the node api files too.

Its location is(usually):
- For Windows: `C:\Program Files\nodejs\include\node` OR `C:\Users\HP\AppData\Local\node-gyp\Cache\19.8.1\include\node` (replace 19.8.1 with your node version)
- For Linux: `/usr/include/node`
- For macOS: `/usr/local/include/node`

Put the path into the `includePath` list and let's continue.

You will also need the windows and linux(x11) header files. (You can contribute to this README by adding the instructions to install the remaining includePaths!)