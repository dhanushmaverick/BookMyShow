//-forgot username/password --> ask mobile/email  ---> display username, pass
//-edit user credentials ///
//-add occupied seats and available number of seats to csv
//-in saving and loading, take care of occcupied seats logic
//-users csv must save details

#include "admin.h"
#include "customer.h"

bool admin(Booking_tickets *Book, UserDetails *ud)
{
    //system("cls");
   // init_user_details(ud);
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
                save_movie(Book);
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
                list_users(ud);//list users
                printf("\n");
                break;
            case 6:
                return 1;
                break;
            case 7:
                printf("Saving and Exiting...\n");
                printf("Exit Successful.\n");
                save_movie(Book);
                exit(EXIT_SUCCESS);
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
        initialize_seat(&(Book->booking_movie[size].seats_[i]),i+1);
    }
    Book->movies_count++;


}

void edit_movie(Booking_tickets *book)
{
    /* Defining the logic for Edit movie */
    char str[50];
    int flag = 0;
    int option;
    int same_movie[30];
    int k = 0;
    search:
        printf("Please Enter the name of Movie to edit: ");
        getchar();//reading the name from the user based on the option
        scanf("%[^\n]", str);
    for (int i = 0; i < book->movies_count; i++)
    {
        if ((strcmp(book->booking_movie[i].movie_name, str) == 0))
        {
            same_movie[k++] = i;//increasing the k value
        }
    }
    if(k == 0)
    {
        printf("No matching Movie found\n");
        goto search;//if no matching found then again going to search option
    }
    else
    {
        printf("Found %d matching Movies:\n", k);
        for (int i = 0; i < k; i++) 
        {
            int j = same_movie[i];
            printf("Movie S.No %d\n", i+1);
            printf("Movie Name: %s\n", book->booking_movie[j].movie_name);
            printf("Movie Time: %s\n", book->booking_movie[j].movie_time);
            printf("Movie price: %lf\n", book->booking_movie[j].price);
            printf("\n");
        }
    }
    int c;
    choice:
    printf("Enter your Movie choice: ");
    scanf("%d", &c);
    if (c < 1 || c > k) 
    {
        printf("Invalid choice\n");
        goto choice;//if the choice is invalid then again going to choice option
    }
    int editindex = same_movie[c - 1];
    //if the entered choice is correct proceding to editing the selected movie
    printf("Editing Movie:\n");
    //editing name of movie
    printf("Name of Movie(current: %s): ", book->booking_movie[editindex].movie_name);
    getchar();//reading the name from the user
    scanf("%[^\n]", book->booking_movie[editindex].movie_name);

    printf("Enter the time of the Movie(current: %s): ",book->booking_movie[editindex].movie_time);
    scanf("%s", book->booking_movie[editindex].movie_time);//reading the phone number from the user
    
    printf("Enter Price of the movie(current: %lf): ", book->booking_movie[editindex].price);
    scanf("%lf",&book->booking_movie[editindex].price);//reading the email_id from the user
    
    printf("Movie updated successfully\n");
    save_movie(book); // Save updated movie details to file
}


void delete_movie(Booking_tickets *Book)
{
    char str[50];
    int same_movie[30];

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
    save_movie(Book); // Save updated movie details to file
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
        printf("-----------------------------------------------------Movie List----------------------------------------------------\n");
        //if movie count is not zero then it prints movies
        printf("%-5s %-30s %-15s %-10s %-12s %-13s %-20s\n", "S.No", "Movie Name", "Time", "Price",
                                                             "Total Seats", "Booked Seats", "Booked Seat Numbers");
        printf("-------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < book->movies_count; i++) 
        {
            int booked_seats_count = 0;
            printf("%-5d", i + 1);
            printf(" %-30s", book->booking_movie[i].movie_name);
            printf(" %-15s", book->booking_movie[i].movie_time);
            printf(" %-10.2lf", book->booking_movie[i].price);
            printf(" %-12d", MAX_SEATS_);
            for(int j = 0; j < MAX_SEATS_; j++)
            {
                if(book->booking_movie[i].seats_[j].isEmpty_ == false)
                {
                    booked_seats_count++;
                }
            }
            printf(" %-13d", booked_seats_count);
            
            for(int j = 0; j < MAX_SEATS_; j++)
            {
                if(book->booking_movie[i].seats_[j].isEmpty_ == false)
                {
                    printf("%-d, ", book->booking_movie[i].seats_[j].number_);
                }
            }
            
            printf("\n");
        }
        printf("--------------------------------------------------------------------------------------------------------------------\n");
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
    //exit(EXIT_SUCCESS); // Exit the program
}

void initialize(Booking_tickets * Book) 
{
    Book->movies_count = 0;
    //Load movies from file during initialization (After files)
    load_from_file(Book);
}

void initialize_seat(Seat* seat, int number)
{
    //static int count = 1;
    seat->number_ = number;
    seat->isEmpty_ = true;
}
void initialize_ticket_seat(Seat* seat)
{
    seat->number_ = 0;
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
        int booked_seats_count = 0;
        for(int j = 0; j < MAX_SEATS_; j++)
        {
            if(Book->booking_movie[i].seats_[j].isEmpty_ == false)
            {
                booked_seats_count++;
            }
        }
        fprintf(fptr, "%s,%s,%lf,%d,", Book->booking_movie[i].movie_name,
            Book->booking_movie[i].movie_time,
            Book->booking_movie[i].price,
            booked_seats_count);
        for(int j = 0; j < MAX_SEATS_; j++)
        {
            if(Book->booking_movie[i].seats_[j].isEmpty_ == false)
            {
                fprintf(fptr, "%d ", Book->booking_movie[i].seats_[j].number_);
            }
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);//closing the file
    printf("movies saved to file successfully\n");//printing the statment that movies are saved to file successfully
}

void load_from_file(Booking_tickets *Book)
{
    FILE* fptr = fopen("movies.csv","r");
    if (!fptr) 
    {
        printf("Error opening file for reading\n");
        return;
    }
    fscanf(fptr,"#%d\n",&Book->movies_count);
    for (int i = 0; i < Book->movies_count; i++) 
    {
        int booked_count = 0;
        char line[1024];
        fgets(line, sizeof(line), fptr);
        char *token = strtok(line, ",");
        strcpy(Book->booking_movie[i].movie_name, token);
        token = strtok(NULL, ",");
        strcpy(Book->booking_movie[i].movie_time, token);
        token = strtok(NULL, ",");
        Book->booking_movie[i].price = atof(token);
        token = strtok(NULL, ",");
        booked_count = atoi(token);

        // Initialize all seats as empty
        for(int j = 0; j < MAX_SEATS_; j++)
            initialize_seat(&(Book->booking_movie[i].seats_[j]), j + 1);

        // Read booked seat numbers
        token = strtok(NULL, "\n");
        if(token && booked_count > 0) {
            int seat_no;
            char *seat_token = strtok(token, " ");
            while(seat_token) {
                seat_no = atoi(seat_token);
                if(seat_no > 0 && seat_no <= MAX_SEATS_)
                    Book->booking_movie[i].seats_[seat_no-1].isEmpty_ = false;
                seat_token = strtok(NULL, " ");
            }
        }
    }
    fclose(fptr);
    printf("Movies loaded from file successfully\n");
}