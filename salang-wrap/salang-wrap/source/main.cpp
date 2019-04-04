#include <stdio.h>
#include <string>
#include <Windows.h>

#include "BridgeWin.h"


int main(int argc, char *argv[]) {

  BridgeWin bridge(L"window", 1366, 768);
  bridge.startWindowThread();

  while (bridge.isExistWindowThread()) {
    // ここに更新処理
    Sleep(1);
  }
}
