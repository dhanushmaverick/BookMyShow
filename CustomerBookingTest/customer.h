#ifndef CUSTOMER_MAIN__H
#define CUSTOMER_MAIN__H

#include "admin.h"
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
    bool isLoggedIn_;
    int ID_; //id is the count of users registered and the unique ID
    char username_[100];
    char password_[100];
}User;

typedef struct {
    User *user_details;
    int users_count_; // track current number of users
    int users_capacity_; // track current capacity
} UserDetails;

void initialize_user(User* user);
void initialize_ticket(Ticket* ticket, bool withID);
void initialize_seat(Seat* seat);

bool customer(Booking_tickets* booking_tickets, UserDetails* ud);
bool admin(Booking_tickets *Book, UserDetails *ud);//to prevent circular inclusion

void initialize_users_start(User *user);
void login_user(User* user,UserDetails* ud);//Login user
void register_user(User* user,UserDetails* ud);//Register user
void save_user_file(UserDetails *user); //saving the user details function decleration
void list_users(UserDetails *ud);
void load_from_userfile(UserDetails *user);//loading users to file function definition
void ensure_capacity(UserDetails *ud);
void init_user_details(UserDetails *ud);//
void list_users(UserDetails *ud);

//View available movies
void book_tickets(User* user, Booking_tickets* booking_tickets);//Book tickets
void view_seats(Movies* movie);//View seats
void select_seats(User* user, Movies* movie);//Select seats
void pay_for_seats(User* user);//Pay for seats
void view_ticket(Ticket* ticket);//View ticket
void select_movie(User* user,Booking_tickets* booking_tickets, int* movie);
void edit_credentials(User* user);

int validname(char *p);
int validemail(char* email, User *user);
int validphone(char *phone, User *user);
//Exit program



#endif