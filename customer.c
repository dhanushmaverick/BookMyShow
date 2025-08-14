#include "customer.h"


void initialize_user(User* user)
{
    static int count = 0;
    strcpy(user->first_name_ ,"\0");
    strcpy(user->last_name_ ,"\0");
    strcpy(user->number_ ,"\0");
    strcpy(user->email_ ,"\0");
    strcpy(user->password_ ,"\0");
    strcpy(user->username_ ,"\0");
    user->ID_ = count++;
    user->isRegistered_ = false;
    for(int i = 0; i < MAX_TICKETS_; i++)
    user->tickets_[i].isBooked_ = false;
    user->isLoggedIn_ = false;
}

void initialize_user_reg(User* user, char* first_name, char* last_name, char* number, char* email,char* username, char* password)
{
    strcpy(user->first_name_ ,first_name);
    strcpy(user->last_name_ ,last_name);
    strcpy(user->number_,number);
    strcpy(user->email_,email);
    strcpy(user->password_, password);
    strcpy(user->username_, username);
    user->isLoggedIn_ = false;
    user->isRegistered_ = true;
}


void init_user_details(UserDetails *ud) 
{
    ud->users_capacity_ = 2; // start small
    ud->users_count_ = 0;
    ud->user_details = malloc(ud->users_capacity_ * sizeof(User));
    if (!ud->user_details) 
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    load_from_userfile(ud);
}

void initialize_ticket(Ticket* ticket, bool withID)
{
    static int count = 1;
    if(withID)
    ticket->ID_ = count++;
    else
    {
        ticket->ID_ = 0;
        count--;
    }
    ticket->isBooked_ = false;
}



bool customer(Booking_tickets* booking_tickets, UserDetails* ud)
{
    User user;
    initialize_user(&user);
    system("cls");
    printf("-----Welcome to BookMyShow!-----\n");
    int choice = 0; 
    do
    {
        printf("Please choose an action below:\n");
        printf("1. User Login\n");
        printf("2. Register New User\n");
        printf("3. View Available Movies\n");
        printf("4. Book Tickets\n");
        printf("5. View Booked Tickets\n");
        printf("6. View/Edit User Credentials\n");
        printf("7. Exit Program\n"); //return false
       // printf("8. Exit to Admin Version\n"); //return true //make secret
        printf("Enter your choice: ");//entering the choice
        scanf("%d", &choice);//reading the choice from the user

        switch (choice) {
            case 1:
            login_user(&user,ud);//Login user
            break;
            case 2:
            register_user(&user,ud);//register new user
            break;
            case 3:
            list_movies(booking_tickets);
            break;
            case 4:
            book_tickets(&user, booking_tickets);//Book tickets
            break;
            case 5:
            int i = 0;
            while(i < MAX_TICKETS_ && user.tickets_[i].isBooked_ == true)
            view_ticket(&user.tickets_[i++]);
            if(i == 0)
            printf("No tickets booked yet!\n");
            break;
            case 6:
            edit_credentials(&user);
            break;
            case 7:
            printf("Thank you for using BookMyShow!\n");
            printf("Goodbye and see you again!\n"); 
            return 0;
            break;
            case 8:
            return 1; // secret input, for admins to access admin view
            default:
            printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 7);

}


void view_ticket(Ticket* ticket)
{
    printf("Seat Number: %d\n", ticket->seat_.number_);
    printf("Movie Details: \n");
    print_movie(&(ticket->movie_));
}

void login_user(User* user, UserDetails* ud)
{ 
     if (!user->isRegistered_)
            {
                printf("New users must register before attempting to login!\nPlease register yourself with us first.\n");
                return;
            }
    if (user->isLoggedIn_)
    {
        printf("You are already logged in!\nPlease proceed to view/select/pay for seats.\n");
        return;
    }

    char username[100];
    char password[100];

    printf("Please Enter Your Username: ");
    getchar();
    scanf("%[^\n]", username);

    printf("Please Enter Your Password: ");
    getchar();
    scanf("%[^\n]", password);

    for (int i = 0; i < ud->users_count_; i++)
    {
        if (strcmp(ud->user_details[i].username_, username) == 0 &&
            strcmp(ud->user_details[i].password_, password) == 0)
        {
           
            printf("You Logged in Successfully!\n");
            user->isLoggedIn_ = true;
            ud->user_details[i].isLoggedIn_ = true;
            return; 
        }
    }

    // If we reach here, no match was found
    printf("Invalid Username or Password\nNote: Username is firstname + lastname + ID without spaces\nPlease Try Again\n");
}





void register_user(User* user, UserDetails* ud)
{
    //take inputs for all members of user
    //call initialize_user_reg
    ensure_capacity(ud);
    //User *ud = &ud->user_details[ud->users_count_];

    read_firstname:
    printf("Please Enter Your First Name: ");
    getchar();
    scanf("%[^\n]", ud->user_details[ud->users_count_].first_name_);
    if (!validname(ud->user_details[ud->users_count_].first_name_)) //function call of validating name
    {
        printf("Invalid name\nEnter only characters\n");
        goto read_firstname;//if the entered name does not pass function it prints invalid and calls goto function
    }

    read_lastname:
    printf("Please Enter Your Last Name: ");
    getchar();
    scanf("%[^\n]", ud->user_details[ud->users_count_].last_name_);
    if (!validname(ud->user_details[ud->users_count_].last_name_)) //function call of validating name
    {
        printf("Invalid name\nEnter only characters\n");
        goto read_lastname;//if the entered name does not pass function it prints invalid and calls goto function
    }

    readphone:
    printf("Please Enter Your Mobile Number: ");
    getchar();
    scanf("%[^\n]", ud->user_details[ud->users_count_].number_);
    if(!validphone(ud->user_details[ud->users_count_].number_))//function call of validating phone number
    {
        printf("Invalid phone number\n");
        printf("Enter phone number(10 digits)\n");
        goto readphone;//if the entered phone number does not pass function it prints invalid and calls goto function
    }

    reademail:
    printf("Please Enter Your Mail ID: ");
    getchar();
    scanf("%[^\n]", ud->user_details[ud->users_count_].email_);
    if(!validemail(ud->user_details[ud->users_count_].email_)) //function call of validating email
    {
        printf("Invalid email_id\n");
        printf("Enter valid email_id\n");
        goto reademail;//if the entered email-id does not pass function it prints invalid and calls goto function
    }
    strcat(ud->user_details[ud->users_count_].username_,ud->user_details[ud->users_count_].first_name_); 
    strcat(ud->user_details[ud->users_count_].username_,ud->user_details[ud->users_count_].last_name_); 
    ud->user_details[ud->users_count_].ID_ = ud->users_count_ + 1;
    char id[30];
    sprintf(id, "%d", ud->user_details[ud->users_count_].ID_);
    strcat(ud->user_details[ud->users_count_].username_, id);

    printf("New User Created\n\nYour Username is Firstname + Lastname + ID\n\nUsername:%s\n", ud->user_details[ud->users_count_].username_);

    printf("Please Choose Your Password: ");
    getchar();
    scanf("%[^\n]", ud->user_details[ud->users_count_].password_);

    ud->user_details[ud->users_count_].isRegistered_ = true;
    initialize_user_reg(user, 
        ud->user_details[ud->users_count_].first_name_, 
        ud->user_details[ud->users_count_].last_name_,  
        ud->user_details[ud->users_count_].number_, 
        ud->user_details[ud->users_count_].email_,
        ud->user_details[ud->users_count_].username_, 
        ud->user_details[ud->users_count_].password_);
    ud->users_count_++;
    save_user_file(ud); // Save user details to file
    
}


void list_users(UserDetails *ud) //read from file instead of this
{
    if (ud->users_count_ == 0) 
    {
        printf("No Users Found\n");
        return;
    }
    printf("------------------------------------------------------------------Users List-----------------------------------------------------------------\n");
    printf("%-5s %-20s %-20s %-20s %-20s %-20s %-20s %-20s\n", 
           "S.No", "Firstname", "Lastname", "Number", "Email ID", "Username", "Password", "Registration");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < ud->users_count_; i++) 
    {
        printf("%-5d %-20s %-20s %-20s %-20s %-20s %-20s %-20d\n",
               i + 1,
               ud->user_details[i].first_name_,
               ud->user_details[i].last_name_,
               ud->user_details[i].number_,
               ud->user_details[i].email_,
               ud->user_details[i].username_,
               ud->user_details[i].password_,
               ud->user_details[i].isRegistered_);
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
}


void view_seats(Movies* movie)//View seats
{
    printf("Seat Number = count from left to right, increasing as you go lower\n");
    printf("* = Unoccupied Seat\nX = Occupied Seat\n\n");
    printf("0 1 2 3 4 5 6 7 8 9...\n");
    for(int i = 1; i < 6; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(movie->seats_[((i-1)*10)+j].isEmpty_ == true)
            printf("* ");
            else
            printf("X ");
        }
        printf("%d\n", (i*10));
    }
    printf("\n");
    printf("Please proceed to selecting your seats.\n");
}

void select_seats(User* user, Movies* movie)//Select seats
{
    //clear prev selection
    if(user->isRegistered_ == false)
    {
        printf("You cannot select tickets as you aren't registered!\nPlease register yourself and login in order to select seats!\n");
        return;
    }
    else if(user->isLoggedIn_ == false)
    {
        printf("Please login first in order to select seats!\n");
        return;
    }
    view_seats(movie);
    for(int i = 0; i < MAX_TICKETS_; i++)
    {
        for(int j = 0; j < MAX_SEATS_; j++)
        {
            if(movie->seats_[j].number_ == user->tickets_[i].seat_.number_)
            {
                initialize_seat(&movie->seats_[j]);
                initialize_ticket(&user->tickets_[i], false);
            }
        }
    }
    printf("How many tickets would you like to purchase?\n");
    int tickets = 1;
    int result;
    char ch;
    do {
        printf("Number of tickets: ");
        result = scanf("%d", &tickets);
        if(tickets == 0)
        {
            printf("Seat selection terminated since 0 tickets selected.\n");
            return;
        }
        if (result != 1 || tickets > MAX_TICKETS_ || tickets <= 0) {
            printf("Invalid input. Please enter a valid number of tickets, max is 10 per person.\n");
            // Clear input buffer
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    } while (result != 1);
    printf("Please choose the seat numbers:\n");
    int count = 0;
    for(int i = 0; i < tickets; i++)
    {
        int valid = 0;
        do
        {
            printf("Seat %d: ", i+1);
            int no = 0;
            valid = scanf("%d", &no);
            if((valid != 1) || (no > MAX_SEATS_) || (no < 1) || (movie->seats_[no-1].isEmpty_ == false))
            {
                printf("Invalid input. Please enter a valid unoccupied seat number.\n");
                // Clear input buffer
                while ((ch = getchar()) != '\n' && ch != EOF);
                valid = 0;
            }
            else
            {
                initialize_ticket(&user->tickets_[count], true);
                movie->seats_[no-1].isEmpty_ = false;
                user->tickets_[count].movie_ = *movie;
                user->tickets_[count++].seat_ = movie->seats_[no-1];
                valid = 1;
            }
        }
        while(valid != 1);
    }
    printf("Selection Confirmed. You can now proceed to checkout if you'd like.\n");
    return;
}
void pay_for_seats(User* user)//Pay for seats
{
    if(user->isRegistered_ == false)
    {
        printf("You cannot pay for tickets as you aren't registered!\n Please register yourself and login in order to pay!\n");
        return;
    }
    else if(user->isLoggedIn_ == false)
    {
        printf("Please login first in order to pay!\n");
        return;
    }
    int i = 0;
    double cost = 0.0;
    for(i = 0; i < MAX_TICKETS_; i++)
    {
        if(!user->tickets_[i].isBooked_)
        break;
        printf("Ticket ID: %d",user->tickets_[i].ID_);
        printf("Movie Name: %s",user->tickets_[i].movie_.movie_name);
        printf("Ticket Price: %lf",user->tickets_[i].movie_.price);
        cost+= user->tickets_[i].movie_.price;
        user->tickets_[i].isBooked_ = true;
    }
    if(i == 0)
    {
        printf("You haven't selected any seats yet! Please come back after selecting the seats.");
        return;
    }

    printf("Number of tickets being purchased: %d", i+1);
    printf("Total Cost: %lf", cost);
    printf("Please make the payment at the theater before your movie.\nThe ticket price is displayed on the ticket.");
    printf("Thank you for your purchase!\nWe wish you a great time at the cinemas :)\n");
}

void book_tickets(User* user, Booking_tickets* booking_tickets)
{
    bool booked = false;
    int movie_number = 0;
    int result = 0;
    char ch;
    select_movie(user, booking_tickets, &movie_number);
    do
    {
        do {
            int option = 0;
            printf("Options:\n");
            printf("1. View Seats\n");
            printf("2. Select/Change Seats\n");
            printf("3. Proceed to payment\n");
            printf("4. Select different movie\n");
            printf("5. Return to Main menu\n");
            printf("Input: ");
            scanf("%d", &option);
            switch(option)
            {
                case(1):
                view_seats(&booking_tickets->booking_movie[movie_number]);
                break;
                case(2):
                select_seats(user,&booking_tickets->booking_movie[movie_number]);
                break;
                case(3):
                pay_for_seats(user);
                break;
                case(4):
                select_movie(user, booking_tickets, &movie_number);
                break;
                case(5):
                booked = true;
                return;
                default:
                printf("Invalid input. Please enter a valid choice.\n");
                break;
            }
        } while (result != 1);
    }
    while(!booked);
}

void select_movie(User* user,Booking_tickets* booking_tickets, int* movie)
{
    int result = 0;
    char ch;
    printf("Please select a Movie from the list below: \n");
    list_movies(booking_tickets);
    do
    {
        printf("Movie Number: ");
        result = scanf("%d", movie);
        //printf("Result = %d",result);
        
        if (result != 1 || (*movie > booking_tickets->movies_count) || (*movie <= 0)) 
        {
            printf("Invalid input. Please enter a valid movie number.\n");
            // Clear input buffer
            while ((ch = getchar()) != '\n' && ch != EOF);
            result = 0;
        }
    }
    while(result != 1);
    *movie -= 1;
    printf("Movie %d successfully chosen.\n",*movie + 1);
    return;
}

void edit_credentials(User* user)
{
    if(user->isRegistered_ == false)
    {
        printf("Please register and login before trying to view/edit your credentials!\n");
        return;
    }
    else if(user->isLoggedIn_ == false)
    {
        printf("Please login first in order to view/edit credentials!\n");
        return;
    }
    printf("---User Credentials---\n");
    printf("Name:%-20s %-1s Phone Number: %-20s Email: %-20s Username: %-20s Password: %-20s\n",
               user->first_name_,
               user->last_name_,
               user->number_,
               user->email_,
               user->username_,
               user->password_);
               int result = 0;
    do {
            int option = 0;
            printf("Options:\n");
            //ask for password before editing
            printf("1. Edit first name\n");
            printf("2. Edit last name\n");
            printf("3. Edit phone number\n");
            printf("4. Edit email ID\n");
            printf("5. Edit username\n");
            printf("6. Edit password\n");
            printf("7. Return to Main Menu\n");
            printf("Input: ");
            scanf("%d", &option);
            switch(option)
            {
                case(1):
                //first name
                read_ref_name:
                printf("Enter your Firstname(Current: %s): ", user->first_name_);
                getchar();
                scanf("%[^\n]", user->first_name_);
                if(!validname(user->first_name_)) //function call of validating name
                {
                    printf("Invalid name\nEnter only characters\n");
                    goto read_ref_name; // if invalid, continue to re-enter
                }
                printf("First name successfully changed to %s .\n",user->first_name_);
                break;
                case(2):
                //last name
                read_rel_name:
                printf("Enter your Lastname(Current: %s): ", user->last_name_);
                getchar();
                scanf("%[^\n]", user->last_name_);
                if(!validname(user->last_name_)) //function call of validating name
                {
                    printf("Invalid name\nEnter only characters\n");
                    goto read_ref_name;; // if invalid, continue to re-enter
                }

                printf("Last name successfully changed to %s .\n",user->last_name_);
                break;
                case(3):
                //phone
                printf("Phone Number successfully changed to %s .\n",user->number_);
                break;
                case(4):
                //email
                printf("Email ID successfully changed to %s .\n",user->email_);
                case(5):
                //username
                printf("Username successfully changed to %s .\n",user->username_);
                break;
                case(6):
                //password
                printf("Password successfully changed to %s .\n",user->password_);
                break;
                case(7):
                printf("User details saved.\n");
                result = 1;
                return;
                default:
                printf("Invalid input. Please enter a valid choice.\n");
                result = 0;
                break;
            }
        } while (result != 1);
}

