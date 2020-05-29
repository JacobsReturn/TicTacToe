#pragma once
const char* const ESC = "\x1b";
const char* const CSI = "\x1b[";

const char* const TITLE = "\x1b[5;20H";
const char* const INDENT = "\x1b[5C";
const char* const YELLOW = "\x1b[93m";
const char* const MAGENTA = "\x1b[95m";
const char* const RED = "\x1b[91m";
const char* const BLUE = "\x1b[94m";
const char* const WHITE = "\x1b[97m";
const char* const GREEN = "\x1b[92m";
const char* const RESET_COLOR = "\x1b[0m";
const char* const EXTRA_OUTPUT_POS = "\x1b[21;6H";
const char* const INVENTORY_OUTPUT_POS = "\x1b[24;6H";

const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;
const int SPACE = 32;
const int R = 123;

const char* RESET_COLOUR = "\x1b[0m";
const char* SAVE_CURSOR_POS = "\x1b[s";
const char* RESTORE_CURSOR_POS = "\x1b[u";

const int EMPTY = 0;
const int FULL_X = EMPTY + 1;
const int FULL_O = FULL_X + 1;

const int BOARD_WIDTH = 3;
const int BOARD_HEIGHT = 3;