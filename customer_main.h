#ifndef CUSTOMER_MAIN__C
#define CUSTOMER_MAIN__C

#include "admin_main.h"
#include <stdbool.h>
#include <string.h>

#define MAX_SEATS_ 50
#define MAX_TICKETS_ 10


typedef struct{
    Seat seat_;
    int ID_;
    bool isBooked_;
    Movies movie_;
}Ticket;

typedef struct{
    Ticket tickets_[MAX_TICKETS_];
    char first_name_[100];
    char last_name_[100];
    char number_[20];
    char email_[100];
    bool isRegistered_;

    char username[100];
    char password_[100];
    int count;
}User;

void initialize_user(User* user);
void initialize_ticket(Ticket* ticket);
void initialize_seat(Seat* seat);

bool customer_main(Booking_tickets*);
void login_user(User* user);//Login user
void register_user(User* user);//Register user
void save_user_file(User *user); //saving the user details function decleration

    //View available movies
    void book_tickets(User* user, Booking_tickets* booking_tickets);//Book tickets
    void view_seats(Movies* movie);//View seats
    void select_seats(User* user, Movies* movie);//Select seats
    void pay_for_seats(User* user);//Pay for seats
    void view_ticket(Ticket* ticket);//View ticket
    //Exit program


#endif