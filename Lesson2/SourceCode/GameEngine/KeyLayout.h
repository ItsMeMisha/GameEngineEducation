#pragma once

class KeyLayout {
  friend int ConfigHandler(void*, const char*, const char*, const char*);
public:
  int GetLeft() { return mToLeft; };
  int GetRight() { return mToRight; };
  int GetUp() { return mUp; };
  int GetDown() { return mDown; };

  void ParseConfig();
private:
  int mToLeft = 0;
  int mToRight = 0;
  int mUp = 0;
  int mDown = 0;
};