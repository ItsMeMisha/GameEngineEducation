#include "KeyLayout.h"

#include "../../../SDKs/inih/include/ini.h"
#include <string.h>
#include <cassert>

int ConfigHandler(void* user, const char* section, const char* name, const char* value)
{
  KeyLayout* layout = (KeyLayout*)user;

  if (strcmp(section, "keyboard") != 0) {
    return 0;
  }

  if (strcmp(name, "GoLeft") == 0) {
    layout->mToLeft = value[0];
  }
  else if (strcmp(name, "GoRight") == 0) {
    layout->mToRight = value[0];
  }
  else if (strcmp(name, "GoUp") == 0) {
    layout->mUp = value[0];
  }
  else if (strcmp(name, "GoDown") == 0) {
    layout->mDown = value[0];
  }
  else {
    return 0;
  }

  return 1;
}

void KeyLayout::ParseConfig()
{
  if (int error = ini_parse("keyconfig.ini", ConfigHandler, this)) {
    assert(0);
  }
}
