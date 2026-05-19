    #include "admin.h"

    #include "globals.h"
    #include "ui.h"
    #include "inventory.h"

   
        // ============================================================
        // PANEL: SETUJUI PENGAJUAN
        // ============================================================
        void DrawSetujui() {

            int cx = CONTENT_X + 16;
            int cy = CONTENT_Y + 16;

            int W = GetScreenWidth();

            DrawText(
                "Setujui Pengajuan",
                cx,
                cy,
                24,
                C_TEXT
            );

            cy += 40;

            // ALERT

            if(alertTimer > 0){

                Color abg =
                alertSuccess ?
                GetColor(0x0D1A05FF) :
                GetColor(0x200505FF);

                Color ac =
                alertSuccess ?
                C_SUCCESS :
                C_DANGER;

                DrawRect(
                    cx,
                    cy,
                    W - CONTENT_X - 32,
                    30,
                    abg
                );

                DrawText(
                    alertMsg.c_str(),
                    cx + 8,
                    cy + 8,
                    12,
                    ac
                );

                alertTimer--;

                cy += 40;
            }

            // =====================================
            // AMBIL DATA DIAJUKAN
            // =====================================

            std::vector<Inventaris> items;

            for(auto& d : dataInventaris){

                if(d.status == "Diajukan"){

                    items.push_back(d);
                }
            }

            // =====================================
            // TABLE
            // =====================================

            int avail =
            GetScreenHeight() - cy - 20;

            if(items.empty()){

                DrawText(

                    "Belum ada pengajuan",

                    cx + 20,
                    cy + 40,

                    18,

                    C_MUTED
                );

                return;
            }

            DrawTableCabang(
                cx,
                cy,
                W - CONTENT_X - 32,
                avail,
                items,

                true,
                "Setujui",

                [&](int i){

                    if(i >= 0 &&
                    (size_t)i < items.size()){

                        int targetId =
                        items[i].idBarang;

                        for(auto& d :
                            dataInventaris)
                        {
                            if(d.idBarang ==
                            targetId &&

                            d.status ==
                            "Diajukan")
                            {
                                d.status =
                                "Disetujui";

                                

                                showAlert(
                                    "Pengajuan berhasil disetujui!",
                                    true
                                );

                                break;
                            }
                        }
                    }
                },

                

                // =====================================
                // BUTTON TOLAK
                // =====================================

                true,
                "Tolak",

                [&](int i){

                    if(i >= 0 &&
                    (size_t)i < items.size()){

                        int targetId =
                        items[i].idBarang;

                        for(auto& d :
                            dataInventaris)
                        {
                            if(d.idBarang ==
                            targetId &&

                            d.status ==
                            "Diajukan")
                            {
                                d.status =
                                "Ditolak";

                                

                                showAlert(
                                    "Pengajuan berhasil ditolak!",
                                    false
                                );

                                break;
                            }
                        }
                    }
                }
            );
            }

// ============================================================
// PANEL: BELI INVENTARIS
// ============================================================

        void DrawBeli() {

            int cx = CONTENT_X + 16;
            int cy = CONTENT_Y + 16;

            int W = GetScreenWidth();

            DrawText(

                "Beli Inventaris",

                cx,
                cy,

                18,

                C_TEXT
            );

            cy += 36;

            // ========================================================
            // ALERT
            // ========================================================

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
                    cy,

                    W - CONTENT_X - 32,
                    30,

                    abg
                );

                DrawText(

                    alertMsg.c_str(),

                    cx + 8,
                    cy + 8,

                    12,

                    ac
                );

                alertTimer--;

                cy += 40;
            }

            // ========================================================
            // FILTER DATA DISETUJUI
            // ========================================================

            std::vector<Inventaris> items;

            for(auto& d : dataInventaris){

                if(d.status == "Disetujui"){

                    items.push_back(d);
                }
            }

            // ========================================================
            // DATA KOSONG
            // ========================================================

            if(items.empty()){

                DrawText(

                    "Belum ada inventaris yang disetujui",

                    cx + 20,
                    cy + 40,

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

            DrawTableCabang(

                cx,
                cy,

                W - CONTENT_X - 32,
                avail,

                items,

                true,
                "Beli",

                [&](int i){

                    if(i >= 0 &&
                    (size_t)i < items.size())
                    {
                        int targetId =
                        items[i].idBarang;

                        for(auto& d :
                            dataInventaris)
                        {
                            if(d.idBarang ==
                            targetId &&

                            d.status ==
                            "Disetujui")
                            {
                                d.status =
                                "Sudah Dibeli";

                                

                                showAlert(

                                    "Inventaris ID " +

                                    std::to_string(
                                        d.idBarang
                                    ) +

                                    " berhasil dibeli!",

                                    true
                                );

                                break;
                            }
                        }
                    }
                }
            );
        }


            // ============================================================
        // PANEL: TAMBAH INVENTARIS ADMIN
        // ============================================================

        void DrawTambahAdmin() {

            int cx = CONTENT_X + 16;
            int cy = CONTENT_Y + 16;

            int W = GetScreenWidth();

            int fw =
            std::min(460,
                    W - CONTENT_X - 40);

            DrawText("Tambah Inventaris (Admin)",
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

            // =========================================
            // CABANG TNI
            // =========================================

            DrawLabel(cx,
                    cy,
                    "CABANG TNI",
                    C_MUTED,
                    10);

            cy += 14;

            const char* cabs[] = {
                "TNI_AD",
                "TNI_AU",
                "TNI_AL"
            };

            for(int i = 0; i < 3; i++){

                bool sel =
                (std::string(inputCabangSel)
                == cabs[i]);

                Color bg =
                sel ? C_BTN : C_CARD2;

                Color bc =
                sel ? C_ACCENT : C_BORDER;

                DrawRectangle(
                    cx + i * 110,
                    cy,
                    100,
                    32,
                    bg
                );

                DrawRectangleLinesEx(
                    {
                        (float)(cx + i * 110),
                        (float)cy,
                        100.f,
                        32.f
                    },
                    sel ? 2.f : 1.f,
                    bc
                );

                DrawText(
                    cabs[i],

                    cx + i * 110 + 50 -
                    MeasureText(cabs[i],11)/2,

                    cy + 9,
                    11,

                    sel ? C_ACCENT : C_TEXT
                );

                if(IsMouseButtonPressed(
                    MOUSE_LEFT_BUTTON)) {

                    Vector2 m =
                    GetMousePosition();

                    if(m.x >= cx + i * 110 &&
                    m.x <= cx + i * 110 + 100 &&
                    m.y >= cy &&
                    m.y <= cy + 32)

                        strcpy(inputCabangSel,
                            cabs[i]);
                }
            }

            cy += 50;

            DrawText("Status otomatis: Sudah Dibeli",
                    cx,
                    cy,
                    11,
                    Fade(C_MUTED,0.6f));

            cy += 24;

            // =========================================
            // BUTTON TAMBAH
            // =========================================

            if(DrawButton(cx,
                        cy,
                        fw,
                        38,
                        "TAMBAH INVENTARIS",
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
                nw.cabangTNI = inputCabangSel;
                nw.status = "Sudah Dibeli";

                dataInventaris.push_back(nw);

                

                showAlert(
                    "Inventaris berhasil ditambahkan!",
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
            }
        }



        // ============================================================
        // PANEL: HAPUS INVENTARIS ADMIN
        // ============================================================
            void DrawHapusAdmin() {
            
                int cx = CONTENT_X + 16;
                int cy = 80;
                
                 // ====================================
                // JUDUL
                // ====================================

                DrawText(

                    "Hapus Inventaris",

                    cx,
                    cy,

                    18,

                    C_TEXT
                );

                cy += 40;
                
                int avail = GetScreenHeight() - cy - 20;
                if(dataInventaris.empty()){


                    

                    DrawText(

                        "Belum ada data inventaris",

                        cx + 20,
                        cy + 40,

                        18,

                        C_MUTED
                    );

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

                    return;
                } // Menggunakan variabel 'avail' bawaan aslimu

                // Panggil DrawTable dengan parameter yang tepat menggunakan variabel yang sudah disesuaikan
                DrawTableCabang(

                    cx,
                    cy,

                    GetScreenWidth() - CONTENT_X - 32,
                    avail,

                    dataInventaris,

                    false,
                    "",
                    nullptr,

                    true,
                    "Hapus",

                    [&](int i){

                        dataInventaris.erase(
                            dataInventaris.begin() + i
                        );

                        showAlert(
                            "Inventaris berhasil dihapus!",
                            true
                        );
                        return;

                        
                    }
                );
            }



        // ============================================================
        // PANEL: SEMUA DATA
        // ============================================================
        void DrawSemuaData() {

            int cx = CONTENT_X + 16;
            int cy = CONTENT_Y + 16;

            int W = GetScreenWidth();

            if(dataInventaris.empty()){

                DrawText(

                    "Belum ada data inventaris",

                    cx + 20,
                    cy + 40,

                    18,

                    C_MUTED
                );

                return;
            }

            DrawText(
                "Semua Data Inventaris",
                cx,
                cy,
                18,
                C_TEXT
            );

            cy += 40;

            // =====================================
            // FILTER DATA
            // =====================================

            std::vector<Inventaris> ad;
            std::vector<Inventaris> au;
            std::vector<Inventaris> al;

            for(auto& d : dataInventaris){

                if(d.cabangTNI == "TNI_AD")
                    ad.push_back(d);

                else if(d.cabangTNI == "TNI_AU")
                    au.push_back(d);

                else if(d.cabangTNI == "TNI_AL")
                    al.push_back(d);
            }

            // =====================================
            // TNI AD
            // =====================================

            DrawText(
                ("TNI AD (" +
                std::to_string(ad.size()) +
                " Data)").c_str(),

                cx,
                cy,

                15,

                C_ACCENT
            );

            cy += 24;

          

            DrawTable(
                cx,
                cy,
                W - CONTENT_X - 32,
                110,
                ad
            );

            cy += 140;

            // =====================================
            // TNI AU
            // =====================================

            DrawText(
                ("TNI AU (" +
                std::to_string(au.size()) +
                " Data)").c_str(),

                cx,
                cy,

                15,

                GREEN
            );

            cy += 24;

         

            DrawTable(
                cx,
                cy,
                W - CONTENT_X - 32,
                110,
                au
            );

            cy += 140;

            // =====================================
            // TNI AL
            // =====================================

            DrawText(
                ("TNI AL (" +
                std::to_string(al.size()) +
                " Data)").c_str(),

                cx,
                cy,

                15,

                ORANGE
            );

            cy += 24;

        
            

            DrawTable(
                cx,
                cy,
                W - CONTENT_X - 32,
                110,
                al
            );
        }



        // ============================================================
        // PANEL: SORTING
        // ============================================================
        void DrawSorting() {
            int cx=CONTENT_X+16, cy=CONTENT_Y+16;
            int W=GetScreenWidth();
            DrawText("Sorting Data", cx, cy, 16, C_TEXT); cy+=34;

            if(alertTimer>0){
                Color abg=alertSuccess?GetColor(0x0D1A05FF):GetColor(0x200505FF);
                Color ac=alertSuccess?C_SUCCESS:C_DANGER;
                DrawRect(cx,cy-6,W-CONTENT_X-32,30,abg);
                DrawText(alertMsg.c_str(),cx+8,cy,12,ac); alertTimer--; cy+=38;
            }

            struct SortBtn { const char* label; const char* desc; };
            SortBtn btns[]={
                {"Bubble Sort Nama ASC","Urutkan nama A-Z"},
                {"Bubble Sort Nama DESC","Urutkan nama Z-A"},
                {"Selection Sort Jumlah ASC","Urutkan jumlah terkecil"},
                {"Selection Sort Jumlah DESC","Urutkan jumlah terbesar"},
                {"Insertion Sort ID","Urutkan berdasarkan ID"},
            };
            int bw=250,bh=44,gap=10;
            for(int i=0;i<5;i++){
                bool hover=false;
                Rectangle r={(float)cx,(float)cy,(float)bw,(float)bh};
                Vector2 m=GetMousePosition();
                hover=CheckCollisionPointRec(m,r);
                DrawRect(cx,cy,bw,bh,hover?C_BTN_HOV:C_BTN);
                DrawRectangleLinesEx(r,1,C_BORDER);
                DrawText(btns[i].label,cx+10,cy+8,12,C_ACCENT);
                DrawText(btns[i].desc,cx+10,cy+26,10,Fade(C_MUTED,0.7f));
                if(hover&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    if(dataInventaris.empty()){showAlert("Data kosong!",false);}
                    else{
                        if(i==0)bubbleSortNama(true);
                        else if(i==1)bubbleSortNama(false);
                        else if(i==2)selectionSortJumlah(true);
                        else if(i==3)selectionSortJumlah(false);
                        else insertionSortID();
                        showAlert(std::string(btns[i].label)+" berhasil!",true);
                    }
                }
                cy+=bh+gap;
            }

            if(!dataInventaris.empty()){
                cy+=8;
                DrawText("Hasil Data (setelah sorting):", cx, cy, 12, C_MUTED); cy+=18;
                int avail=GetScreenHeight()-cy-20;
                DrawTable(cx,cy,W-CONTENT_X-32,avail,dataInventaris);
            }
        }

        // ============================================================
        // PANEL: SEARCHING
        // ============================================================

        void DrawSearching() {

            int cx = CONTENT_X + 16;
            int cy = CONTENT_Y + 16;

            int W = GetScreenWidth();
            int fw = 360;

            DrawText("Searching Data",
                    cx,
                    cy,
                    16,
                    C_TEXT);

            cy += 34;

            // =========================================
            // SEARCH BY ID
            // =========================================

            DrawText("Sequential Search (by ID):",
                    cx,
                    cy,
                    13,
                    C_MUTED);

            cy += 20;

            DrawLabel(cx,
                    cy,
                    "ID BARANG",
                    C_MUTED,
                    10);

            cy += 14;

            DrawTextBox(cx,
                        cy,
                        fw,
                        34,
                        inputId,
                        16,
                        20,
                        "masukkan ID");

            cy += 10;

            if(DrawButton(

                cx + fw + 10,
                cy - 34,

                120,
                34,

                "Cari ID",

                C_BTN,
                C_ACCENT,

                12))
            {

                // RESET HASIL
                if(strlen(inputId) == 0)
                {
                    searchResultIdx = -1;

                    searchMsg = "";

                    return;
                }

                if(!isAllDigit(inputId)) {

                    showAlert(
                        "ID harus berupa angka!",
                        false
                    );

                    return;
                }

                int id = atoi(inputId);

                if(id < 1) {

                    showAlert(
                        "ID tidak valid!",
                        false
                    );

                    return;
                }

                int idx =
                sequentialSearchID(id);

                if(idx >= 0) {

                    searchResultIdx = idx;

                    searchMsg =
                    "DATA DITEMUKAN (Sequential Search)";
                }

                else {

                    searchResultIdx = -1;

                    searchMsg =
                    "Data tidak ditemukan!";
                }
            }

            cy += 38;

            // =========================================
            // SEARCH BY NAMA
            // =========================================

            DrawText("Binary Search (by Nama):",
                    cx,
                    cy,
                    13,
                    C_MUTED);

            cy += 20;

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
                        21,
                        "masukkan nama lengkap");

            cy += 10;

            if(DrawButton(cx + fw + 10,
                        cy - 34,
                        120,
                        34,
                        "Cari Nama",
                        C_BTN,
                        C_ACCENT,
                        12)) {

                std::string nama = inputNama;

                if(!isAllAlpha(nama)) {

                    showAlert(
                        "Nama hanya boleh huruf & spasi!",
                        false
                    );

                    return;
                }

                int idx = binarySearchNama(nama);

                if(idx >= 0) {

                    searchResultIdx = idx;

                    searchMsg =
                    "DATA DITEMUKAN (Binary Search)";
                }

                else {

                    searchResultIdx = -1;

                    searchMsg =
                    "Data tidak ditemukan!";
                }
            }

            cy += 38;

            // =========================================
            // HASIL SEARCH
            // =========================================

            if(!searchMsg.empty()) {

                bool found =
                (searchResultIdx >= 0);

                Color c =
                found ?
                C_SUCCESS :
                C_DANGER;

                Color bg =
                found ?
                GetColor(0x0D1A05FF) :
                GetColor(0x200505FF);

                DrawRect(cx,
                        cy,
                        W - CONTENT_X - 32,
                        found ? 130 : 40,
                        bg);

                DrawRectangleLinesEx(
                    {
                        (float)cx,
                        (float)cy,
                        (float)(W - CONTENT_X - 32),
                        found ? 130.f : 40.f
                    },
                    1,
                    c
                );

                DrawText(searchMsg.c_str(),
                        cx + 10,
                        cy + 10,
                        13,
                        c);

                cy += 30;

                if(found) {

                    auto& d =
                    dataInventaris[searchResultIdx];

                    DrawText(
                        ("ID        : " +
                        std::to_string(d.idBarang)).c_str(),

                        cx + 10,
                        cy,
                        12,
                        C_TEXT
                    );

                    cy += 20;

                    DrawText(
                        ("Nama      : " +
                        d.namaBarang).c_str(),

                        cx + 10,
                        cy,
                        12,
                        C_TEXT
                    );

                    cy += 20;

                    DrawText(
                        ("Jumlah    : " +
                        std::to_string(d.jumlahBarang)).c_str(),

                        cx + 10,
                        cy,
                        12,
                        C_TEXT
                    );

                    cy += 20;

                    DrawText(
                        ("Cabang    : " +
                        d.cabangTNI).c_str(),

                        cx + 10,
                        cy,
                        12,
                        C_TEXT
                    );

                    cy += 20;

                    DrawText(
                        ("Status    : " +
                        d.status).c_str(),

                        cx + 10,
                        cy,
                        12,
                        StatusColor(d.status)
                    );
                }
            }
        }

