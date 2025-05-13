#ifndef HOTELROOM_H
#define HOTELROOM_H

#include <iostream>
using namespace std;

class HotelRoom {
protected:
    int floor, roomNumber;
public:
    HotelRoom();
    virtual void book_a_room() = 0;
    virtual void available_rooms() = 0;
    virtual void displayPrice() = 0;
    virtual ~HotelRoom();
};

class Standard : public HotelRoom {
public:
    int price, discount, totalprice, finalPrice, days, sum;
    char** array_for_availability;

    Standard();
    void book_a_room();
    void available_rooms();
    void displayPrice();
    friend ostream& operator<<(ostream&, const Standard&);
    ~Standard();
};

class Deluxe : public HotelRoom {
public:
    int price, discount, totalprice, finalPrice, days, sum;
    char** array_for_availability;

    Deluxe();
    void book_a_room();
    void available_rooms();
    void displayPrice();
    friend ostream& operator<<(ostream&, const Deluxe&);
    ~Deluxe();
};

class Suite : public HotelRoom {
public:
    int price, discount, totalprice, finalPrice, days, sum;
    char** array_for_availability;

    Suite();
    void book_a_room();
    void available_rooms();
    void displayPrice();
    friend ostream& operator<<(ostream&, const Suite&);
    ~Suite();
};

class ExecutiveSuite : public HotelRoom {
public:
    int price, discount, totalprice, finalPrice, days, sum;
    char** array_for_availability;

    ExecutiveSuite();
    void book_a_room();
    void available_rooms();
    void displayPrice();
    friend ostream& operator<<(ostream&, const ExecutiveSuite&);
    ~ExecutiveSuite();
};

class LuxuryApartment : public HotelRoom {
public:
    int price, discount, totalprice, finalPrice, days, sum;
    char** array_for_availability;

    LuxuryApartment();
    void book_a_room();
    void available_rooms();
    void displayPrice();
    friend ostream& operator<<(ostream&, const LuxuryApartment&);
    ~LuxuryApartment();
};

#endif