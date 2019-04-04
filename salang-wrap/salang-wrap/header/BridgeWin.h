/**
 * @file BridgeWin.h
 * @brief WindowsópÇÃÇ»Ç…Ç©ÅH
 * @author nozomi hiragi
 * @date 2019/04/05
 * Copyright (C) 2019 nozomi hiragi, Inc. All rights reserved.
 */
#pragma once
#ifndef BRIDGE_WIN_H
#define BRIDGE_WIN_H

#include <Windows.h>
#include <string>

class BridgeWin {
private:
  HWND _hwnd;
  HINSTANCE _hinstance;

  std::string _app_name;
  long _window_width;
  long _window_height;

  /**
   * Processing message
   */
  LRESULT _processingMessage(UINT uMsg, WPARAM wParam, LPARAM lParam); 

  /**
   * Window procedure
   */
  static LRESULT CALLBACK _windowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    BridgeWin* instance = reinterpret_cast<BridgeWin *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    if (instance != nullptr) {
      return instance->_processingMessage(uMsg, wParam, lParam);
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }

protected:
public:

  /**
   * Constructor
   */
  BridgeWin(const char* app_name, long width, long height) :
    _app_name(app_name),
    _window_width(width),
    _window_height(height) {
  }

  /**
   * Destructor
   */
  ~BridgeWin() { destroyWindow(); }

  /**
   * Create window
   */
  void createWindow();

  /**
   * Destroy window
   */
  void destroyWindow();

  /**
   * Process system message
   * return quit: true
   */
  bool processSystemMessage();
};

#endif BRIDGE_WIN_H
