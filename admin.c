

#include "admin_main.h"
#include "customer_main.h"

bool admin(Booking_tickets *Book, User *user)
{
    system("cls");
    int choice;
    do
    {
        printf("\n----------Admin Menu----------\n");
        printf("1. Create Movie\n");
        printf("2. Edit Movie\n");
        printf("3. Delete Movie\n");
        printf("4. List all Movies\n");
        printf("5. List all Users\n");
        printf("6. Exit to Customer Version\n"); //return false
        printf("7. Exit Program\n"); //return true
        printf("Enter your choice: ");//entering the choice
        scanf("%d", &choice);//reading the choice from the user

        switch (choice) {
            case 1:
            create_movie(Book);
            printf("\n");
            break;
            case 2:
            edit_movie(Book);//edit
            printf("\n");
            break;
            case 3:
            delete_movie(Book);//delete movie
            printf("\n");
            break;
            case 4:
            list_movies(Book);//list movies
            printf("\n");
            break;
            case 5:
            list_users(user);//list movies
            printf("\n");
            break;
            case 6:
            return 1;
            break;
            case 7:
            printf("Saving and Exiting...\n");
            printf("Exit Successful.\n");
            save_movie(Book);
            break;
            default:
            printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 6);
}

void valid_price(Booking_tickets *Book, int index) 
{
    char buffer[100];
    int valid;

    while (1) 
    {
        printf("Enter the Movie Price: ");
        scanf(" %[^\n]", buffer); // Read entire line as string

        valid = 1;
        int dot_count = 0;

        for (int i = 0; buffer[i] != '\0'; i++) 
        {
            if (buffer[i] == '.') 
            {
                dot_count++;
                if (dot_count > 1) 
                {
                    valid = 0; // More than one decimal
                    break;
                }
            }
            else if (!isdigit((unsigned char)buffer[i])) 
            {
                valid = 0; // Non-digit character found
                break;
            }
        }

        if (valid) 
        {
            double value = atof(buffer);
            if (value > 0) 
            {
                Book->booking_movie[index].price = value;
                break; // Exit after valid input
            } else 
            {
                printf("Price must be greater than 0.\n");
            }
        } 
        else 
        {
            printf("Invalid input. Please enter only numbers.\n");
        }
    }
}

void create_movie(Booking_tickets *Book)//create movie function decleration
{
    int size = Book->movies_count;
    printf("Enter the Movie Name:");
    scanf(" %[^\n]",Book->booking_movie[size].movie_name);

    printf("Enter the Movie Time:");
    scanf(" %[^\n]",Book->booking_movie[size].movie_time);

    valid_price(Book, size);
    
    for(int i = 0; i < MAX_SEATS_; i++)
    {
        initialize_seat(&(Book->booking_movie[size].seats_[i]));
    }
    Book->movies_count++;


}

void edit_movie(Booking_tickets *book)
{


}


void delete_movie(Booking_tickets *Book)
{
    char str[50];
    //int option;
    int same_movie[30];
    //printf("Delete Movie by:\n1. Movie_name\nEnter option: ");
    //scanf("%d", &option);

    printf("Enter the Movie: ");
    getchar();//reading the input from the user
    scanf("%[^\n]", str);
    int k=0;
    for (int i = 0; i < Book->movies_count; i++)
    {
        if(strcmp(Book->booking_movie[i].movie_name, str) == 0)
        {
            same_movie[k++] = i;//increasing the k value
        }
    }
    if(k == 0)
    {
        printf("No matching Movie found\n");//if the k value is zero then prints the below statement
    }
    else
    {
        //if the k value is not zero then prints the booking_movie 
        printf("Found %d matching movies:\n", k);
        for (int i = 0; i < k; i++) 
        {
            int j = same_movie[i];
            printf("Movie S.No %d\n", i+1);
            printf("Movie_name: %s\n", Book->booking_movie[j].movie_name);
            printf("Movie_time: %s\n", Book->booking_movie[j].movie_time);
            printf("Price: %lf\n", Book->booking_movie[j].price);
            printf("\n");
        }
    }
    int c;
    printf("Enter your Movie choice to delete: ");
    scanf("%d", &c);//giving the promt to select which contact to delete
    if (c < 1 || c > k) 
    {
        printf("Invalid choice.\n");//if the movie choice is not listed then printing invalid
    }
    int index = same_movie[c - 1];
    
    for (int i = index; i < Book->movies_count - 1; i++) 
    {
        Book->booking_movie[i] = Book->booking_movie[i + 1];
    }
    Book->movies_count--;//decreasing the movie count
    printf("Movie deleted successfully.\n");
}


void list_movies(Booking_tickets * book)
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



void print_movie(Movies* movie)
{
    printf("Movie_name: %s\n", movie->movie_name);
    printf("Movie_time: %s\n", movie->movie_time);
    printf("Price: %lf\n", movie->price);
    printf("\n");
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

void initialize_seat(Seat* seat)
{
    static int count = 1;
    seat->number_ = count++;
    seat->isEmpty_ = true;
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


