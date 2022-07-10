# qmk-keymaps
Repo of my QMK-compatible keymaps

There should be a top-level directory for each keymap containing:
- (required) `KEYBOARD`
  - Containing one line with the keyboard to be passed to QMK's -kb flag
- (required) `keymap.c`
- (optional) `conditional/`
  - If there is any code that should only be linked based on a flag given to the
    build script, then it should be placed under this directory, in a nested
    directory with the same name as the flag gating whether or not it will be
    linked, in another nested directory named with the true/false value of the
    flag. Note that the default will be false.
- (optional) any other source files to include in the build

To build the firmware, provide the name of the top-level directory to the build
script (e.g. `python build.py corne`), and the `*.hex` file will be generated
in the project root.
