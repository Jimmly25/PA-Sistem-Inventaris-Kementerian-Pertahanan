#include "inventory.h"


void showAlert(const std::string& msg, bool success) {

    alertMsg = msg;
    alertSuccess = success;
    alertTimer = 180;
}



bool idExists(int id) {

    for (auto& d : dataInventaris)

        if (d.idBarang == id)
            return true;

    return false;
}

bool isAllAlpha(const std::string& s) {

    if(s.empty())
        return false;

    for(char c : s){

        if(

            !isalnum(c) &&
            c != ' ' &&
            c != '-'
        )
        {
            return false;
        }
    }

    return true;
}

bool isAllDigit(const std::string& s){

    if(s.empty()) return false;

    for(char c : s){

        if(!isdigit(c)){

            return false;
        }
    }

    return true;
}


void bubbleSortNama(bool asc) {

    int n = dataInventaris.size();

    for (int i = 0; i < n-1; i++)

        for (int j = 0; j < n-i-1; j++)

            if (asc ?

                dataInventaris[j].namaBarang >
                dataInventaris[j+1].namaBarang

                :

                dataInventaris[j].namaBarang <
                dataInventaris[j+1].namaBarang)

                std::swap(
                    dataInventaris[j],
                    dataInventaris[j+1]
                );
}

void selectionSortJumlah(bool asc) {

    int n = dataInventaris.size();

    for (int i = 0; i < n-1; i++) {

        int idx = i;

        for (int j = i+1; j < n; j++)

            if (asc ?

                dataInventaris[j].jumlahBarang <
                dataInventaris[idx].jumlahBarang

                :

                dataInventaris[j].jumlahBarang >
                dataInventaris[idx].jumlahBarang)

                idx = j;

        std::swap(
            dataInventaris[i],
            dataInventaris[idx]
        );
    }
}

void insertionSortID() {

    int n = dataInventaris.size();

    for (int i = 1; i < n; i++) {

        Inventaris key =
        dataInventaris[i];

        int j = i - 1;

        while (j >= 0 &&
            dataInventaris[j].idBarang >
            key.idBarang)
        {
            dataInventaris[j+1] =
            dataInventaris[j];

            j--;
        }

        dataInventaris[j+1] = key;
    }
}


int binarySearchNama(const std::string& nama) {

    std::vector<Inventaris> temp =
    dataInventaris;

    int n = temp.size();

    for (int i = 0; i < n - 1; i++)

        for (int j = 0; j < n - i - 1; j++)

            if (temp[j].namaBarang >
                temp[j + 1].namaBarang)

                std::swap(
                    temp[j],
                    temp[j + 1]
                );

    int l = 0;
    int r = temp.size() - 1;

    while (l <= r) {

        int m = (l + r) / 2;

        if (temp[m].namaBarang == nama) {

            for (size_t i = 0;
                i < dataInventaris.size();
                i++) {

                if (dataInventaris[i].idBarang ==
                    temp[m].idBarang)

                    return i;
            }
        }

        if (temp[m].namaBarang < nama)

            l = m + 1;

        else

            r = m - 1;
    }

    return -1;
}

int sequentialSearchID(int id) {

    for (int i = 0;
        i < (int)dataInventaris.size();
        i++)

        if (dataInventaris[i].idBarang == id)
            return i;

    return -1;
}


Color StatusColor(const std::string& s){

    if(s == "Diajukan")
        return ORANGE;

    if(s == "Disetujui")
        return GREEN;

    if(s == "Sudah Dibeli")
        return SKYBLUE;

    if(s == "Ditolak")
    return RED;

    return RAYWHITE;
}
