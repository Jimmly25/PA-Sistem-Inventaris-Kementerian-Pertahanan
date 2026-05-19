#pragma once

#include "globals.h"

// =====================================================
// BASIC UI
// =====================================================

void DrawRect(
    int x,
    int y,
    int w,
    int h,
    Color c
);

void DrawRectBorder(
    int x,
    int y,
    int w,
    int h,
    Color bg,
    Color border
);

// =====================================================
// BUTTON
// =====================================================

bool DrawButton(
    int x,
    int y,
    int w,
    int h,
    const char* text,
    Color bg,
    Color fg,
    int fs = 14
);

// =====================================================
// LABEL
// =====================================================

void DrawLabel(
    int x,
    int y,
    const char* text,
    Color col,
    int size
);

// =====================================================
// TEXTBOX
// =====================================================

void DrawTextBox(
    int x,
    int y,
    int w,
    int h,
    char* buf,
    int bufSize,
    int fieldId,
    const char* placeholder = ""
);

// =====================================================
// TABLE
// =====================================================

void DrawTable(

    int x,
    int y,

    int w,
    int h,

    const std::vector<Inventaris>& data,

    bool showBtn1 = false,

    const char* btn1Text = "",

    std::function<void(int)> onBtn1 = nullptr,

    bool showBtn2 = false,

    const char* btn2Text = "",

    std::function<void(int)> onBtn2 = nullptr
);

void DrawTableCabang(

    int x,
    int y,

    int w,
    int h,

    const std::vector<Inventaris>& data,

    bool showBtn1 = false,

    const char* btn1Text = "",

    std::function<void(int)> onBtn1 = nullptr,

    bool showBtn2 = false,

    const char* btn2Text = "",

    std::function<void(int)> onBtn2 = nullptr
);

// =====================================================
// CARD
// =====================================================

void DrawStatCard(
    int x,
    int y,
    int w,
    int h,
    const char* title,
    const char* value,
    Color accent
);

// =====================================================
// LAYOUT
// =====================================================

void DrawTopbar();

void DrawSidebar();