#pragma once

#include "globals.h"


// =====================================================
// ALERT
// =====================================================

void showAlert(

    const std::string& msg,

    bool success
);

// =====================================================
// VALIDATION
// =====================================================

bool idExists(

    int id
);

bool isAllAlpha(

    const std::string& s
);

bool isAllDigit(

    const std::string& s
);

// =====================================================
// STATUS COLOR
// =====================================================

Color StatusColor(

    const std::string& s
);



// =====================================================
// SORTING
// =====================================================

void bubbleSortNama(

    bool asc
);

void selectionSortJumlah(

    bool asc
);

void insertionSortID();

// =====================================================
// SEARCHING
// =====================================================

int binarySearchNama(

    const std::string& nama
);

int sequentialSearchID(

    int id
);

