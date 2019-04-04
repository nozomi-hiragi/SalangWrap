/**
 * @file BridgeWin.cpp
 * @brief Windows用のなにか？
 * @author nozomi hiragi
 * @date 2019/04/05
 * Copyright (C) 2019 nozomi hiragi, Inc. All rights reserved.
 */
#include "BridgeWin.h"

/**
 * Processing message
 */
LRESULT BridgeWin::_processingMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_DESTROY: {
    PostQuitMessage(0);
  } break;

  case WM_SIZE: {
    UINT width = LOWORD(lParam);
    UINT height = HIWORD(lParam);
    // ビューポート変える
  } break;

  case WM_KEYDOWN: {
    // ここで入力もらって送るって方法もあるが....
  } break;

  case WM_CLOSE: {
    // アプリに終わり処理送る？
  }

  default:
    return DefWindowProc(_hwnd, uMsg, wParam, lParam);
    break;
  }

  return 0;
}

/**
 * Create window
 */
void BridgeWin::createWindow() {

  const std::string window_class_name(_app_name + "WindowClass");
  _hinstance = GetModuleHandle(nullptr);

  WNDCLASSEX window_class = {};
  window_class.cbSize = sizeof(WNDCLASSEX);
  window_class.style = CS_HREDRAW | CS_VREDRAW;
  window_class.lpfnWndProc = _windowProcedure;
  window_class.hInstance = _hinstance;
  window_class.lpszClassName = window_class_name.c_str();
  RegisterClassEx(&window_class);

  const DWORD win_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE | WS_OVERLAPPEDWINDOW;

  RECT win_rect = { 0, 0, _window_width, _window_height };
  AdjustWindowRect(&win_rect, win_style, false);

  _hwnd = CreateWindowEx(
    WS_EX_APPWINDOW,
    window_class_name.c_str(),
    _app_name.c_str(),
    win_style,
    0,
    0,
    win_rect.right - win_rect.left,
    win_rect.bottom - win_rect.top,
    nullptr,
    nullptr,
    _hinstance,
    nullptr);

  SetForegroundWindow(_hwnd);
  SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)this);
}

/**
 * Destroy window
 */
void BridgeWin::destroyWindow() {
  DestroyWindow(_hwnd);
}

/**
 * Process system message
 * return quit : true
 */
bool BridgeWin::processSystemMessage() {
  MSG msg;
  while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
    if (msg.message == WM_QUIT) {
      return true;
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return false;
}

/**
 * Start window thread
 */
void BridgeWin::startWindowThread() {
  if (_window_thread.joinable()) {
    return;
  }
  _window_thread = std::thread([this]() {
    _window_thread_end_flag = false;
    createWindow();
    while (!processSystemMessage()) {
      if (_window_thread_end_flag) {
        PostQuitMessage(0);
      }
      Sleep(1);
    }
    destroyWindow();
    _window_thread_end_flag = true;
  });
}

/**
 * End window thread
 */
void BridgeWin::endWindowThread() {
  if (_window_thread.joinable()) {
    _window_thread_end_flag = true;
    _window_thread.join();
  }
}
