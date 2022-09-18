#pragma once

class KeyLayout {
  friend int ConfigHandler(void*, const char*, const char*, const char*);
public:
  int GetLeft() { return mToLeft; };
  int GetRight() { return mToRight; };

  void ParseConfig();
private:
  int mToLeft = 0;
  int mToRight = 0;
};