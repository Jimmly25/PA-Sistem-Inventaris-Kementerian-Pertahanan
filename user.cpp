#include "user.h"

#include "globals.h"
#include "ui.h"
#include "inventory.h"

// ============================================================
// PANEL: LIHAT USER
// ============================================================

    void DrawUserLihat() {

        int cx = CONTENT_X + 16;
        int cy = CONTENT_Y + 16;

        int W = GetScreenWidth();

        DrawText(

            ("Lihat " + currentRole).c_str(),

            cx,
            cy,

            18,

            C_TEXT
        );

        cy += 36;

        // ========================================================
        // FILTER DATA USER
        // ========================================================

        std::vector<Inventaris> myData;

        for(auto& d : dataInventaris){

            if(d.cabangTNI == currentRole){

                myData.push_back(d);
            }
        }

        // ========================================================
        // HITUNG STATUS
        // ========================================================

        int totalData = myData.size();

        int diajukan = 0;
        int disetujui = 0;
        int sudahDibeli = 0;

        for(auto& d : myData){

            if(d.status == "Diajukan"){

                diajukan++;
            }

            else if(d.status == "Disetujui"){

                disetujui++;
            }

            else if(d.status == "Sudah Dibeli"){

                sudahDibeli++;
            }
        }

        // ========================================================
        // CARD STATISTIK
        // ========================================================

        int cw =
        (W - CONTENT_X - 60) / 4;

        DrawStatCard(

            cx,
            cy,

            cw,
            80,

            "Data Saya",

            std::to_string(totalData).c_str(),

            C_MUTED
        );

        DrawStatCard(

            cx + cw + 10,
            cy,

            cw,
            80,

            "Pengajuan",

            std::to_string(diajukan).c_str(),

            C_WARN
        );

        DrawStatCard(

            cx + (cw + 10) * 2,
            cy,

            cw,
            80,

            "Disetujui",

            std::to_string(disetujui).c_str(),

            C_SUCCESS
        );

        DrawStatCard(

            cx + (cw + 10) * 3,
            cy,

            cw,
            80,

            "Sudah Dibeli",

            std::to_string(sudahDibeli).c_str(),

            C_INFO
        );

        cy += 110;

        // ========================================================
        // JUDUL TABLE
        // ========================================================

        DrawText(

            ("Inventaris " + currentRole).c_str(),

            cx,
            cy,

            13,

            C_MUTED
        );

        cy += 20;

        // ========================================================
        // DATA KOSONG
        // ========================================================

        if(myData.empty()){

            DrawText(

                "Belum ada data inventaris",

                cx + 10,
                cy + 30,

                18,

                C_MUTED
            );

            return;
        }

        // ========================================================
        // TABLE
        // ========================================================

        int avail =
        GetScreenHeight() - cy - 20;

        DrawTable(

            cx,
            cy,

            W - CONTENT_X - 32,
            avail,

            myData
        );
    }




    // ============================================================
    // PANEL: TAMBAH PENGAJUAN USER
    // ============================================================

    void DrawTambahUser() {

        int cx = CONTENT_X + 16;
        int cy = CONTENT_Y + 16;

        int W = GetScreenWidth();

        int fw =
        std::min(460,
                W - CONTENT_X - 40);

        DrawText("Ajukan Inventaris",
                cx,
                cy,
                16,
                C_TEXT);

        cy += 34;

        // =========================================
        // ALERT
        // =========================================

        if(alertTimer > 0){

            Color abg =
            alertSuccess ?
            GetColor(0x0D1A05FF) :
            GetColor(0x200505FF);

            Color ac =
            alertSuccess ?
            C_SUCCESS :
            C_DANGER;

            DrawRect(cx,
                    cy - 6,
                    fw,
                    30,
                    abg);

            DrawText(alertMsg.c_str(),
                    cx + 8,
                    cy,
                    12,
                    ac);

            alertTimer--;

            cy += 34;
        }

        // =========================================
        // INPUT ID
        // =========================================

        DrawLabel(cx,
                cy,
                "ID BARANG (1-99999)",
                C_MUTED,
                10);

        cy += 14;

        DrawTextBox(cx,
                    cy,
                    fw,
                    34,
                    inputId,
                    16,
                    10,
                    "contoh: 101");

        cy += 44;

        // =========================================
        // INPUT NAMA
        // =========================================

        DrawLabel(cx,
                cy,
                "NAMA BARANG",
                C_MUTED,
                10);

        cy += 14;

        DrawTextBox(cx,
                    cy,
                    fw,
                    34,
                    inputNama,
                    128,
                    11,
                    "contoh: Senapan");

        cy += 44;

        // =========================================
        // INPUT JUMLAH
        // =========================================

        DrawLabel(cx,
                cy,
                "JUMLAH BARANG",
                C_MUTED,
                10);

        cy += 14;

        DrawTextBox(cx,
                    cy,
                    fw,
                    34,
                    inputJumlah,
                    16,
                    12,
                    "contoh: 10");

        cy += 44;

        DrawText(
            ("Cabang otomatis: " +
            currentRole).c_str(),

            cx,
            cy,

            11,

            Fade(C_MUTED,0.7f)
        );

        cy += 24;

        DrawText("Status otomatis: Menunggu Persetujuan",
                cx,
                cy,
                11,
                Fade(C_MUTED,0.6f));

        cy += 24;

        // =========================================
        // BUTTON AJUKAN
        // =========================================

        if(DrawButton(cx,
                    cy,
                    fw,
                    38,
                    "AJUKAN INVENTARIS",
                    C_ACCENT2,
                    C_TEXT,
                    14)) {

            // VALIDASI ANGKA

            if(!isAllDigit(inputId)){

                showAlert(
                    "ID harus berupa angka!",
                    false
                );

                return;
            }

            if(!isAllDigit(inputJumlah)){

                showAlert(
                    "Jumlah harus berupa angka!",
                    false
                );

                return;
            }

            int id =
            atoi(inputId);

            int jml =
            atoi(inputJumlah);

            // VALIDASI ID

            if(id < 1 || id > 99999){

                showAlert(
                    "ID tidak valid (1-99999)!",
                    false
                );

                return;
            }

            if(idExists(id)){

                showAlert(
                    "ID sudah digunakan!",
                    false
                );

                return;
            }

            // VALIDASI NAMA

            if(!isAllAlpha(inputNama)){

                showAlert(
                    "Nama hanya boleh huruf, spasi, strip & angka!",
                    false
                );

                return;
            }

            // VALIDASI JUMLAH

            if(jml <= 0){

                showAlert(
                    "Jumlah harus lebih dari 0!",
                    false
                );

                return;
            }

            // VALIDASI KAPASITAS

            if(dataInventaris.size() >= 100){

                showAlert(
                    "Kapasitas penuh (maks 100)!",
                    false
                );

                return;
            }

            // =====================================
            // TAMBAH DATA
            // =====================================

            Inventaris nw;

            nw.idBarang = id;
            nw.namaBarang = inputNama;
            nw.jumlahBarang = jml;
            nw.cabangTNI = currentRole;
            nw.status = "Diajukan";

            dataInventaris.push_back(nw);

           
        

            showAlert(
                "Pengajuan berhasil dikirim!",
                true
            );

            memset(inputId,
                0,
                sizeof(inputId));

            memset(inputNama,
                0,
                sizeof(inputNama));

            memset(inputJumlah,
                0,
                sizeof(inputJumlah));

            activeField = -1;
        }
    }





        // ============================================================
    // PANEL: UBAH DATA USER
    // ============================================================

    void DrawUbahUser() {

        int cx = CONTENT_X + 16;
        int cy = CONTENT_Y + 16;

        DrawText(
            "Ubah Data Pengajuan",
            cx,
            cy,

            18,
            C_TEXT
        );

        cy += 40;

        // =========================================
        // ALERT
        // =========================================

        if(alertTimer > 0){

            Color abg =
            alertSuccess ?

            GetColor(0x0D1A05FF)

            :

            GetColor(0x200505FF);

            Color ac =
            alertSuccess ?

            C_SUCCESS :

            C_DANGER;

            DrawRect(
                cx,
                cy - 6,
                420,
                30,
                abg
            );

            DrawText(
                alertMsg.c_str(),
                cx + 8,
                cy,
                12,
                ac
            );

            alertTimer--;

            cy += 34;
        }

        std::vector<int> myIndex;

        for(size_t i = 0;
            i < dataInventaris.size();
            i++)
        {
            if(dataInventaris[i].cabangTNI ==
            currentRole)
            {
                myIndex.push_back(i);
            }
        }

        if(myIndex.empty()){

            DrawText(
                "Belum ada data.",
                cx,
                cy,
                14,
                C_MUTED
            );

            return;
        }

        static int selected = -1;

        // =====================================
        // LIST DATA
        // =====================================

        for(size_t i = 0;
            i < myIndex.size();
            i++)
        {
            int idx = myIndex[i];

            std::string txt =
            std::to_string(
                dataInventaris[idx].idBarang
            ) +

            " - " +

            dataInventaris[idx].namaBarang +

            " (" +

            dataInventaris[idx].status +

            ")";

            if(DrawButton(
                cx,
                cy,
                420,
                34,
                txt.c_str(),

                selected == idx ?
                C_ACCENT :
                C_CARD2,

                C_TEXT,
                12))
            {
                selected = idx;

                strcpy(
                    inputNama,
                    dataInventaris[idx]
                    .namaBarang.c_str()
                );

                sprintf(
                    inputJumlah,
                    "%d",

                    dataInventaris[idx]
                    .jumlahBarang
                );
            }

            cy += 42;
        }

        // =====================================
        // FORM UBAH
        // =====================================

        if(selected >= 0){

            cy += 10;

            DrawText(
                "Nama Barang",
                cx,
                cy,
                12,
                C_MUTED
            );

            cy += 16;

            DrawTextBox(
                cx,
                cy,
                420,
                34,
                inputNama,
                128,
                51,
                "Nama Barang"
            );

            cy += 50;

            DrawText(
                "Jumlah Barang",
                cx,
                cy,
                12,
                C_MUTED
            );

            cy += 16;

            DrawTextBox(
                cx,
                cy,
                420,
                34,
                inputJumlah,
                16,
                52,
                "Jumlah"
            );

            cy += 50;

            // =====================================
            // BUTTON UBAH
            // =====================================

            if(DrawButton(
                cx,
                cy,
                420,
                38,
                "UBAH DATA",
                C_ACCENT2,
                C_TEXT,
                14))
            {
                // =================================
                // VALIDASI STATUS
                // =================================

                if(dataInventaris[selected]
                .status == "Disetujui" ||

                dataInventaris[selected]
                .status == "Sudah Dibeli" ||

                dataInventaris[selected]
                .status == "Ditolak")
                {
                    showAlert(
                        "Data ini tidak bisa diubah!",
                        false
                    );

                    return;
                }
                // =================================
                // VALIDASI NAMA
                // =================================

                if(!isAllAlpha(inputNama)){

                    showAlert(
                        "Nama hanya boleh huruf, spasi, strip & angka!",
                        false
                    );

                    return;
                }

                // =================================
                // VALIDASI JUMLAH
                // =================================

                if(!isAllDigit(inputJumlah)){

                    showAlert(
                        "Jumlah harus angka!",
                        false
                    );

                    return;
                }

                int jml =
                atoi(inputJumlah);

                if(jml <= 0){

                    showAlert(
                        "Jumlah harus lebih dari 0!",
                        false
                    );

                    return;
                }

                // =================================
                // UPDATE DATA
                // =================================

                dataInventaris[selected]
                .namaBarang = inputNama;

                dataInventaris[selected]
                .jumlahBarang = jml;

                

                showAlert(
                    "Data berhasil diubah!",
                    true
                );

                selected = -1;

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
            }
        }
    }



        // ============================================================
    // PANEL: HAPUS DATA USER
    // ============================================================

    void DrawHapusUser() {

        int cx = CONTENT_X + 16;
        int cy = CONTENT_Y + 16;

        DrawText(
            "Hapus Data Pengajuan",
            cx,
            cy,
            18,
            C_TEXT
        );

        cy += 40;

                // =========================================
        // ALERT
        // =========================================

        if(alertTimer > 0){

            Color abg =
            alertSuccess ?

            GetColor(0x0D1A05FF)

            :

            GetColor(0x200505FF);

            Color ac =
            alertSuccess ?

            C_SUCCESS

            :

            C_DANGER;

            DrawRect(
                cx,
                cy - 6,
                420,
                30,
                abg
            );

            DrawText(
                alertMsg.c_str(),
                cx + 8,
                cy,
                12,
                ac
            );

            alertTimer--;

            cy += 40;
        }

        bool ada = false;

        for(size_t i = 0;
            i < dataInventaris.size();
            i++)
        {
            if(dataInventaris[i].cabangTNI ==
            currentRole)
            {
                ada = true;

                std::string txt =

                std::to_string(
                    dataInventaris[i]
                    .idBarang
                )

                + " - " +

                dataInventaris[i]
                .namaBarang

                + " (" +

                dataInventaris[i]
                .status +

                ")";

                DrawText(
                    txt.c_str(),
                    cx,
                    cy + 8,
                    12,
                    C_TEXT
                );

                if(DrawButton(
                    cx + 500,
                    cy,
                    120,
                    32,
                    "HAPUS",
                    RED,
                    WHITE,
                    12))
                {
                    // =============================
                    // VALIDASI STATUS
                    // =============================

                    if(dataInventaris[i]
                    .status == "Disetujui" ||

                    dataInventaris[i]
                    .status == "Sudah Dibeli")
                    {
                        showAlert(
                            "Data yang sudah disetujui tidak bisa dihapus!",
                            false
                        );

                        return;
                    }

                    dataInventaris.erase(
                        dataInventaris.begin() + i
                    );

                    
                    

                   

                    showAlert(
                        "Data berhasil dihapus!",
                        true
                    );

                    break;
                }

                cy += 42;


            }
        }

        if(!ada){

            DrawText(
                "Belum ada data.",
                cx,
                cy,
                14,
                C_MUTED
            );
        }
    }