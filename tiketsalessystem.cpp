


#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
#include<vector>
#include <conio.h>
using namespace std;

const int ROWS = 15;
const int COLUMNS = 30;
const int NUM_PROGRAMS = 2;
const string ADMIN_USERNAME = "ADMIN";
const string ADMIN_PASSWORD = "123";
const string MANAGER_USERNAME = "MANAGER";
const string MANAGER_PASSWORD = "123";
const int PROGRAM_ZEN = 1;
const int PROGRAM_LION = 2;
const int MAX_BOOKINGS = ROWS * COLUMNS;
const string PROMO_CODE = "DISCOUNT10";
struct customerDetails
{
    string name;
    string email;
    string paymentMethod;
    double price;
    int program;
    int row;
    int col;

};

vector<customerDetails> customerDetailsVector;

bool seats_2[ROWS][COLUMNS] = { false };
bool seats_1[ROWS][COLUMNS] = { false };
const double SEAT_PRICES[ROWS] = { 14, 14, 14, 14, 14, 19, 19, 19, 19, 19, 23, 23, 23, 23, 23 };
double total_payment = 0;
int num_seats, selected_row, selected_col, seats_sold = 0;
double total_payment2 = 0;
int num_seats2, selected_row2, selected_col2, seats_sold2 = 0;
int bookingsCount = 0;

bool logged_in = false;
int choice, manager_choice, administrator_choice, seating_choice;
string manager_username, manager_password;


void clearsys()
{
    system("cls");
}

void displayWelcomeMessage()
{
    cout << "\033[1;31mWelcome to the Ticket Sales System by SURYADEV V.S\033[0m" << endl;
}

void display_error()
{
    cout << "Invalid input. Please enter a valid option" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}



bool display_ticketsales()
{

    cout << "1. Administrator Login " << endl;
    cout << "2. Manager Login " << endl;
    cout << "3. Exit " << endl;
    cout << "Enter Your Choice: ";

    if (!(cin >> choice) || choice < 1 || choice > 3)
    {
        cout << "Invalid choice. Please enter a valid option." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    return true;
}

void seatingchartfor_zen()
{

    cout << "Seating chart for The Zen Substitute:" << endl;

    cout << setw(7) << " ";

    for (int col = 0; col < COLUMNS; col++)

    {

        cout << setw(2) << col + 1 << " ";

    }

    cout << endl;

    for (int row = 0; row < ROWS; row++)

    {

        cout << "row " << setw(2) << (row + 1) << ": ";

        for (int col = 0; col < COLUMNS; col++)

            if (seats_1[row][col])
            {
                cout << "\033[1;31m#  \033[0m";
            }

            else

            {
                cout << "\033[1;34m@  \033[0m";
            }

        cout << endl;

    }

}

void seatingchartfor_lion()
{
    cout << "Seating chart for Lion And The Jewel:" << endl;
    cout << setw(7) << " ";
    for (int col = 0; col < COLUMNS; col++)
    {
        cout << setw(2) << col + 1 << " ";
    }
    cout << endl;
    for (int row = 0; row < ROWS; row++)
    {
        cout << "row " << setw(2) << (row + 1) << ": ";
        for (int col = 0; col < COLUMNS; col++)
            if (seats_2[row][col])
            {
                cout << "\033[1;31m#  \033[0m";
            }
            else
            {
                cout << "\033[1;34m@  \033[0m";
            }
        cout << endl;
    }
}

void writeBookingDetailsToFile() {
    ofstream outputFile("booking_details.txt");

    if (!outputFile.is_open()) {
        cout << "Error: Unable to open the file for writing." << endl;
        return;
    }

    outputFile << "Booking Details:" << endl;

    for (int i = 0; i < bookingsCount; ++i)
    {
        customerDetails customer;
        outputFile << "Booking ID " << i + 1 << ":" << endl;
        outputFile << "Name: " << customerDetailsVector[i].name << endl;
        outputFile << "Email: " << customerDetailsVector[i].email << endl;
        outputFile << "Payment Method: " << customerDetailsVector[i].paymentMethod << endl;
        outputFile << "Program: ";

        if (customerDetailsVector[i].program == PROGRAM_ZEN)
        {
            outputFile << "The Zen Substitute" << endl;
        }
        else
        {
            if (customerDetailsVector[i].program == PROGRAM_LION)
            {
                outputFile << "Lion And The Jewel" << endl;
            }

            outputFile << "Seat Details - Row: " << customerDetailsVector[i].row << endl
                << " | Column: " << customerDetailsVector[i].col << endl
                << " | Price: " << customerDetailsVector[i].price << " RM" << endl;
            outputFile << "Payment: " << customerDetailsVector[i].price << " RM" << endl;

            outputFile << "------------------------" << endl;

        }
        outputFile << "------------------------" << endl;
    }

    outputFile.close();
}

bool bookseatsfor_zen()
{

    cout << "Enter number of seats to book for the program The Zen Substitute : ";
    if (!(cin >> num_seats))
    {
        display_error();
        return false;
    }

    if (num_seats <= 0)
    {
        cout << "Invalid input. Please enter a positive integer." << endl;

        return false;
    }



    for (int j = 0; j < num_seats; j++)
    {
        customerDetails customer;
        cout << "Enter your name: ";
        cin >> customer.name;

        cout << "Enter your email ID: ";
        cin >> customer.email;

        cout << "Enter payment method (cash or card): ";
        cin >> customer.paymentMethod;

        cout << "Seat prices (per row): " << endl;
        for (int row = 0; row < ROWS; row++)
        {
            cout << "row " << row + 1 << ": RM" << SEAT_PRICES[row] << endl;
        }

        cout << "Enter the row number: ";

        if (!(cin >> selected_row))
        {
            display_error();
            j--; // to retry booking
            continue;
        }

        cout << "Enter the seat number: ";

        if (!(cin >> selected_col))
        {
            display_error();
            j--;
            continue;
        }

        if (selected_row >= 1 && selected_row <= ROWS && selected_col >= 1 && selected_col <= COLUMNS && !seats_1[selected_row - 1][selected_col - 1])
        {
            seats_1[selected_row - 1][selected_col - 1] = true;
            seats_sold++;
            customer.program = PROGRAM_ZEN;
            customer.row = selected_row;
            customer.col = selected_col;
            customer.price = SEAT_PRICES[selected_row - 1];
            cout << "Enter promo code (if any): ";
            string enteredPromoCode;
            cin >> enteredPromoCode;

            if (enteredPromoCode == PROMO_CODE)
            {
                clearsys();
                customer.price -= 10;
                cout << "Promo code applied! You get a discount of 10 RM." << endl;
            }

            customerDetailsVector.push_back(customer);
            total_payment += SEAT_PRICES[selected_row - 1];

            cout << "Row:" << selected_row << " Seat:" << selected_col << " booked successfully!" << endl;
            cout << "Price: " << customer.price << " RM" << endl;
            cout << "Dear " << customer.name << " thank you for booking with us." << endl;
            cout << "Your Booking ID is: " << bookingsCount + 1 << endl;
            cout << "Please remember your Booking ID to cancel your booking." << endl;
            cout << "Tickets will be available for collection at the counter."
                << " also will be sent to:" << customer.email << "\n"
                << "Have a great day!" << "\n" "\n" << endl;

            bookingsCount++;
            writeBookingDetailsToFile();

        }
        else
        {
            cout << "Invalid seat selection. Please try again!" << endl;
            j--;
        }
    }
    return true;
}

bool bookseatsfor_lion()
{

    cout << "Enter number of seats to book for Lion And The Jewel : ";
    if (!(cin >> num_seats2))
    {
        display_error();
        return false;
    }

    if (num_seats2 <= 0)
    {
        cout << "Invalid input. Please enter a positive integer." << endl;

        return false;
    }

    for (int j = 0; j < num_seats2; j++)
    {
        customerDetails customer;
        cout << "Enter your name: ";
        cin >> customer.name;

        cout << "Enter your email ID: ";
        cin >> customer.email;

        cout << "Enter payment method (cash or card): ";
        cin >> customer.paymentMethod;

        cout << "Seat prices (per row): " << endl;
        for (int row = 0; row < ROWS; row++)
        {
            cout << "row " << row + 1 << ": RM" << SEAT_PRICES[row] << endl;
        }

        cout << "Enter the row number: ";

        if (!(cin >> selected_row2) || selected_row2 < 1 || selected_row2 > ROWS)
        {
            display_error();
            j--;
            continue;
        }

        cout << "Enter the seat number: ";

        if (!(cin >> selected_col2) || selected_col2 < 1 || selected_col2 > COLUMNS)
        {
            display_error();
            j--;
            continue;
        }

        if (!seats_2[selected_row2 - 1][selected_col2 - 1])
        {
            seats_2[selected_row2 - 1][selected_col2 - 1] = true;
            seats_sold2++;
            customer.program = PROGRAM_LION;
            customer.row = selected_row2;
            customer.col = selected_col2;
            customer.price = SEAT_PRICES[selected_row2 - 1];

            cout << "Enter promo code (if any): ";
            string enteredPromoCode;
            cin >> enteredPromoCode;
            if (enteredPromoCode == PROMO_CODE)
            {
                clearsys();
                customer.price -= 10;
                cout << "Promo code applied! You get a discount of 10 RM." << endl;
            }

            customerDetailsVector.push_back(customer);
            total_payment += SEAT_PRICES[selected_row - 1];
            cout << "Row:" << selected_row2 << " Seat:" << selected_col2 << " booked successfully!" << endl;
            cout << "Price: " << customer.price << " RM" << endl;
            cout << "Dear " << customer.name << " thank you for booking with us." << endl;
            cout << "Your booking ID is: " << bookingsCount + 1 << endl;
            cout << "Please remember your booking ID to cancel your booking." << endl;
            cout << "Tickets will be available for collection at the counter."
                << " also will be sent to :" << customer.email << "\n"
                << "Have a great day!" << "\n" "\n" << endl;
            bookingsCount++;

            writeBookingDetailsToFile();

        }
        else
        {
            cout << "Invalid seat selection. The seat is already booked. Please try again!" << endl;
            j--;
        }
    }
    return true;
}
void cancelBooking()
{
    clearsys();

    if (bookingsCount == 0)
    {
        cout << "No bookings to cancel." << endl;
        return;
    }

    cout << "Enter booking ID to cancel (1 to " << bookingsCount << "): ";
    int cancelChoice;
    if (!(cin >> cancelChoice) || cancelChoice < 1 || cancelChoice > bookingsCount)
    {
        display_error();
        return;
    }

    // Decrement cancelChoice to match the vector 
    cancelChoice--;

    customerDetails canceledBooking = customerDetailsVector[cancelChoice];

    if (canceledBooking.program == PROGRAM_ZEN)
    {
        seats_1[canceledBooking.row - 1][canceledBooking.col - 1] = false;
        seats_sold--;
        total_payment -= canceledBooking.price;
    }
    else if (canceledBooking.program == PROGRAM_LION)
    {
        seats_2[canceledBooking.row - 1][canceledBooking.col - 1] = false;
        seats_sold2--;
        total_payment2 -= canceledBooking.price;
    }

    // TO Remove canceled booking from the vector
    customerDetailsVector.erase(customerDetailsVector.begin() + cancelChoice);

    bookingsCount--;

    cout << "Booking canceled! Collect your refund from the counter " << endl;
    writeBookingDetailsToFile();
}

void viewCustomerDetails()
{
    clearsys();
    cout << "Customer Details:" << endl;
    for (int i = 0; i < bookingsCount; ++i) {
        cout << "Booking ID " << i + 1 << ":" << endl;
        cout << "Name: " << customerDetailsVector[i].name << endl;
        cout << "Email: " << customerDetailsVector[i].email << endl;
        cout << "Payment Method: " << customerDetailsVector[i].paymentMethod << endl;
        cout << "Program: ";

        if (customerDetailsVector[i].program == PROGRAM_ZEN)
        {
            cout << "The Zen Substitute" << endl;
            cout << "Seat Details - Row: " << customerDetailsVector[i].row
                << " | Seat: " << customerDetailsVector[i].col
                << " | Price: " << customerDetailsVector[i].price << " RM" << endl;


            cout << "------------------------" << endl;
        }
        else
        {
            if (customerDetailsVector[i].program == PROGRAM_LION)
            {
                cout << "Lion And The Jewel" << endl;
            }

            cout << "Seat Details - Row: " << customerDetailsVector[i].row
                << " | Seat: " << customerDetailsVector[i].col
                << " | Price: " << customerDetailsVector[i].price << " RM" << endl;


            cout << "------------------------" << endl;

        }

        cout << "------------------------" << endl;
    }
}
void display_managerlogin()
{
    cout << "Enter Manager Username: ";
    cin >> manager_username;

    cout << "Enter Manager Password: ";

    char ch;
    manager_password = "";

    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!manager_password.empty())
            {
                cout << "\b \b";
                manager_password.pop_back();
            }
        }
        else
        {
            cout << '*';
            manager_password += ch;
        }
    }

    cout << endl;

    if (manager_username == MANAGER_USERNAME && manager_password == MANAGER_PASSWORD)
    {
        logged_in = true;
        while (logged_in)
        {
            cout << "Manager Menu " << endl;
            cout << "1. View Overall Payments Collected " << endl;
            cout << "2. View Total Number Of Seats Sold " << endl;
            cout << "3. Display seating chart " << endl;
            cout << "4. View Payment Details " << endl;
            cout << "5. Exit " << endl;
            cout << "Enter your choice: ";

            int manager_choice;
            if (!(cin >> manager_choice))
            {
                display_error();
                continue;
            }

            switch (manager_choice)
            {
            case 1:
                cout << "Overall Payments Collected: " << total_payment + total_payment2 << endl;
                break;
            case 2:
                cout << "Total Number Of Seats Sold: " << seats_sold + seats_sold2 << endl;
                break;

            case 3:
                cout << "Seating chart Menu " << endl;
                cout << "1. Display seating chart for The Zen Substitute" << endl;
                cout << "2. Display seating chart for Lion And The Jewel" << endl;
                cout << "3. exit" << endl;
                cout << "Enter your choice: ";

                if (!(cin >> seating_choice))
                {
                    display_error();
                }
                else {
                    switch (seating_choice)
                    {
                    case 1:
                        seatingchartfor_zen();
                        break;
                    case 2:
                        seatingchartfor_lion();
                        break;
                    case 3:
                        logged_in = false;
                        break;
                    default:
                        display_error();
                        break;
                    }
                }
                break;
            case 4:
                viewCustomerDetails();
                break;
            case 5:
                logged_in = false;
                break;
            default:
                display_error();
                break;
            }
        }
    }
}

void display_administratorlogin()
{
    string admin_user, admin_password;

    cout << "Enter Administrator Username: ";
    cin >> admin_user;

    cout << "Enter Administrator Password: ";

    char ch;
    admin_password = "";

    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!admin_password.empty())
            {
                cout << "\b \b";
                admin_password.pop_back();
            }
        }
        else
        {
            cout << '*';
            admin_password += ch;
        }
    }

    cout << endl;


    if (admin_user == ADMIN_USERNAME && admin_password == ADMIN_PASSWORD)
    {
        logged_in = true;
        clearsys();

        while (logged_in)
        {
            cout << "Administrator Menu " << endl;
            cout << "1. Display seating chart " << endl;
            cout << "2. Book Seats" << endl;
            cout << "3. Cancel Booking" << endl;
            cout << "4. View Payment Details " << endl;
            cout << "5. View Customer Details" << endl;
            cout << "6. Exit " << endl;
            cout << "Enter Your Choice: ";

            int administrator_choice;
            if (!(cin >> administrator_choice))
            {
                display_error();
                continue;
            }

            switch (administrator_choice)
            {
            case 1:
                clearsys();
                cout << "Seating chart Menu " << endl;
                cout << "1. Display seating chart for The Zen Substitute" << endl;
                cout << "2. Display seating chart for Lion And The Jewel" << endl;
                cout << "3. exit" << endl;
                cout << "Enter your choice: ";

                if (!(cin >> seating_choice))
                {
                    display_error();
                }
                else
                {
                    switch (seating_choice)
                    {
                    case 1:
                        clearsys();
                        seatingchartfor_zen();
                        break;
                    case 2:
                        clearsys();
                        seatingchartfor_lion();
                        break;
                    case 3:
                        clearsys();
                        logged_in = false;
                        break;
                    default:
                        display_error();
                        break;
                    }
                }
                break;
            case 2:

                clearsys();
                cout << "Select a program to book tickets:" << endl;
                cout << "1. The Zen Substitute" << endl;
                cout << "2. Lion And The Jewel" << endl;
                cout << "Enter your choice: ";

                int booking_program_choice;
                if (!(cin >> booking_program_choice) || booking_program_choice < 1 || booking_program_choice > NUM_PROGRAMS)
                {
                    display_error();
                    break;
                }

                seating_choice = booking_program_choice;


                if (seating_choice == 1)
                {
                    clearsys();
                    bookseatsfor_zen();
                }
                else if (seating_choice == 2)
                {
                    clearsys();
                    bookseatsfor_lion();
                }
                else
                {
                    cout << "Invalid program choice." << endl;
                }
                break;
            case 3:
                cancelBooking();
                break;

            case 4:
                cout << "Payment Details:" << endl;
                for (int i = 0; i < seats_sold + seats_sold2; ++i)
                {
                    cout << "Row: " << i + 1 << " | Program: ";
                    if (i < seats_sold)
                    {
                        cout << "The Zen Substitute";
                        cout << " | Seat: " << customerDetailsVector[i].col
                            << " | Price: " << customerDetailsVector[i].price << " RM"
                            << " | Payment: " << customerDetailsVector[i].paymentMethod << endl;
                    }
                    else
                    {
                        cout << "Lion And The Jewel";
                        cout << " | Seat: " << customerDetailsVector[i - seats_sold].col
                            << " | Price: " << customerDetailsVector[i - seats_sold].price << " RM"
                            << " | Payment: " << customerDetailsVector[i - seats_sold].paymentMethod << endl;
                    }
                }
                break;
            case 5:
                viewCustomerDetails();
                break;
            case 6:
                logged_in = false;
                break;
            default:

                display_error();
                break;
            }
        }
    }
    else
    {
        cout << "Invalid username or password. Please try again." << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main()
{
    displayWelcomeMessage();

    while (true)
    {
        if (!display_ticketsales())
        {
            continue;
        }

        switch (choice)
        {
        case 1:
            display_administratorlogin();
            break;
        case 2:
            display_managerlogin();
            break;
        case 3:
            cout << "Exiting the program" << endl;
            return 0;
        default:
            display_error();
            break;
        }
    }
}