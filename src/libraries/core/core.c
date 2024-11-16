#include "core.h"

void initialize() {
    printf("%d", registerCitizen(
        "Naphon",
        "Janggerd",
        "1122234556788",
        make_date(
            11,
            "January",
            2024
        ),
        make_address(
            "11",
            "Prachauthith",
            "Bangmod",
            "Bangkok",
            "10140"
        ),
        make_contact(
            "0887776666",
            "thewhalezaza900@gmail.com"
        )
    ));

    printTBL("Citizens.dat");
    printTBL("Addresses.dat");
    printTBL("Contacts.dat");
}