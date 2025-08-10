
#include "main.h"

void create_movie(Booking_tickets *Book)//create movie function decleration
{
    printf("Enter the Movie Name:");
    scanf(" %[^\n]",Book->booking_movie->movie_name);

    printf("Enter the Movie Time:");
    scanf(" %[^\n]",Book->booking_movie->movie_time);

    printf("Enter the Movie Price:");
    scanf(" %[^\n]",&Book->booking_movie->price);

}


void edit_movie(Booking_tickets *book)
{


}


void delete_movie(Booking_tickets *book)
{


}


void list_movie(Booking_tickets * book)
{
    if (book->movies_count == 0)
    {
        printf("No movies available\n");//if the movie is zero it prints no movies
    } 
    else 
    {
        //if movie count is not zero then it prints the name,phone number and email of the movies
        for (int i = 0; i < book->movies_count; i++) 
        {
            printf("--------------------Movie List-------------------");
            printf("Movie: %d:\n", i + 1);
            printf("Movie: %s\n", book->movies[i].);
            printf("Time: %s\n", book->movies[i].phone);
            printf("Price: %s\n", book->movies[i].email);
            printf("\n");
        }
    }
}

void save_movie(Booking_tickets * book)
{
    save_movie_file(book); // Save movies to file
    exit(EXIT_SUCCESS); // Exit the program
}

void save_movie_file(Booking_tickets *book) //save to file definition
{
    FILE* fptr = fopen("movies.csv","w+");//opening the file
    if (!fptr) 
    {
        printf("Error opening file for writing\n");//printing the error if the file is not opened
    }
    fprintf(fptr,"#%d\n", book->movies_count);//printing the number of movies in address book
    for (int i = 0; i < book->movies_count ;i++) 
    {
        //printing the name,phone number and mail in the file 
        fprintf(fptr, "%s,%s,%d\n", book->booking_movie[i].movie_name,book->booking_movie[i].movie_time,book->booking_movie[i].price);
    }
    fclose(fptr);//closing the file
    printf("movies saved to file successfully\n");//printing the statment that movies are saved to file successfully
}

