#include <stdio.h>
#include <string>
#include <Windows.h>

#include "BridgeWin.h"


int main(int argc, char *argv[]) {

  BridgeWin bridge("window", 1366, 768);
  bridge.createWindow();

  while (!bridge.processSystemMessage()) {
    // ここに更新処理
  }

  bridge.destroyWindow();
}
