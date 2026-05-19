#include "globals.h"

#include "ui.h"
#include "login.h"
#include "admin.h"
#include "user.h"
#include "inventory.h"



std::vector<Inventaris> dataInventaris;

User adminUser = {
    "admin",
    "123"
};

std::string currentRole = "";
std::string alertMsg = "";

bool alertSuccess = false;

int alertTimer = 0;

int activeField = -1;

int currentScreen = SCREEN_LOGIN;
int currentPanel = PANEL_A_SETUJUI;


int selRole = -1;

int loginAttempts = 0;

int searchResultIdx = -1;

std::string searchMsg = "";


char inputUsername[64] = "";
char inputPassword[64] = "";

char inputNama[128] = "";
char inputJumlah[16] = "";
char inputId[16] = "";
char inputCabangSel[32] = "TNI_AD";



Color C_BG      = GetColor(0x020B18FF);
Color C_CARD    = GetColor(0x08182AFF);
Color C_CARD2   = GetColor(0x10243DFF);
Color C_BORDER  = GetColor(0x1E4976FF);

Color C_TEXT    = RAYWHITE;
Color C_MUTED   = GRAY;

Color C_ACCENT  = GetColor(0x4DA3FFFF);
Color C_ACCENT2 = GetColor(0x2B6CB0FF);

Color C_SUCCESS = GREEN;
Color C_DANGER  = RED;
Color C_WARN    = ORANGE;
Color C_INFO    = SKYBLUE;

Color C_INPUT   = GetColor(0x0D2035FF);

Color C_BTN = GetColor(0x16314EFF);

Color C_BTN_HOV = GetColor(0x1E4976FF);

int main() {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
        InitWindow(1100, 700, "Sistem Inventaris Kementerian / TNI");
        SetTargetFPS(60);

        dataInventaris = { };

        while (!WindowShouldClose()) {

            BeginDrawing();

            ClearBackground(C_BG);

            if(currentScreen == SCREEN_LOGIN){

                DrawLoginScreen();
            }

            else{

                DrawTopbar();

                DrawSidebar();

                switch(currentPanel){


                    case PANEL_A_SETUJUI:
                        DrawSetujui();
                        break;

                    case PANEL_A_BELI:
                        DrawBeli();
                        break;

                    case PANEL_A_TAMBAH:
                        DrawTambahAdmin();
                        break;

                    case PANEL_A_HAPUS:
                        DrawHapusAdmin();
                        break;

                    case PANEL_A_SEMUA:
                        DrawSemuaData();
                        break;

                    case PANEL_A_SORT:
                        DrawSorting();
                        break;

                    case PANEL_A_SEARCH:
                        DrawSearching();
                        break;

                    case PANEL_U_LIHAT:
                        DrawUserLihat();
                        break;

                    case PANEL_U_TAMBAH:
                        DrawTambahUser();
                        break;

                    case PANEL_U_UBAH:
                        DrawUbahUser();
                        break;

                    case PANEL_U_HAPUS:
                        DrawHapusUser();
                        break;
                }
            }

            EndDrawing();
        }

        CloseWindow();
        return 0;
    }