#include "inventory.h"
#include "ui.h"

void DrawRect(

    int x,
    int y,

    int w,
    int h,

    Color c)
{
    DrawRectangle(
        x,
        y,
        w,
        h,
        c
    );
}

void DrawRectBorder(

    int x,
    int y,

    int w,
    int h,

    Color bg,

    Color border)
{
    DrawRectangle(
        x,
        y,
        w,
        h,
        bg
    );

    DrawRectangleLinesEx(

        {
            (float)x,
            (float)y,
            (float)w,
            (float)h
        },

        1,

        border
    );
}

bool DrawButton(

    int x,
    int y,

    int w,
    int h,

    const char* text,

    Color bg,
    Color fg,

    int fs)
{
    Vector2 m =
    GetMousePosition();

    bool hover =

    m.x >= x &&
    m.x <= x + w &&

    m.y >= y &&
    m.y <= y + h;

    Color finalBg =

    hover ?

    Fade(bg,0.85f)

    :

    bg;

    DrawRectangle(
        x,
        y,
        w,
        h,
        finalBg
    );

    DrawRectangleLinesEx(

        {
            (float)x,
            (float)y,
            (float)w,
            (float)h
        },

        hover ? 2.f : 1.f,

        C_BORDER
    );

    DrawText(

        text,

        x + w/2 -
        MeasureText(text,fs)/2,

        y + h/2 - fs/2,

        fs,

        fg
    );

    return
    hover &&
    IsMouseButtonPressed(
        MOUSE_LEFT_BUTTON
    );
}

void DrawLabel(

    int x,
    int y,

    const char* text,

    Color col,

    int size)
{
    DrawText(
        text,
        x,
        y,
        size,
        col
    );
}

void DrawTextBox(

    int x,
    int y,

    int w,
    int h,

    char* buf,

    int bufSize,

    int fieldId,

    const char* placeholder)
{
    bool active =
    (activeField == fieldId);

    Color border =
    active ?

    C_ACCENT

    :

    C_BORDER;

    DrawRectangle(
        x,
        y,
        w,
        h,
        C_INPUT
    );

    DrawRectangleLinesEx(

        {
            (float)x,
            (float)y,
            (float)w,
            (float)h
        },

        1,

        border
    );

    std::string display =
    std::string(buf);


    std::string showStr =

    (fieldId == 2)

    ?

    std::string(
        strlen(buf),
        '*'
    )

    :

    display;


    if(display.empty() && !active){

        DrawText(

            placeholder,

            x + 8,

            y + h/2 - 7,

            13,

            Fade(C_MUTED,0.5f)
        );
    }

    else{

        DrawText(

            showStr.c_str(),

            x + 8,

            y + h/2 - 7,

            13,

            C_TEXT
        );
    }


    if(active &&

    ((GetTime()*2) -
    (int)(GetTime()*2) < 1.0))
    {
        DrawText(

            "|",

            x + 8 +

            MeasureText(
                showStr.c_str(),
                13
            ),

            y + h/2 - 7,

            13,

            C_ACCENT
        );
    }


    if(IsMouseButtonPressed(
        MOUSE_LEFT_BUTTON))
    {
        Vector2 m =
        GetMousePosition();

        if(m.x >= x &&
        m.x <= x+w &&

        m.y >= y &&
        m.y <= y+h)
        {
            activeField =
            fieldId;
        }
    }


    if(active){

        int key =
        GetCharPressed();

        while(key > 0){

            int len =
            strlen(buf);

            if(len < bufSize - 1 &&

            key >= 32 &&
            key <= 126)
            {
                buf[len] =
                (char)key;

                buf[len + 1] =
                '\0';
            }

            key =
            GetCharPressed();
        }

        if(IsKeyPressed(
            KEY_BACKSPACE)
            &&
            strlen(buf) > 0)
        {
            buf[strlen(buf)-1] =
            '\0';
        }
    }
}

void DrawTable(

    int x,
    int y,

    int w,
    int h,

    const std::vector<Inventaris>& data,

    bool showBtn1,

    const char* btn1Text,

    std::function<void(int)> onBtn1,

    bool showBtn2,

    const char* btn2Text,

    std::function<void(int)> onBtn2)
{
    int rowH = 36;

    DrawRectangle(
        x,
        y,
        w,
        rowH,
        C_CARD
    );

    DrawRectangleLinesEx(

        {
            (float)x,
            (float)y,
            (float)w,
            (float)rowH
        },

        1,

        C_BORDER
    );

    DrawText(
        "ID",
        x + 12,
        y + 10,
        12,
        C_ACCENT
    );

    DrawText(
        "Nama Barang",
        x + 90,
        y + 10,
        12,
        C_ACCENT
    );


    DrawText(
        "Jumlah",
        x + 330,
        y + 10,
        12,
        C_ACCENT
    );

    DrawText(
        "Status",
        x + 460,
        y + 10,
        12,
        C_ACCENT
    );

    int startY =
    y + rowH;

    for(size_t i = 0;
        i < data.size();
        i++)
    {
        int ry =
        startY + i * rowH;

        DrawRectangle(

            x,
            ry,

            w,
            rowH-1,

            i%2==0 ?

            C_CARD2

            :

            Fade(C_CARD2,0.85f)
        );

        DrawText(

            std::to_string(
                data[i].idBarang
            ).c_str(),

            x + 12,
            ry + 10,

            11,

            C_TEXT
        );

        DrawText(

            data[i]
            .namaBarang
            .c_str(),

            x + 90,
            ry + 10,

            11,

            C_TEXT
        );

        DrawText(

            std::to_string(
                data[i]
                .jumlahBarang
            ).c_str(),

            x + 330,
            ry + 10,

            11,

            C_TEXT
        );

        DrawText(

            data[i]
            .status
            .c_str(),

            x + 460,
            ry + 10,

            11,

            StatusColor(data[i].status)
        );

        if(showBtn1){

            if(DrawButton(

                x + w - 110,
                ry + 4,

                90,
                26,

                btn1Text,

                C_ACCENT2,
                C_TEXT,

                11))
            {
                if(onBtn1)
                    onBtn1(i);
            }
        }

        if(showBtn2){

            if(DrawButton(

                x + w - 210,
                ry + 4,

                90,
                26,

                btn2Text,

                C_DANGER,
                C_TEXT,

                11))
            {
                if(onBtn2)
                    onBtn2(i);
            }
        }
    }
}


void DrawStatCard(

    int x,
    int y,

    int w,
    int h,

    const char* title,

    const char* value,

    Color accent)
{

    DrawRectangle(
        x,
        y,
        w,
        h,
        C_CARD
    );

    DrawRectangleLinesEx(

        {
            (float)x,
            (float)y,
            (float)w,
            (float)h
        },

        1,

        C_BORDER
    );


    DrawRectangle(
        x,
        y,
        5,
        h,
        accent
    );

    DrawText(

        title,

        x + 16,
        y + 16,

        12,

        Fade(C_MUTED,0.8f)
    );


    DrawText(

        value,

        x + 16,
        y + 42,

        26,

        C_TEXT
    );
}

void DrawTableCabang(

    int x,
    int y,

    int w,
    int h,

    const std::vector<Inventaris>& data,

    bool showBtn1,

    const char* btn1Text,

    std::function<void(int)> onBtn1,

    bool showBtn2,

    const char* btn2Text,

    std::function<void(int)> onBtn2)
{
    int rowH = 36;

    DrawRectangle(
        x,
        y,
        w,
        rowH,
        C_CARD
    );

    DrawRectangleLinesEx(

        {
            (float)x,
            (float)y,
            (float)w,
            (float)rowH
        },

        1,

        C_BORDER
    );

    DrawText(
        "ID",
        x + 12,
        y + 10,
        12,
        C_ACCENT
    );

    DrawText(
        "Nama Barang",
        x + 90,
        y + 10,
        12,
        C_ACCENT
    );

    DrawText(
        "Cabang",
        x + 300,
        y + 10,
        12,
        C_ACCENT
    );

    DrawText(
        "Jumlah",
        x + 430,
        y + 10,
        12,
        C_ACCENT
    );

    DrawText(
        "Status",
        x + 570,
        y + 10,
        12,
        C_ACCENT
    );

    int startY =
    y + rowH;

    for(size_t i = 0;
        i < data.size();
        i++)
    {
        int ry =
        startY + i * rowH;

        DrawRectangle(

            x,
            ry,

            w,
            rowH - 1,

            i % 2 == 0 ?

            C_CARD2

            :

            Fade(C_CARD2,0.85f)
        );

        DrawText(

            std::to_string(
                data[i].idBarang
            ).c_str(),

            x + 12,
            ry + 10,

            11,

            C_TEXT
        );

        DrawText(

            data[i]
            .namaBarang
            .c_str(),

            x + 90,
            ry + 10,

            11,

            C_TEXT
        );

        DrawText(

            data[i]
            .cabangTNI
            .c_str(),

            x + 300,
            ry + 10,

            11,

            C_TEXT
        );

        DrawText(

            std::to_string(
                data[i]
                .jumlahBarang
            ).c_str(),

            x + 430,
            ry + 10,

            11,

            C_TEXT
        );

        DrawText(

            data[i]
            .status
            .c_str(),

            x + 570,
            ry + 10,

            11,

            StatusColor(data[i].status)
        );

        if(showBtn1){

            if(DrawButton(

                x + w - 110,
                ry + 4,

                90,
                26,

                btn1Text,

                C_ACCENT2,
                C_TEXT,

                11))
            {
                if(onBtn1)
                    onBtn1(i);
            }
        }

        if(showBtn2){

            if(DrawButton(

                x + w - 210,
                ry + 4,

                90,
                26,

                btn2Text,

                C_DANGER,
                C_TEXT,

                11))
            {
                if(onBtn2)
                    onBtn2(i);
            }
        }
    }
}

void DrawTopbar(){

    DrawRectangle(

        0,
        0,

        GetScreenWidth(),

        TOPBAR_H,

        C_CARD
    );

    DrawRectangle(
        0,
        TOPBAR_H - 2,

        GetScreenWidth(),

        2,

        C_BORDER
    );

    DrawText(

        "SISTEM INVENTARIS TNI",

        20,
        15,

        18,

        C_ACCENT
    );

    DrawText(

        currentRole.c_str(),

        GetScreenWidth() - 140,

        16,

        12,

        Fade(C_MUTED,0.8f)
    );
}

void DrawSidebar(){

    DrawRectangle(

        0,
        TOPBAR_H,

        SIDEBAR_W,

        GetScreenHeight(),

        C_CARD2
    );

    DrawRectangle(
        SIDEBAR_W - 2,
        TOPBAR_H,

        2,
        GetScreenHeight(),

        C_BORDER
    );

    int y =
    TOPBAR_H + 20;

    if(currentRole == "admin"){

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Setujui",

            currentPanel ==
            PANEL_A_SETUJUI

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_A_SETUJUI;
        }

        y += 48;

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Beli",

            currentPanel ==
            PANEL_A_BELI

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_A_BELI;
        }

        y += 48;

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Tambah",

            currentPanel ==
            PANEL_A_TAMBAH

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_A_TAMBAH;
        }

        y += 48;

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Hapus",

            currentPanel ==
            PANEL_A_HAPUS

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_A_HAPUS;
        }

        y += 48;

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Semua Data",

            currentPanel ==
            PANEL_A_SEMUA

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_A_SEMUA;
        }

        y += 48;

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Sorting",

            currentPanel ==
            PANEL_A_SORT

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_A_SORT;
        }

        y += 48;

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Searching",

            currentPanel ==
            PANEL_A_SEARCH

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_A_SEARCH;
        }
    }

    else{

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Lihat",

            currentPanel ==
            PANEL_U_LIHAT

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_U_LIHAT;
        }

        y += 48;

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Tambah",

            currentPanel ==
            PANEL_U_TAMBAH

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_U_TAMBAH;
        }

        y += 48;

       

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Ubah",

            currentPanel ==
            PANEL_U_UBAH

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_U_UBAH;
        }

        y += 48;

        if(DrawButton(

            14,
            y,

            SIDEBAR_W - 28,
            38,

            "Hapus",

            currentPanel ==
            PANEL_U_HAPUS

            ?

            C_ACCENT2

            :

            C_CARD,

            C_TEXT,

            13))
        {
            currentPanel =
            PANEL_U_HAPUS;
        }
    }


if(DrawButton(

    14,
    GetScreenHeight() - 60,

    SIDEBAR_W - 28,
    40,

    "LOGOUT",

    C_DANGER,
    C_TEXT,

    13))
{
    currentScreen =
    SCREEN_LOGIN;

    currentPanel =
    PANEL_A_SETUJUI;

    currentRole = "";

    selRole = -1;

    
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


    memset(
        inputNama,
        0,
        sizeof(inputNama)
    );

    memset(
        inputJumlah,
        0,
        sizeof(inputJumlah)
    );

    memset(
        inputId,
        0,
        sizeof(inputId)
    );


    alertMsg = "";

    alertTimer = 0;

    alertSuccess = false;


    searchMsg = "";

    searchResultIdx = -1;

    activeField = -1;
    }
}