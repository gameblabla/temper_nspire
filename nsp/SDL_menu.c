#include "../common.h"

const char *control_config_string = "NSP           PC-Engine";
const u32 control_config_start_column = 64;
//const char *control_config_exit_string = "Press escape to return to the main menu";
const char *control_config_exit_string = "Press ESCAPE to return to the main menu";

const u32 platform_control_count = 12;
char *platform_control_names[MAX_CONTROLS] =
{
  "Up         ", "Down       ", "Left       ", "Right      ",
  "CTRL       ", "SHIFT      ", "VAR        ", "DEL        ",
  "7          ", "9          ", "TAB        ", "DOC        "
};

