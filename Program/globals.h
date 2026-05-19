#pragma once

#include "raylib.h"

#include <vector>
#include <string>
#include <functional>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>

// =====================================================
// STRUCT
// =====================================================

struct User {

    std::string username;
    std::string password;
};

struct Inventaris {

    int idBarang;
    std::string namaBarang;
    int jumlahBarang;
    std::string cabangTNI;
    std::string status;
};

// =====================================================
// GLOBAL VARIABLE
// =====================================================

extern std::vector<Inventaris> dataInventaris;

extern User adminUser;

extern std::string currentRole;
extern std::string alertMsg;
extern std::string searchMsg;

extern bool alertSuccess;

extern int alertTimer;
extern int activeField;
extern int currentScreen;
extern int currentPanel;
extern int selRole;
extern int loginAttempts;
extern int searchResultIdx;

// =====================================================
// INPUT BUFFER
// =====================================================

extern char inputUsername[64];
extern char inputPassword[64];

extern char inputNama[128];
extern char inputJumlah[16];
extern char inputId[16];

extern char inputCabangSel[32];

// =====================================================
// COLORS
// =====================================================

extern Color C_BG;
extern Color C_CARD;
extern Color C_CARD2;
extern Color C_BORDER;

extern Color C_TEXT;
extern Color C_MUTED;

extern Color C_ACCENT;
extern Color C_ACCENT2;

extern Color C_SUCCESS;
extern Color C_DANGER;
extern Color C_WARN;
extern Color C_INFO;

extern Color C_INPUT;

extern Color C_BTN;
extern Color C_BTN_HOV;

// =====================================================
// SCREEN
// =====================================================

#define SCREEN_LOGIN 0
#define SCREEN_MAIN  1

// =====================================================
// ADMIN PANEL
// =====================================================


#define PANEL_A_SETUJUI 1
#define PANEL_A_BELI 2
#define PANEL_A_TAMBAH 3
#define PANEL_A_HAPUS 4
#define PANEL_A_SEMUA 5
#define PANEL_A_SORT 6
#define PANEL_A_SEARCH 7

// =====================================================
// USER PANEL
// =====================================================

#define PANEL_U_LIHAT 20
#define PANEL_U_TAMBAH 21
#define PANEL_U_UBAH 23
#define PANEL_U_HAPUS 24

// =====================================================
// LAYOUT
// =====================================================

#define TOPBAR_H 50
#define SIDEBAR_W 190

#define CONTENT_X (SIDEBAR_W)
#define CONTENT_Y (TOPBAR_H)