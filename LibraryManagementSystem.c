/*
DSA Project Defination: library management system

Program will simulate the library management like Add a book, Delete book from library, 
also issue a book and many. we will implement the whole Project using Linked List, Array, BST.

Program Modules:
for students:
1) Issue book
2) Return book;
3) Search book
    i) By Book Name
   ii) By Author Name
4) Display available books in library

for librarian:
1) Add book in library
2) Remove book from library
3) Display issued Books
4) Display Members of Library
5) Display available books in library


                                           :: Roll No ::
                                     20BCE104 : Jatin B. Undhad
                                     20BCE103 : Jani Chetan
                                     20BCE089 : Het Patel

*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
int SrNo = 0;
int count = 0;

// Book1 used to create node of  "Book BST"
typedef struct Book1
{
    char book_name[50];
    char author_name[40];
    struct Book1 *left, *right;
} book1;

// Book1 used to create node of Linked List for "Issued Books"
typedef struct Book2
{
    char book_name[50];
    char author_name[40];
    char student_name[40];
    int id;
    struct Book2 *next;
} book2;

// Student used to create node of "Student BST"
typedef struct Student
{
    char name[40];
    char id;
    struct Student *right, *left;
} student;

book1 *root_book1 = NULL;
student *root_student = NULL;
book1 *dummy = NULL;

book2 *first = NULL;
book2 *last = NULL;

// it will insert the Book in BST
void insert_book1(char book_name[], char author_name[])
{

    book1 *new = (book1 *)malloc(sizeof(book1));
    strcpy(new->book_name, book_name);
    strcpy(new->author_name, author_name);
    new->left = NULL;
    new->right = NULL;

    if (root_book1 == NULL)
    {
        root_book1 = new;
    }
    else
    {
        book1 *ptr = root_book1;
        book1 *parent_ptr;

        while (ptr != NULL)
        {
            if (strcmpi(ptr->book_name, new->book_name) > 0)
            {
                parent_ptr = ptr;
                ptr = ptr->left;
            }
            else
            {
                parent_ptr = ptr;
                ptr = ptr->right;
            }
        }

        if (strcmpi(parent_ptr->book_name, new->book_name) > 0)
        {
            parent_ptr->left = new;
        }
        else
        {
            parent_ptr->right = new;
        }
    }
}

// Travese the BST of Book (Inorder Traversal)
void Display_Available_Books(book1 *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    Display_Available_Books(ptr->left);
    SrNo++;
    printf("%d\t\t%s\n", SrNo, ptr->book_name);
    Display_Available_Books(ptr->right);
}

book1 *find_succ(book1 *ptr)
{
    while (ptr->left != NULL)
    {
        ptr = ptr->left;
    }
    return ptr;
}

// Delete the Book from the Book BST
void Delete_book1(char Book_name[])
{
    book1 *ptr = root_book1;
    book1 *parent_ptr = root_book1;

    if (ptr == NULL)
    {
        printf("There is not any book available.\n");
        return;
    }

    int found = 0;
    while (ptr != NULL)
    {
        if (strcmpi(ptr->book_name, Book_name) == 0)
        {
            found = 1;
            break;
        }
        else
        {
            if (strcmpi(ptr->book_name, Book_name) > 0)
            {
                parent_ptr = ptr;
                ptr = ptr->left;
            }
            else
            {
                parent_ptr = ptr;
                ptr = ptr->right;
            }
        }
    }

    if (found == 0)
    {
        printf("There is not any book available with name \"%s\" in Library\n", Book_name);
        return;
    }

    if (ptr->left == NULL && ptr->right == NULL)
    {
        if (ptr == root_book1)
        {
            free(ptr);
            root_book1 = NULL;
            return;
        }
        else if (parent_ptr->left == ptr)
        {
            parent_ptr->left = NULL;
        }
        else
        {
            parent_ptr->right = NULL;
        }
        free(ptr);
    }
    else if (ptr->left != NULL && ptr->right != NULL)
    {
        book1 *succ = find_succ(ptr->right);
        book1 *copy_succ = (book1 *)malloc(sizeof(book1));
        strcpy(copy_succ->book_name, succ->book_name);
        strcpy(copy_succ->author_name, succ->author_name);

        Delete_book1(succ->book_name);

        strcpy(ptr->book_name, copy_succ->book_name);
        strcpy(ptr->author_name, copy_succ->author_name);
        free(copy_succ);
    }
    else
    {
        if (parent_ptr == ptr)
        {
            if (ptr->left == NULL)
            {
                root_book1 = ptr->right;
            }
            else
            {
                root_book1 = ptr->left;
            }
        }
        else if (parent_ptr->left == ptr)
        {
            if (ptr->left != NULL)
            {
                parent_ptr->left = ptr->left;
            }
            else
            {
                parent_ptr->left = ptr->right;
            }
        }
        else
        {
            if (ptr->left != NULL)
            {
                parent_ptr->right = ptr->left;
            }
            else
            {
                parent_ptr->right = ptr->right;
            }
        }
        free(ptr);
    }
}

// Search the Book by Book name
void Search_By_Name()
{

    if (root_book1 == NULL)
    {
        printf("\nThere is not any book in Library.\n");
    }

    printf("Enter a Book name: ");
    char str[50];
    gets(str);
    gets(str);

    book1 *ptr = root_book1;
    while (ptr != NULL)
    {
        if (strcmpi(ptr->book_name, str) == 0)
        {
            printf("\n--------------------------------------------------------------\nBook Name\t\tAuthor Name\n--------------------------------------------------------------\n");
            printf("%s\t\t%s\n", ptr->book_name, ptr->author_name);
            printf("--------------------------------------------------------------\n");
            return;
        }
        else if (strcmpi(ptr->book_name, str) > 0)
        {
            ptr = ptr->left;
        }
        else if (strcmpi(ptr->book_name, str) < 0)
        {
            ptr = ptr->right;
        }
    }

    if (ptr == NULL)
    {
        printf("\n--------------------------------------------------------------\nThere is not book available with name \"%s\" in Library now.\n--------------------------------------------------------------\n", str);
    }
}

// Search the Book by Author name
void Find_Author(book1 *ptr, char str[])
{
    if (ptr == NULL)
    {
        return;
    }
    Find_Author(ptr->left, str);
    if (strcmpi(ptr->author_name, str) == 0)
    {
        count++;
        printf("%s\t\t%s\n", ptr->book_name, ptr->author_name);
    }
    Find_Author(ptr->right, str);

    count = 0;
}
void Search_By_Author()
{
    if (root_book1 == NULL)
    {
        printf("\nThere is not any book in Library.\n");
    }

    printf("Enter a Author name: ");
    char str[50];
    gets(str);
    gets(str);

    printf("\n--------------------------------------------------------------\nBook Name\t\tAuthor Name\n--------------------------------------------------------------\n");
    Find_Author(root_book1, str);
    printf("--------------------------------------------------------------\n");
}

// Insert the node in student BST
void Insert_student(char name[], int id)
{
    FILE *fp1 = fopen("D:\\3rd sem\\DSA\\Innovative_Assignment\\Members_of_Library.txt", "a+");
    fprintf(fp1, "ID: %d ->\t%s\n\n", id, name);
    fclose(fp1);

    student *new = (student *)malloc(sizeof(student));
    strcpy(new->name, name);
    new->id = id;
    new->left = NULL;
    new->right = NULL;

    if (root_student == NULL)
    {
        root_student = new;
        return;
    }

    student *ptr = root_student;
    student *parent_ptr;
    while (ptr != NULL)
    {
        if (ptr->id > id)
        {
            parent_ptr = ptr;
            ptr = ptr->left;
        }
        else
        {
            parent_ptr = ptr;
            ptr = ptr->right;
        }
    }

    if (parent_ptr->id > id)
    {
        parent_ptr->left = new;
    }
    else
    {
        parent_ptr->right = new;
    }
}

// find the Author name and retun it
char *find_Author(char str[])
{

    book1 *ptr = root_book1;
    while (ptr != NULL)
    {
        if (strcmpi(ptr->book_name, str) == 0)
        {
            return ptr->author_name;
        }
        else if (strcmpi(ptr->book_name, str) > 0)
        {
            ptr = ptr->left;
        }
        else if (strcmpi(ptr->book_name, str) < 0)
        {
            ptr = ptr->right;
        }
    }
}

// Insert a node in Book Linkedlist
void Insert_book2(char Book_name[], char Student_name[], int id)
{
    FILE *fp2 = fopen("D:\\3rd sem\\DSA\\Innovative_Assignment\\Issued_books.txt", "a+");
    fprintf(fp2, "Book \"%s\" issued to \"%s\".\n\n", Book_name, Student_name);
    fclose(fp2);

    book2 *new = (book2 *)malloc(sizeof(book2));
    strcpy(new->book_name, Book_name);
    strcpy(new->student_name, Student_name);
    strcpy(new->author_name, find_Author(Book_name));
    new->id = id;
    new->next = NULL;

    if (first == NULL)
    {
        first = new;
        last = new;
    }
    else
    {
        last->next = new;
        last = new;
    }
}

book2 *check(int id)
{
    book2 *ptr = first;
    while (ptr != NULL)
    {
        if (ptr->id == id)
        {
            return ptr;
        }
        else
        {
            ptr = ptr->next;
        }
    }

    return ptr;
}

int check_student(int id)
{
    student *ptr = root_student;
    while (ptr != NULL)
    {
        if (ptr->id == id)
        {
            return 1;
        }
        else if (ptr->id > id)
        {
            ptr = ptr->left;
        }
        else if (ptr->id < id)
        {
            ptr = ptr->right;
        }
    }

    return 0;
}

// Issue the Book (Deletion in Book BST, Insertion in Book Linked List, Insertion in Student BST)
void Issue_Book()
{
    printf("Enter your choice:\n1: Search a Book\n2: See available Books\nEnter here: ");
    int choice;
    scanf("%d", &choice);
    system("cls");

    if (choice == 1)
    {
        int choice_search;
        printf("Enter choice:\n1: Search by Name\n2: Search by Author\nEnter here: ");
        scanf("%d", &choice_search);
        system("cls");
        if (choice_search == 1)
        {
            Search_By_Name();
        }
        else if (choice_search == 2)
        {
            Search_By_Author();
        }
    }
    else if (choice == 2)
    {
        SrNo = 0;
        printf("--------------------------------------------------------------\nSr. No.\t\tBook Name\n--------------------------------------------------------------\n");
        Display_Available_Books(root_book1);
        printf("--------------------------------------------------------------\n");
    }

    printf("\nIf you find your desire Book, Enter\n1: For issue\n2: Discard\nEnter here: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("\nPlease, Enter Your Name: ");
        char Student_name[40];
        gets(Student_name);
        gets(Student_name);
        int id;
        printf("\nPlease, Enter Your id: ");
        scanf("%d", &id);

        book2 *ptr = check(id);
        if (ptr != NULL)
        {
            system("cls");
            printf("\n-----------------------------------------------------------------\nYou already issued one Book with name \"%s\", please return it before issue new Book\n-----------------------------------------------------------------\n", ptr->book_name);
            return;
        }
        else
        {
            if (check_student(id) == 0)
            {
                Insert_student(Student_name, id);
            }
            char Book_name[50];
            printf("\nEnter a Book Name correctly : ");
            gets(Book_name);
            gets(Book_name);
            Insert_book2(Book_name, Student_name, id);
            Delete_book1(Book_name);
            system("cls");
            printf("\n-----------------------------------------------------------------\nYou have issued the Book \"%s\".\n-----------------------------------------------------------------\n", Book_name);
        }
    }
    else
    {
        system("cls");
        return;
    }
}

// Delete the issued book (Deletion in Book Linked List)
void Delete_book2(int id)
{
    book2 *ptr = first;
    book2 *previous_ptr = NULL;
    while (ptr->id != id)
    {
        previous_ptr = ptr;
        ptr = ptr->next;
    }

    if (ptr == first)
    {
        first = first->next;
    }
    else if (ptr == last)
    {
        last = previous_ptr;
        last->next = NULL;
    }
    else
    {
        previous_ptr->next = ptr->next;
    }
    free(ptr);
}

// Retuen the Book (Delete the book from Book Linked List, Insert the Book in Book BST)
void Return_Book()
{
    if (first == NULL)
    {
        printf("\n--------------------------------------------------------------\nThere is not any issued books in Library\n--------------------------------------------------------------\n");
        return;
    }

    printf("Enter Your Name: ");
    char Student_name[40];
    gets(Student_name);
    gets(Student_name);

    int id;
    printf("Enter Your id: ");
    scanf("%d", &id);

    book2 *ptr = check(id);
    printf("\nYour current issued Book is \"%s\" written by \"%s\".\n", ptr->book_name, ptr->author_name);

    printf("\nIf given information is right then Enter \'1\' else \'0\' : ");
    int tele;
    scanf("%d", &tele);

    if (tele == 1)
    {
        char book_name[50];
        strcpy(book_name, ptr->book_name);
        insert_book1(ptr->book_name, ptr->author_name);

        FILE *fp3 = fopen("D:\\3rd sem\\DSA\\Innovative_Assignment\\Returned_Book.txt", "a+");
        fprintf(fp3, "Book \"%s\" is returned by \"%s\".\n\n", ptr->book_name, ptr->student_name);
        fclose(fp3);

        Delete_book2(id);
        system("cls");
        printf("\n--------------------------------------------------------------\nYou have retuned the Book \"%s\".\n--------------------------------------------------------------\n", book_name);
    }
    else if (tele == 0)
    {
        return;
    }
}

// Display the issued books (Linked List traversal)
void Display_Issued_books()
{
    if (first == NULL)
    {
        system("cls");
        printf("\n--------------------------------------------------------------------\nTill now, there have not any Book issued in library.\n--------------------------------------------------------------------\n");
    }
    else
    {
        book2 *ptr = first;
        int i = 1;
        printf("\n------------------------------------------------------------------------------------\nDETAILS OF ISSUED BOOKS\n------------------------------------------------------------------------------------\n");

        while (ptr != NULL)
        {
            printf("%d ) \"%s\" issued to %s\n", i, ptr->book_name, ptr->student_name);
            i++;
            ptr = ptr->next;
        }

        printf("------------------------------------------------------------------------------------\n");
    }
}

// Display the members of the Library (Inorder traversal of Student BST)
void print_memebers(student *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    print_memebers(ptr->left);
    printf("ID: %d\t\t%s\n", ptr->id, ptr->name);
    print_memebers(ptr->right);
}
void show_member_list()
{
    if (root_student == NULL)
    {
        system("cls");
        printf("\n------------------------------------------------------------------------------------\nThere are not any memebers of the Library.\n------------------------------------------------------------------------------------\n");
    }
    else
    {
        printf("\n------------------------------------------------------------------------------------\nMEMBERS OF THE LIBRARY\n------------------------------------------------------------------------------------\n");
        print_memebers(root_student);
        printf("------------------------------------------------------------------------------------\n");
    }
}

int main()
{
    // change the file loction as per your device storage before run the program
    FILE *fp = fopen("D:\\3rd sem\\DSA\\Innovative_Assignment\\Library_Books.txt", "w");
    FILE *fptr2 = fopen("D:\\3rd sem\\DSA\\Innovative_Assignment\\Issued_books.txt", "w");
    fclose(fptr2);
    FILE *fptr3 = fopen("D:\\3rd sem\\DSA\\Innovative_Assignment\\Members_of_Library.txt", "w");
    fclose(fptr3);
    FILE *fptr4 = fopen("D:\\3rd sem\\DSA\\Innovative_Assignment\\Returned_Book.txt", "w");
    fclose(fptr4);

    // Create stock of the book (BST - Binary Search Tree of Books)
    insert_book1("Turbulence And Triumph The Modi Years", "Rahul Agarwal");
    fprintf(fp, "\"Turbulence And Triumph The Modi Years\" written by \"Rahul Agarwal\"\n\n");

    insert_book1("Savarkar: Echoes from a Forgotten Past", "Vikram Sampath");
    fprintf(fp, "\"Savarkar: Echoes from a Forgotten Past\" written by \"Vikram Sampath\"\n\n");

    insert_book1("Obama-The Call of History", "Peter Baker");
    fprintf(fp, "\"Obama-The Call of History\" written by \"Peter Baker\"\n\n");

    insert_book1("Kashmiri's Untold Story: Declassification", "Maroof Raza");
    fprintf(fp, "\"Kashmiri's Untold Story: Declassification\" written by \"Maroof Raza\"\n\n");

    insert_book1("Sridevi: Girl Women Superstar", "Satyarth Nayak");
    fprintf(fp, "\"Sridevi: Girl Women Superstar\" written by \"Satyarth Nayak\"\n\n");

    insert_book1("Listening, Learning And Leading", "Venkaih Naidu");
    fprintf(fp, "\"Listening, Learning And Leading\" written by \"Venkaih Naidu\"\n\n");

    insert_book1("Darkness to Light", "Lamar Odam");
    fprintf(fp, "\"Darkness to Light\" written by \"Lamar Odam\"\n\n");

    insert_book1("Undaunted-Saving the Idea of India", "P.Chidambharam");
    fprintf(fp, "\"Undaunted-Saving the Idea of India\" written by \"P.Chidambharam\"\n\n");

    insert_book1("We Are Displaced", "Malala Yousafzai");
    fprintf(fp, "\"We Are Displaced\" written by \"Malala Yousafzai\"\n\n");

    insert_book1("I Am Malala", "Malala Yousafzai");
    fprintf(fp, "\"I Am Malala\" written by \"Malala Yousafzai\"\n\n");

    fclose(fp);

    system("cls");
    printf("\t\t\t\t------------------------------------------------------------------------\n");
    printf("\t\t\t\t|                                                                      |\n");
    printf("\t\t\t\t|                                                                      |\n");
    printf("\t\t\t\t|                 WELCOME TO LIBRARY MANAGEMENT SYSTEM                 |\n");
    printf("\t\t\t\t|                                                                      |\n");
    printf("\t\t\t\t|                                                                      |\n");
    printf("\t\t\t\t------------------------------------------------------------------------\n");
    int LogIn;
login:
    printf("\nEnter your choice\n1 : Librarian\n2 : Student\nEnter here: ");
    scanf("%d", &LogIn);
    system("cls");

    if (LogIn == 1)
    {
        printf("\n-------------------------------------------------------\nYou entered as a \"Librarian\"\n-------------------------------------------------------\n");
        char Password[20];
        printf("Enter a password : ");
        scanf("%s", Password);
        system("cls");

        if (strcmp(Password, "Lib@123") == 0)
        {
            while (1)
            {
                printf("\nEnter your choice\n1: Available Books in Library\n2: Show Issued Books\n3: Add New Book in Library\n4: Delete Book from Library\n5: Show Member List of the Library\n6: Go to login page\n7: end\nEnter here: ");
                int choice;
                scanf("%d", &choice);
                system("cls");

                switch (choice)
                {
                case 1:
                {
                    SrNo = 0;
                    printf("--------------------------------------------------------------\nSr. No.\t\tBook Name\n--------------------------------------------------------------\n");
                    Display_Available_Books(root_book1);
                    printf("--------------------------------------------------------------\n");
                }
                break;
                case 2:
                {
                    Display_Issued_books();
                }
                break;
                case 3:
                {
                    char Book_name[50], Author_name[30];
                    printf("Enter a Book name: ");
                    gets(Book_name);
                    gets(Book_name);
                    printf("Enter a Author name of Book \"%s\": ", Book_name);
                    gets(Author_name);

                    fp = fopen("D:\\3rd sem\\DSA\\Innovative_Assignment\\Library_Books.txt", "a+");
                    fprintf(fp, "\"%s\" written by \"%s\"\n\n", Book_name, Author_name);
                    fclose(fp);

                    insert_book1(Book_name, Author_name);
                }
                break;
                case 4:
                {
                    char Book_name[50];
                    printf("Enter a Book name: ");
                    gets(Book_name);
                    gets(Book_name);
                    Delete_book1(Book_name);
                }
                break;
                case 5:
                {
                    show_member_list();
                }
                break;
                case 6:
                {
                    goto login;
                }
                break;
                case 7:
                {
                    printf("\n...THANK YOU FOR VISIT...\n\n");
                    return 0;
                }
                break;
                }
            }
        }
        else
        {
            printf("SORRY!!!, LOG IN FAILED.\n---------------------------------------------------\n");
            goto login;
        }
    }
    else if (LogIn == 2)
    {
        printf("\n-------------------------------------------------------\nYou entered as a \"Student\"\n-------------------------------------------------------\n");
        while (1)
        {
            int choice;
            printf("\nEnter your choice:\n1: Search for book\n2: Available Books in Library\n3: Issue book\n4: Return Book\n5: Go to Login page\n6: End\nEnter here: ");
            scanf("%d", &choice);
            system("cls");

            switch (choice)
            {
            case 1:
            {
                int choice_search;
                printf("Enter choice:\n1: Search by Name\n2: Search by Author\nEnter here: ");
                scanf("%d", &choice_search);
                system("cls");
                if (choice_search == 1)
                {
                    Search_By_Name();
                }
                else if (choice_search == 2)
                {
                    Search_By_Author();
                }
            }
            break;

            case 2:
            {
                SrNo = 0;
                printf("--------------------------------------------------------------\nSr. No.\t\tBook Name\n--------------------------------------------------------------\n");
                Display_Available_Books(root_book1);
                printf("--------------------------------------------------------------\n");
            }
            break;

            case 3:
            {
                Issue_Book();
            }
            break;

            case 4:
            {
                Return_Book();
            }
            break;

            case 5:
            {
                goto login;
            }
            break;

            case 6:
            {
                printf("\n...THANK YOU FOR VISIT...\n\n");
                return 0;
            }
            break;
            }
        }
    }

    return 0;
}