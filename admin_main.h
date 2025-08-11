#ifndef MAIN_H
#define MAIN_H

#define MAX_MOVIES 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//structure decleration 
typedef struct {
    char movie_name[50];
    char movie_time[5];
    double price;
} Movies;

typedef struct {
    Movies booking_movie[MAX_MOVIES];
    int movies_count;
} Booking_tickets;


//functions
void create_movie(Booking_tickets *Book);//create function decleration
void edit_movie(Booking_tickets *Book);
void delete_movie(Booking_tickets *Book);
void list_movie(Booking_tickets * Book);
void save_movie(Booking_tickets * Book);
void save_movie_file(Booking_tickets *Book);//save to file
void load_from_file(Booking_tickets *Book);//load movies to file 
void initialize(Booking_tickets *Book); 


#endif