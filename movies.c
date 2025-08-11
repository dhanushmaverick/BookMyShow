
#include "main.h"

void create_movie(Booking_tickets *Book)//create movie function decleration
{
    int size = Book->movies_count;
    printf("Enter the Movie Name:");
    scanf(" %[^\n]",Book->booking_movie[size].movie_name);

    printf("Enter the Movie Time:");
    scanf(" %[^\n]",Book->booking_movie[size].movie_time);

    printf("Enter the Movie Price:");
    scanf(" %lf",&Book->booking_movie[size].price);
    
    Book->movies_count++;

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
        printf("----------------------------Movie List---------------------------\n");
        //if movie count is not zero then it prints movies
        printf("%-5s %-30s %-15s %-10s\n", "S.No", "Movie Name", "Time", "Price");
        printf("-----------------------------------------------------------------\n");
        for (int i = 0; i < book->movies_count; i++) 
        {
            printf("%-5d", i + 1);
            printf(" %-30s", book->booking_movie[i].movie_name);
            printf(" %-15s", book->booking_movie[i].movie_time);
            printf(" %-10.3lf", book->booking_movie[i].price);
            printf("\n");
        }
        printf("-----------------------------------------------------------------\n");
    }
}

void save_movie(Booking_tickets * Book)
{
    save_movie_file(Book); // Save movies to file
    exit(EXIT_SUCCESS); // Exit the program
}

void initialize(Booking_tickets * Book) 
{
    Book->movies_count = 0;
    //Load movies from file during initialization (After files)
    load_from_file(Book);
}

void save_movie_file(Booking_tickets *Book) //save to file definition
{
    FILE* fptr = fopen("movies.csv","w+");//opening the file
    if (!fptr) 
    {
        printf("Error opening file for writing\n");//printing the error if the file is not opened
    }
    fprintf(fptr,"#%d\n", Book->movies_count);//printing the number of movies in address book
    for (int i = 0; i < Book->movies_count ;i++) 
    {
        //printing  in the file 
        fprintf(fptr, "%s,%s,%lf\n", Book->booking_movie[i].movie_name,Book->booking_movie[i].movie_time,Book->booking_movie[i].price);
    }
    fclose(fptr);//closing the file
    printf("movies saved to file successfully\n");//printing the statment that movies are saved to file successfully
}

void load_from_file(Booking_tickets *Book)//load movies to file function definition 
{
    FILE* fptr = fopen("movies.csv","r");//opening the file in read format
    if (!fptr) 
    {
        printf("Error opening file for reading\n");//printing error opening if file doesn't opened
    }
    fscanf(fptr,"#%d\n",&Book->movies_count);
    for (int i = 0; i < Book->movies_count; i++) 
    {

        fscanf(fptr, "%[^,],",Book->booking_movie[i].movie_name);
        fscanf(fptr, "%[^,],", Book->booking_movie[i].movie_time);
        fscanf(fptr, "%lf\n", &Book->booking_movie[i].price);
    }
    fclose(fptr);//closing the file
    printf("Movies loaded from file successfully\n");
}