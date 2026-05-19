#include "login.h"

#include "globals.h"
#include "ui.h"
#include "inventory.h"

    void DrawLoginScreen() {

        int W = GetScreenWidth(),
            H = GetScreenHeight();

        DrawRect(
            0,
            0,
            W,
            H,
            C_BG
        );

        Color hud =
        Fade(C_ACCENT,0.6f);

        DrawLine(
            30,
            40,

            120,
            40,

            hud
        );

        DrawLine(
            30,
            40,

            30,
            120,

            hud
        );

        DrawLine(
            GetScreenWidth()-30,
            40,

            GetScreenWidth()-120,
            40,

            hud
        );

        DrawLine(
            GetScreenWidth()-30,
            40,

            GetScreenWidth()-30,
            120,

            hud
        );

        DrawLine(
            30,
            GetScreenHeight()-40,

            120,
            GetScreenHeight()-40,

            hud
        );

        DrawLine(
            30,
            GetScreenHeight()-40,

            30,
            GetScreenHeight()-120,

            hud
        );

        DrawLine(
            GetScreenWidth()-30,
            GetScreenHeight()-40,

            GetScreenWidth()-120,
            GetScreenHeight()-40,

            hud
        );

        DrawLine(
            GetScreenWidth()-30,
            GetScreenHeight()-40,

            GetScreenWidth()-30,
            GetScreenHeight()-120,

            hud
        );

        for(int i = 0;
            i < 40;
            i++)
        {
            DrawCircle(

                (i * 97)
                % GetScreenWidth(),

                (
                    (int)(GetTime()*20)
                    + i * 57
                )

                % GetScreenHeight(),

                1.5f,

                Fade(C_ACCENT,0.3f)
            );
        }

        int bw = 380;
        

        int bh =
        selRole == 0 ?

        560

        :

        460;

        int bx =
        W/2 - bw/2,

        by =
        H/2 - bh/2;

        DrawRectangle(
            bx - 4,
            by - 4,

            bw + 8,
            bh + 8,

            Fade(C_ACCENT,0.15f)
        );

        DrawRectBorder(
            bx,
            by,
            bw,
            bh,

            C_CARD,
            C_BORDER
        );

        DrawText(
            "SISTEM INVENTARIS",

            bx+bw/2 -
            MeasureText(
                "SISTEM INVENTARIS",
                14
            )/2,

            by+24,

            14,

            C_ACCENT
        );

        DrawText(
            "KEMENTERIAN / TNI",

            bx+bw/2 -
            MeasureText(
                "KEMENTERIAN / TNI",
                11
            )/2,

            by+44,

            11,

            Fade(C_MUTED,0.7f)
        );

        DrawRect(
            bx+40,
            by+68,

            bw-80,

            1,

            C_BORDER
        );

        DrawText(
            "Pilih Role Login:",
            bx+20,
            by+82,

            12,

            C_MUTED
        );

        const char* roles[] = {
            "Admin",
            "TNI AD",
            "TNI AU",
            "TNI AL"
        };

        const char* subs[] = {
            "Pusat",
            "Angkatan Darat",
            "Angkatan Udara",
            "Angkatan Laut"
        };

        int rw = 160,
            rh = 64,
            gap = 10;

        int rx = bx+20,
            ry = by+100;

        for(int i = 0;
            i < 4;
            i++)
        {
            int cx =
            rx + (i%2)*(rw+gap);

            int cy =
            ry + (i/2)*(rh+gap);

            bool sel =
            (selRole == i);

            Color bg =
            sel ?

            GetColor(0x1A3560FF)

            :

            C_CARD2;

            Color border =
            sel ?

            C_ACCENT

            :

            C_BORDER;

            DrawRectangle(
                cx,
                cy,
                rw,
                rh,
                bg
            );

            DrawRectangleLinesEx(
                {
                    (float)cx,
                    (float)cy,
                    (float)rw,
                    (float)rh
                },

                sel ? 2.f : 1.f,

                border
            );

            DrawText(
                roles[i],

                cx+rw/2 -
                MeasureText(
                    roles[i],
                    14
                )/2,

                cy+14,

                14,

                sel ?
                C_ACCENT :
                C_TEXT
            );

            DrawText(
                subs[i],

                cx+rw/2 -
                MeasureText(
                    subs[i],
                    10
                )/2,

                cy+34,

                10,

                Fade(C_MUTED,0.7f)
            );

            if(IsMouseButtonPressed(
                MOUSE_LEFT_BUTTON))
            {
                Vector2 m =
                GetMousePosition();

                if(m.x>=cx &&
                m.x<=cx+rw &&
                m.y>=cy &&
                m.y<=cy+rh)

                    selRole = i;
            }
        }

        int fy =
        ry + 2*(rh+gap) + 16;

        if(selRole == 0){

            DrawLabel(
                bx+20,
                fy,

                "USERNAME",

                C_MUTED,
                10
            );

            fy += 14;

            DrawTextBox(
                bx+20,
                fy,

                bw-40,

                34,

                inputUsername,
                64,

                1,

                "Masukkan Username"
            );

            fy += 44;

            DrawLabel(
                bx+20,
                fy,

                "PASSWORD",

                C_MUTED,
                10
            );

            fy += 14;

            DrawTextBox(
                bx+20,
                fy,

                bw-40,

                34,

                inputPassword,
                64,

                2,

                "Masukkan Password"
            );

            fy += 52;
        }

        else{

            fy += 16;
        }

        if(alertTimer > 0){

            Color abg =
            alertSuccess ?

            GetColor(0x0D1A05FF)

            :

            GetColor(0x200505FF);

            Color acol =
            alertSuccess ?

            C_SUCCESS :

            C_DANGER;

            DrawRectangle(
                bx+20,
                fy-36,

                bw-40,

                28,

                abg
            );

            DrawRectangleLinesEx(
                {
                    (float)(bx+20),
                    (float)(fy-36),

                    (float)(bw-40),

                    28.f
                },

                1,

                acol
            );

            DrawText(
                alertMsg.c_str(),

                bx+28,
                fy-30,

                12,

                acol
            );

            alertTimer--;

            fy += 4;
        }

        if(DrawButton(
            bx+20,
            fy,

            bw-40,

            38,

            "MASUK",

            C_ACCENT2,

            C_TEXT,

            14))
        {
            if(selRole < 0){

                showAlert(
                    "Pilih role terlebih dahulu!",
                    false
                );

                return;
            }

            if(selRole == 0){

                loginAttempts++;

                if(std::string(inputUsername)
                != adminUser.username ||

                std::string(inputPassword)
                != adminUser.password)
                {
                    if(loginAttempts >= 3){

                        showAlert(
                            "Terlalu banyak percobaan! Program akan ditutup.",
                            false
                        );

                        EndDrawing();

                        CloseWindow();

                        exit(0);
                    }

                    else{

                        showAlert(
                            "Username/password salah! Sisa: " +

                            std::to_string(
                                3 - loginAttempts
                            ),

                            false
                        );
                    }

                    return;
                }

                loginAttempts = 0;

                currentRole = "admin";
            }

            else{

                currentRole =

                (selRole==1)

                ?

                "TNI_AD"

                :

                (selRole==2)

                ?

                "TNI_AU"

                :

                "TNI_AL";
            }

            currentScreen =
            SCREEN_MAIN;

            currentPanel =

            (currentRole=="admin")

            ?

            PANEL_A_SETUJUI

            :

            PANEL_U_LIHAT;


            memset(
                inputUsername,
                0,
                sizeof(inputUsername)
            );

            memset(
                inputPassword,
                0,
                sizeof(inputPassword)
            );
        }

        if(DrawButton(

            bx + bw/2 - 110,
            fy + 55,

            220,
            42,

            "KELUAR PROGRAM",

            C_DANGER,
            C_TEXT,

            14))
        {
            CloseWindow();
        }
    }

    

