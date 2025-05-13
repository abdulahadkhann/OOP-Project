#include "HotelRoom.h"
#include <iostream>
using namespace std;

HotelRoom::HotelRoom() {}
HotelRoom::~HotelRoom() {}

// --------------------- Standard ---------------------
Standard::Standard() : price(10000), sum(0) {
    array_for_availability = new char*[10];
    for (int i = 0; i < 10; i++) {
        array_for_availability[i] = new char[20];
        for (int j = 0; j < 20; j++) array_for_availability[i][j] = 'A';
    }
}
void Standard::book_a_room() {
    cout << "Enter floor (0-9): "; cin >> floor;
    cout << "Enter room number (1-20): "; cin >> roomNumber;
    if (array_for_availability[9 - floor][roomNumber - 1] == 'A') {
        array_for_availability[9 - floor][roomNumber - 1] = 'S';
        cout << "Days staying: "; cin >> days;
    } else cout << "Room already booked.\n";
}
void Standard::available_rooms() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) cout << array_for_availability[i][j] << " ";
        cout << endl;
    }
}
void Standard::displayPrice() {
    discount = price * days * 0.3;
    totalprice = price * days;
    finalPrice = totalprice - discount;
    sum += finalPrice;
    cout << "Final Price: " << finalPrice << " PKR" << endl;
}
ostream& operator<<(ostream& os, const Standard& room) {
    os << "Standard Room: Price per night: " << room.price;
    return os;
}
Standard::~Standard() {
    for (int i = 0; i < 10; i++) delete[] array_for_availability[i];
    delete[] array_for_availability;
}

// --------------------- Deluxe ---------------------
Deluxe::Deluxe() : price(20000), sum(0) {
    array_for_availability = new char*[10];
    for (int i = 0; i < 10; i++) {
        array_for_availability[i] = new char[20];
        for (int j = 0; j < 20; j++) array_for_availability[i][j] = 'A';
    }
}
void Deluxe::book_a_room() {
    cout << "Enter floor (0-9): "; cin >> floor;
    cout << "Enter room number (1-20): "; cin >> roomNumber;
    if (array_for_availability[9 - floor][roomNumber - 1] == 'A') {
        array_for_availability[9 - floor][roomNumber - 1] = 'S';
        cout << "Days staying: "; cin >> days;
    } else cout << "Room already booked.\n";
}
void Deluxe::available_rooms() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) cout << array_for_availability[i][j] << " ";
        cout << endl;
    }
}
void Deluxe::displayPrice() {
    discount = price * days * 0.3;
    totalprice = price * days;
    finalPrice = totalprice - discount;
    sum += finalPrice;
    cout << "Final Price: " << finalPrice << " PKR" << endl;
}
ostream& operator<<(ostream& os, const Deluxe& room) {
    os << "Deluxe Room: Price per night: " << room.price;
    return os;
}
Deluxe::~Deluxe() {
    for (int i = 0; i < 10; i++) delete[] array_for_availability[i];
    delete[] array_for_availability;
}

// --------------------- Suite ---------------------
Suite::Suite() : price(30000), sum(0) {
    array_for_availability = new char*[10];
    for (int i = 0; i < 10; i++) {
        array_for_availability[i] = new char[20];
        for (int j = 0; j < 20; j++) array_for_availability[i][j] = 'A';
    }
}
void Suite::book_a_room() {
    cout << "Enter floor (0-9): "; cin >> floor;
    cout << "Enter room number (1-20): "; cin >> roomNumber;
    if (array_for_availability[9 - floor][roomNumber - 1] == 'A') {
        array_for_availability[9 - floor][roomNumber - 1] = 'S';
        cout << "Days staying: "; cin >> days;
    } else cout << "Room already booked.\n";
}
void Suite::available_rooms() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) cout << array_for_availability[i][j] << " ";
        cout << endl;
    }
}
void Suite::displayPrice() {
    discount = price * days * 0.3;
    totalprice = price * days;
    finalPrice = totalprice - discount;
    sum += finalPrice;
    cout << "Final Price: " << finalPrice << " PKR" << endl;
}
ostream& operator<<(ostream& os, const Suite& room) {
    os << "Suite: Price per night: " << room.price;
    return os;
}
Suite::~Suite() {
    for (int i = 0; i < 10; i++) delete[] array_for_availability[i];
    delete[] array_for_availability;
}

// --------------------- ExecutiveSuite ---------------------
ExecutiveSuite::ExecutiveSuite() : price(40000), sum(0) {
    array_for_availability = new char*[10];
    for (int i = 0; i < 10; i++) {
        array_for_availability[i] = new char[20];
        for (int j = 0; j < 20; j++) array_for_availability[i][j] = 'A';
    }
}
void ExecutiveSuite::book_a_room() {
    cout << "Enter floor (0-9): "; cin >> floor;
    cout << "Enter room number (1-20): "; cin >> roomNumber;
    if (array_for_availability[9 - floor][roomNumber - 1] == 'A') {
        array_for_availability[9 - floor][roomNumber - 1] = 'S';
        cout << "Days staying: "; cin >> days;
    } else cout << "Room already booked.\n";
}
void ExecutiveSuite::available_rooms() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) cout << array_for_availability[i][j] << " ";
        cout << endl;
    }
}
void ExecutiveSuite::displayPrice() {
    discount = price * days * 0.3;
    totalprice = price * days;
    finalPrice = totalprice - discount;
    sum += finalPrice;
    cout << "Final Price: " << finalPrice << " PKR" << endl;
}
ostream& operator<<(ostream& os, const ExecutiveSuite& room) {
    os << "Executive Suite: Price per night: " << room.price;
    return os;
}
ExecutiveSuite::~ExecutiveSuite() {
    for (int i = 0; i < 10; i++) delete[] array_for_availability[i];
    delete[] array_for_availability;
}

// --------------------- LuxuryApartment ---------------------
LuxuryApartment::LuxuryApartment() : price(50000), sum(0) {
    array_for_availability = new char*[10];
    for (int i = 0; i < 10; i++) {
        array_for_availability[i] = new char[20];
        for (int j = 0; j < 20; j++) array_for_availability[i][j] = 'A';
    }
}
void LuxuryApartment::book_a_room() {
    cout << "Enter floor (0-9): "; cin >> floor;
    cout << "Enter room number (1-20): "; cin >> roomNumber;
    if (array_for_availability[9 - floor][roomNumber - 1] == 'A') {
        array_for_availability[9 - floor][roomNumber - 1] = 'S';
        cout << "Days staying: "; cin >> days;
    } else cout << "Room already booked.\n";
}
void LuxuryApartment::available_rooms() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) cout << array_for_availability[i][j] << " ";
        cout << endl;
    }
}
void LuxuryApartment::displayPrice() {
    discount = price * days * 0.3;
    totalprice = price * days;
    finalPrice = totalprice - discount;
    sum += finalPrice;
    cout << "Final Price: " << finalPrice << " PKR" << endl;
}
ostream& operator<<(ostream& os, const LuxuryApartment& room) {
    os << "Luxury Apartment: Price per night: " << room.price;
    return os;
}
LuxuryApartment::~LuxuryApartment() {
    for (int i = 0; i < 10; i++) delete[] array_for_availability[i];
    delete[] array_for_availability;
}