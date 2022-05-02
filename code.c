/*
Varun Grover @lasallecollege
Student ID: 2130884

Algorithm and Programming - Sem 1 
- Final Project - Books Inventory
dummy data for books - https://gist.github.com/nanotaboada/6396437
*/

#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct book{
    int isbn;
    char title[50];
    char author[50];
    char publisher[50];
    char genre[50];
    int year_of_publication;
    int stock;
    int price;
} book;

// array to store books
book library[500] = {
        {97815, "Eolquent JavaScript, Third Edition", "Marijn Haverbeke", "No Starch Press", "Education", 2018, 5, 20},
        {97816, "Practical", "Nicolás Bevacqua", "O'Reilly Media", "Education", 2017, 5, 40},
        {97817, "Understanding ECMAScript 6", "Nicholas C. Zakas", "No Starch Press", "Education", 2016, 10, 10},
        {97818, "Speaking JavaScript", "Axel Rauschmayer", "O'Reilly Media", "Education", 2018, 15, 20}
}; 

// keeps track off books in library array
int available_books = 4;


// function declarations
int print_menu();
void add_new_book();
void search_book();
void transaction(int);
void delete_book_input();
void delete_book(int);
void show_books();
void print_book(int);
void issue_book(int);
void return_book(int);
void clear_buffer();
void clear_screen();
void menu_caller();

// main function
int main(){
    clear_screen();

    int option = print_menu();
   
    switch(option){
        case 1: add_new_book();
            break;
        case 2: search_book();
            break;
        case 3: search_book();
            break;
        case 4: delete_book_input();
            break;
        case 5: show_books();
            break;
        case 6: 
            printf("\n\nEXITING THE SYSTEM....");
            exit(0);
            break;
    }

    return 0;
}

// function definitions
int print_menu(){
    int option;

    printf("\n\t\tBooks Inventory");
    printf("\nPlease select the option to proceed: ");
    printf("\n1. Populate the inventory\n2. Search by Keyword\n3. Process a transaction\n4. Delete a book record\n5. Display all the books in the inventory\n6. Exit the system");
    printf("\nYour choice: ");
    scanf("%d", &option);

    return option;
}

void show_books(){
    clear_screen();

    printf("\n\t\tBooks Details");

    for(int i=0; i<available_books; i++){
        printf("\n\nBook #%d",i+1);
        print_book(i);
    }

    printf("\n------------------------------\n");

    menu_caller();
}

// function to print 1 book
void print_book(int i){
    printf("\nISBN : %d", library[i].isbn);
    printf("\nTitle : %s", library[i].title);
    printf("\nAuthor : %s", library[i].author);
    printf("\nPublisher : %s", library[i].publisher);
    printf("\nGenre : %s", library[i].genre);
    printf("\nYear of Publication : %d", library[i].year_of_publication);
    printf("\nAmount in Stock : %d", library[i].stock);
    printf("\nSelling Price : $%d", library[i].price);
}

void add_new_book(){
    clear_screen();
    
    printf("\n\t\tADD NEW BOOK");

    for(int i=available_books; i<500; i++){
        // checking space in array to store book
        if(i==500){
            printf("\nNo more books can be added!!");
            main();
            break;
        }

        printf("\n\nEnter the details to add new book:");

        // unique ISBN
        bool isSame;
        do{
            printf("\nISBN : ");
            clear_buffer();
            scanf("%d", &library[i].isbn);

            isSame = false;

            for(int j=0; j<available_books; j++){
                if(library[j].isbn == library[i].isbn){
                    isSame = true;
                    printf("\nWrong ISBN entered.... Book already existed");
                    break;
                }
            }
        }while(isSame);

        printf("\nTitle : ");
        clear_buffer();
        fgets(library[i].title, 49, stdin);
        library[i].title[strlen(library[i].title)-1] = '\0'; // ADDING NULL CHARACTER AT THE END OF STRING

        printf("\nAuthor : ");
        clear_buffer();
        fgets(library[i].author, 49, stdin);
        library[i].author[strlen(library[i].author)-1] = '\0'; // ADDING NULL CHARACTER AT THE END OF STRING

        printf("\nPublisher : ");
        clear_buffer();
        fgets(library[i].publisher, 49, stdin);
        library[i].publisher[strlen(library[i].publisher)-1] = '\0'; // ADDING NULL CHARACTER AT THE END OF STRING

        printf("\nGenre : ");
        clear_buffer();
        fgets(library[i].genre, 49, stdin);
        library[i].genre[strlen(library[i].genre)-1] = '\0'; // ADDING NULL CHARACTER AT THE END OF STRING

        printf("\nYear of Publication : ");
        clear_buffer();
        scanf("%d", &library[i].year_of_publication);

        printf("\nSelling Price : ");
        clear_buffer();
        scanf("%d", &library[i].price);
        
        printf("\nQuantity: ");
        clear_buffer();
        scanf("%d", &library[i].stock);

        available_books++; // increasing available books

        // option to add new
        add_again:
        char add_new;
        printf("\n\nDo you want to add new book again (Y/N): ");
        clear_buffer();
        scanf("%c", &add_new);
        
        if(tolower(add_new) == 'n'){
            main();
            break;
        }
        else if(tolower(add_new) == 'y'){
            continue;
        }
        else{
            printf("\nPlease select the right choice!!");
            goto add_again;
        }
    }
}

void search_book(){
    bool isFound=true;

    start_search:
    clear_screen();

    if(!isFound){
        printf("\nBook not found OR Please enter the right value to find book you want!!");
    }

    printf("\n\t\tSEARCH");
    int isbn_to_search = 0;
    char title_to_search[50]="", author_to_search[50]="", publisher_to_search[50]="", genre_to_search[50]="";

    search:
    int search_option;
    printf("\nWhat you want to search using ?\n1. ISBN\n2. Title\n3. Author\n4. Publisher\n5. Genre\n\tOR\n6. GO TO MENU");
    printf("\nYour choice: ");
    clear_buffer();
    scanf("%d", &search_option);

    switch(search_option){
        case 1: // ISBN
                printf("\nEnter the ISBN number of the book: ");
                clear_buffer();
                scanf("%d", &isbn_to_search);
                break;
        case 2: // Title
                printf("\nEnter the Title of the book: ");
                clear_buffer();
                fgets(title_to_search, 49, stdin);
                title_to_search[strlen(title_to_search)-1] = '\0'; // ADDING NULL CHARACTER AT THE END OF STRING
                break;
        case 3: // Author
                printf("\nEnter the author of the book: ");
                clear_buffer();
                fgets(author_to_search, 49, stdin);
                author_to_search[strlen(author_to_search)-1] = '\0'; // ADDING NULL CHARACTER AT THE END OF STRING
                break;
        case 4: // Publisher
                printf("\nEnter the publisher of the book: ");
                clear_buffer();
                fgets(publisher_to_search, 49, stdin);
                publisher_to_search[strlen(publisher_to_search)-1] = '\0'; // ADDING NULL CHARACTER AT THE END OF STRING
                break;
        case 5: // Genre
                printf("\nEnter the genre of the book: ");
                clear_buffer();
                fgets(genre_to_search, 49, stdin);
                genre_to_search[strlen(genre_to_search)-1] = '\0'; // ADDING NULL CHARACTER AT THE END OF STRING
                break;
        case 6: main();
                break;
        default: 
                printf("\nWrong input... Please select again..");
                goto search;
    }


    // for comparison
    char choice;
    for(int i=0; i<available_books; i++){
        if(strcmp(library[i].title, title_to_search) == 0 || strcmp(library[i].author, author_to_search) == 0 || strcmp(library[i].publisher, publisher_to_search) == 0 || strcmp(library[i].genre, genre_to_search) == 0 || library[i].isbn == isbn_to_search){
            clear_screen();
            printf("\n\t\tBOOK FOUND..\n");
            isFound = true;
            print_book(i);

            printf("\n\nDo you want to issue or return this book? (Y/N) or to go to menu, type 'M': ");
            clear_buffer();
            scanf("%c", &choice);

            if(tolower(choice) == 'y'){
                transaction(i);
            }
            else if(tolower(choice) == 'm'){
                main();
            }
        }
        isFound=false;
    }

    if(!isFound){
        goto start_search;
    }

    
}

void transaction(int i){

    printf("\n\t\tTRANSCATION");

    int trans_option;
    printf("\nSelect the below option to Proceed:\n1. Issue a book\n2. Return a book\n\tOR\n3. GO TO MENU");
    printf("\nYour choice: ");
    clear_buffer();
    scanf("%d", &trans_option);

    switch(trans_option){
        case 1: issue_book(i);
            break;
        case 2: return_book(i);
            break;
        case 3: main();
            break;
        default: printf("\nWrong input!! Please select the right choice again!!");
            transaction(i);
            break;
    }
}

void issue_book(int i){
    printf("\n\t\tIssue"); 

    if(library[i].stock == 0){
        printf("\nSorry this book is not available right now.... Check back later.");
    }
    else{
        library[i].stock--; // decreasing 1 from stock
        printf("\nCongratulations..... Book Issued.");
        printf("\n\nTITLE: %s\nAUTHOR: %s\nPUBLISHER: %s", library[i].title, library[i].author, library[i].publisher);

        printf("\n----------------------------\n");
    }

    menu_caller();
}

void return_book(int i){
    printf("\n\t\tReturn"); 
    
    library[i].stock++; // adding 1 to stock
    printf("\n\nBOOK RETURNED");
    printf("\n----------------------------\n");

    menu_caller();
}

void delete_book_input(){

    int isbn;
    printf("\nEnter the ISBN number of the book to delete: ");
    clear_buffer();
    scanf("%d", &isbn);

    delete_book(isbn);
}

void delete_book(int isbn_of_del_book){
    bool isAvailable = true;
    printf("\nDELETING...");
    
    // searching for index value of book to delete
    for(int i=0; i<available_books; i++){
        if(isbn_of_del_book == library[i].isbn){
            for(int j=i; j<available_books; j++){
                // shifting elements back
                library[i].isbn = library[i+1].isbn;
                strcpy(library[i].title, library[i+1].title);
                strcpy(library[i].author, library[i+1].author);
                strcpy(library[i].publisher, library[i+1].publisher);
                strcpy(library[i].genre, library[i+1].genre);
                library[i].year_of_publication = library[i+1].year_of_publication;
                library[i].price = library[i+1].price;
                library[i].stock = library[i+1].stock;
            }

            printf("\nBOOK DELETED....");
            
            available_books--; // decreasing available books
            
            menu_caller();

            break;
        }
        isAvailable = false;
        
    }

    if(!isAvailable){
        printf("\nEntered ISBN number not available!!!\nPlease enter the right one to delete");
        delete_book_input();
    }
    
}

void clear_screen(){
    system("cls");
}

void clear_buffer(){
    fflush(stdin);
}

void menu_caller(){
    char choice;
    printf("\n\nPress 'M' to go to main menu: ");
    clear_buffer();
    scanf("%s", &choice);
    
    if(tolower(choice) == 'm'){
        main();
    }
    else{
        printf("\nPlease type the correct input again!!");
        menu_caller();
    }
}