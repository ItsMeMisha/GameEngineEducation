#pragma once

enum EActionKeys {
  LEFT = 0,
  RIGHT,
  UP,
  DOWN
};

class KeyLayout {
  friend int ConfigHandler(void*, const char*, const char*, const char*);
public:
  int GetKey(EActionKeys key) { return mKeysLayout[key]; }
  
  void ParseConfig();
private:
  int mKeysLayout[4] = {};
};