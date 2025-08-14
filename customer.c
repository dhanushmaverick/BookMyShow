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
    ud->users_capacity_ = 25; // start small
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
    {
        ticket->ID_ = count++;
        ticket->isBooked_ = false;
        initialize_ticket_seat(&ticket->seat_);
        ticket->seat_.isEmpty_ = false;
    return;
    }
    else
    {
        ticket->ID_ = 0;
        if(count!= 1)
        count--;
        ticket->isBooked_ = false;
        initialize_ticket_seat(&ticket->seat_);
    }
    
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
        printf("7. Forgot Password\n");
        printf("8. Exit Program\n"); //return false
       // printf("9. Exit to Admin Version\n"); //return true //make secret
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
            edit_credentials(ud,&user);
            break;
            case 7:
            forgot_password(ud);
            break;
            case 8:
            printf("Thank you for using BookMyShow!\n");
            printf("Goodbye and see you again!\n"); 
            return 0;
            break;
            case 9:
            return 1; // secret input, for admins to access admin view
            default:
            printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 8);

}


void view_ticket(Ticket* ticket)
{
    printf("Seat Number: %d\n", ticket->seat_.number_);
    printf("Movie Details: \n");
    print_movie(&(ticket->movie_));
}

void login_user(User* user, UserDetails* ud)
{ 
     
    if (user->isLoggedIn_ || ud->user_details->isLoggedIn_)
    {
        printf("You are already logged in!\nPlease proceed to view/select/pay for seats.\n");
        return;
    }

    char username[100];
    char password[100];
    printf("Do you already have an account? [Y/N]: ");
    char opt[10];
    getchar();
    scanf("%[^\n]", opt);
    if(!(strncmp(opt,"y",1) == 0|| strncmp(opt,"Y",1) == 0))
    {
        printf("Please register first before attempting to login!\n");
        return;
    }
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
            if(ud->user_details[i].isRegistered_ != true)
            {
                printf("Invalid Username or Password.\nPlease register first before attempting to login!\n");
                return;
            }
            initialize_user_reg(user, 
            ud->user_details[i].first_name_, 
            ud->user_details[i].last_name_,  
            ud->user_details[i].number_, 
            ud->user_details[i].email_,
            ud->user_details[i].username_, 
            ud->user_details[i].password_);
            user->isLoggedIn_ = true;
            ud->user_details[i].isLoggedIn_ = true;
            printf("You Logged in Successfully!\n");
            return; 
        }
    }

    //no match was found
    printf("Invalid Username or Password\nNote: Username is firstname + lastname + ID without spaces\nPlease Try Again\n");
}





void register_user(User* user, UserDetails* ud)
{
    //take inputs for all members of user
    //call initialize_user_reg
    ensure_capacity(ud);
    //User *ud = &ud->user_details[ud->users_count_];
    if (user->isLoggedIn_ || ud->user_details->isLoggedIn_)
    {
        printf("You are already logged in!\nPlease proceed to view/select/pay for seats.\n");
        return;
    }

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
    printf("* = Unoccupied Seat\nX = Selected/Occupied Seat\n\n");
    printf("1 2 3 4 5 6 7 8 9 10...\n");
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
        if (user->tickets_[i].seat_.isEmpty_ == true)
        continue;
        // for(int j = 0; j < MAX_SEATS_; j++)
        // {
        //     if(movie->seats_[j].number_ == user->tickets_[i].seat_.number_)//&& movie->seats_[j].number_ != 0)
        //     {
        //         initialize_seat(&movie->seats_[j]);
        //         initialize_ticket(&user->tickets_[i], false);
        //     }
        // }
         int seat_no = user->tickets_[i].seat_.number_;
            if(seat_no > 0 && seat_no <= MAX_SEATS_)
            {
                // Mark the seat as available again
                initialize_seat(&movie->seats_[seat_no - 1], seat_no);
            }
            // Clear the user's ticket
            initialize_ticket(&user->tickets_[i], false);
    }
    printf("How many tickets would you like to purchase?\n");
    int tickets = 1;
    int result;
    char ch;
    int user_max_tickets = 0;
    int user_first_ticket = 0;
    for(int i = 0; i < MAX_TICKETS_; i++)
    {
        if(user->tickets_[i].seat_.isEmpty_ == true)
        {
            i = user_first_ticket;
            user_max_tickets = MAX_TICKETS_-i-1;
            break;
        }
    }
    do {
        printf("Number of tickets: ");
        result = scanf("%d", &tickets);
        if(tickets == 0)
        {
            printf("Seat selection terminated since 0 tickets selected.\n");
            return;
        }
        if (result != 1 || tickets > user_max_tickets|| tickets <= 0) {
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
            bool same_seat_error = false;
            for(int j = 0; j < i; j++)
            {
                if(user->tickets_[j].seat_.number_ == no)
                {
                    same_seat_error = true;
                    break;
                }
                else
                {
                    same_seat_error = false;
                }
            }
            if((valid != 1) || (no > MAX_SEATS_) || (no < 1) || (movie->seats_[no-1].isEmpty_ == false) || same_seat_error == true)
            {
                if(same_seat_error == true)
                printf("Please select different seats for each ticket! Cannot book same seat twice.\n");
                else
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
                user->tickets_[count].seat_.number_ = no;
                user->tickets_[count++].seat_.isEmpty_ = false;
                valid = 1;
            }
        }
        while(valid != 1);
    }
    printf("Selection Confirmed. You can now proceed to checkout if you'd like.\n");
    return;
}
void pay_for_seats(User* user, Booking_tickets* booking_tickets, int movie_index)
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
    int user_first_ticket = 0;
    double cost = 0.0;
    for(user_first_ticket = 0; user_first_ticket < MAX_TICKETS_; user_first_ticket++)
    {
        if(!user->tickets_[user_first_ticket].isBooked_)
        break;
    }
    if(user_first_ticket == 0 && user->tickets_[user_first_ticket].seat_.isEmpty_ == true)
    {
        printf("You haven't selected any seats yet! Please come back after selecting the seats.\n");
        return;
    }
    int tickets = 0;
    for(int i = user_first_ticket; i < MAX_TICKETS_; i++)
    {
        if(user->tickets_[i].seat_.isEmpty_ == false && user->tickets_[i].seat_.number_ != 0)
        {
            tickets++;
            printf("Ticket ID: %d\n",user->tickets_[i].ID_);
            printf("Movie Name: %s\n",user->tickets_[i].movie_.movie_name);
            printf("Ticket Price: %lf\n",user->tickets_[i].movie_.price);
            cost+= user->tickets_[i].movie_.price;
            user->tickets_[i].isBooked_ = true;
            printf("Seat Number: %d\n", user->tickets_[i].seat_.number_);

            // --- Update the main Booking_tickets seats array ---
            int seat_no = user->tickets_[i].seat_.number_;
            if(seat_no > 0 && seat_no <= MAX_SEATS_)
                booking_tickets->booking_movie[movie_index].seats_[seat_no-1].isEmpty_ = false;
        }
        else
        break;
    }
    printf("Number of tickets being purchased: %d\n", tickets);
    printf("Total Cost: %lf\n", cost);
    printf("Tickets successfully booked!\nPlease make the payment at the theater before your movie.\nThe ticket price is displayed on the ticket.\n");
    printf("Thank you for your purchase!\nWe wish you a great time at the cinemas :)\n");

    // --- Save the updated movie data to file ---
    save_movie_file(booking_tickets);
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
            printf("4. View Selected Seats Details\n");
            printf("5. Select different movie\n");
            printf("6. Return to Main menu\n");
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
                pay_for_seats(user, booking_tickets, movie_number); // <-- pass movie_number
                break;
                case(4):
                view_booked_tickets(user);
                break;
                case(5):
                select_movie(user, booking_tickets, &movie_number);
                break;
                case(6):
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

void edit_credentials(UserDetails* ud, User* currentUser) 
{
    // Find the index of the logged-in user
    int j = -1;
    for (int i = 0; i < ud->users_count_; i++) {
        if (ud->user_details[i].isLoggedIn_ &&
            strcmp(ud->user_details[i].username_, currentUser->username_) == 0 &&
            strcmp(ud->user_details[i].password_, currentUser->password_) == 0) 
        {
            j = i;
            break;
        }
    }

    if (j == -1) {
        printf("Please login first in order to view/edit credentials!\n");
        return;
    }

    printf("---User Credentials---\n");
    printf("Username: %s\n", ud->user_details[j].username_);
    printf("Password: %s\n", ud->user_details[j].password_);
    printf("First Name: %s\n", ud->user_details[j].first_name_);
    printf("Last Name: %s\n", ud->user_details[j].last_name_);
    printf("Phone Number: %s\n", ud->user_details[j].number_);
    printf("Email ID: %s\n", ud->user_details[j].email_);
    printf("Registration Status: %d\n", ud->user_details[j].isRegistered_);
    printf("Logged In Status: %d\n", ud->user_details[j].isLoggedIn_);
    printf("ID: %d\n", ud->user_details[j].ID_);
    printf("You can now edit your credentials.\n");

    int result = 0;
    do {
        int option = 0;
        printf("\nOptions:\n");
        printf("1. Edit first name\n");
        printf("2. Edit last name\n");
        printf("3. Edit phone number\n");
        printf("4. Edit email ID\n");
        printf("5. Edit username\n");
        printf("6. Edit password\n");
        printf("7. Save and Return to Main Menu\n");
        printf("Input: ");
        scanf("%d", &option);
        getchar(); // clear newline

        switch (option) {
            case 1:
                do {
                    printf("Enter your First Name (Current: %s): ", ud->user_details[j].first_name_);
                    scanf("%[^\n]", ud->user_details[j].first_name_);
                    getchar();
                } while (!validname(ud->user_details[j].first_name_));
                printf("First name updated.\n");
                break;

            case 2:
                do {
                    printf("Enter your Last Name (Current: %s): ", ud->user_details[j].last_name_);
                    scanf("%[^\n]", ud->user_details[j].last_name_);
                    getchar();
                } while (!validname(ud->user_details[j].last_name_));
                printf("Last name updated.\n");
                break;

            case 3:
                do {
                    printf("Enter your Phone Number (Current: %s): ", ud->user_details[j].number_);
                    scanf("%[^\n]", ud->user_details[j].number_);
                    getchar();
                } while (!validphone(ud->user_details[j].number_));
                printf("Phone number updated.\n");
                break;

            case 4:
                do {
                    printf("Enter your Email ID (Current: %s): ", ud->user_details[j].email_);
                    scanf("%[^\n]", ud->user_details[j].email_);
                    getchar();
                } while (!validemail(ud->user_details[j].email_));
                printf("Email updated.\n");
                break;

            case 5:
                snprintf(ud->user_details[j].username_, sizeof(ud->user_details[j].username_), 
                         "%s%s%d",
                         ud->user_details[j].first_name_, 
                         ud->user_details[j].last_name_, 
                         ud->user_details[j].ID_);
                printf("Username updated to %s.\n", ud->user_details[j].username_);
                break;

            case 6:
                printf("Enter your new Password: ");
                scanf("%[^\n]", ud->user_details[j].password_);
                getchar();
                printf("Password updated.\n");
                break;

            case 7:
                printf("User details saved.\n");
                save_user_file(ud);
                result = 1;
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (result != 1);
}

void view_booked_tickets(User* user)
{
    int i = 0;
    while(user->tickets_[i].isBooked_ == true)
    {
        view_ticket(&user->tickets_[i++]);
        printf("\n");
    }
    if(i == 0)
    {
        printf("No tickets have been booked yet!\nPlease proceed to payment after selecting your seats in order to bool tickets.\n");
        return;
    }
}