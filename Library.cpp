#include <iostream>
#include <string>
using namespace std;

// ---------- ARRAY : Books ----------
struct Book
{
    int id;
    string name;
    bool issued;
};

Book books[50];
int bookCount = 0;


// ---------- LINKED LIST : Members ----------
struct Member
{
    int id;
    string name;
    Member *next;
};

Member *head = NULL;


// ---------- STACK : Recently Returned Books ----------
int returnedStack[20];
int top = -1;


// ---------- QUEUE : Book Issue Requests ----------
int requestQueue[20];
int front = -1;
int rear = -1;


// ---------- CIRCULAR QUEUE : Waiting List ----------
int waitingQueue[10];
int cfront = -1;
int crear = -1;


// Add Book
void addBook()
{
    if(bookCount >= 50)
    {
        cout << "Library is full!\n";
        return;
    }

    cout << "Enter Book ID: ";
    cin >> books[bookCount].id;

    cout << "Enter Book Name: ";
    cin.ignore();
    getline(cin, books[bookCount].name);

    books[bookCount].issued = false;

    bookCount++;

    cout << "Book added successfully!\n";
}


// Display Books
void displayBooks()
{
    if(bookCount == 0)
    {
        cout << "No books available.\n";
        return;
    }

    cout << "\n--- BOOK LIST ---\n";

    for(int i = 0; i < bookCount; i++)
    {
        cout << "ID: " << books[i].id;
        cout << "  Name: " << books[i].name;

        if(books[i].issued)
            cout << "  Status: Issued\n";
        else
            cout << "  Status: Available\n";
    }
}


// Search Book
void searchBook()
{
    int id;
    cout << "Enter Book ID: ";
    cin >> id;

    for(int i = 0; i < bookCount; i++)
    {
        if(books[i].id == id)
        {
            cout << "Book Found!\n";
            cout << "Name: " << books[i].name << endl;

            if(books[i].issued)
                cout << "Status: Issued\n";
            else
                cout << "Status: Available\n";

            return;
        }
    }

    cout << "Book not found.\n";
}


// Issue Request - QUEUE
void issueRequest()
{
    int id;

    if(rear == 19)
    {
        cout << "Request queue is full.\n";
        return;
    }

    cout << "Enter Book ID for issue request: ";
    cin >> id;

    if(front == -1)
        front = 0;

    rear++;
    requestQueue[rear] = id;

    cout << "Issue request added to queue.\n";
}


// Process Issue Request
void processRequest()
{
    if(front == -1 || front > rear)
    {
        cout << "No issue requests.\n";
        return;
    }

    int id = requestQueue[front];
    front++;

    for(int i = 0; i < bookCount; i++)
    {
        if(books[i].id == id)
        {
            if(!books[i].issued)
            {
                books[i].issued = true;
                cout << "Book issued successfully.\n";
            }
            else
            {
                cout << "Book is already issued.\n";
            }

            return;
        }
    }

    cout << "Book not found.\n";
}


// Return Book - STACK
void returnBook()
{
    int id;

    cout << "Enter Book ID to return: ";
    cin >> id;

    for(int i = 0; i < bookCount; i++)
    {
        if(books[i].id == id)
        {
            books[i].issued = false;

            if(top < 19)
            {
                top++;
                returnedStack[top] = id;
            }

            cout << "Book returned successfully.\n";
            return;
        }
    }

    cout << "Book not found.\n";
}


// Display Stack
void recentReturns()
{
    if(top == -1)
    {
        cout << "No returned books.\n";
        return;
    }

    cout << "\n--- RECENTLY RETURNED BOOKS ---\n";

    for(int i = top; i >= 0; i--)
    {
        cout << "Book ID: " << returnedStack[i] << endl;
    }
}


// Add Member - LINKED LIST
void addMember()
{
    Member *newMember = new Member;

    cout << "Enter Member ID: ";
    cin >> newMember->id;

    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, newMember->name);

    newMember->next = NULL;

    if(head == NULL)
    {
        head = newMember;
    }
    else
    {
        Member *temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newMember;
    }

    cout << "Member added successfully.\n";
}


// Display Members
void displayMembers()
{
    if(head == NULL)
    {
        cout << "No members registered.\n";
        return;
    }

    Member *temp = head;

    cout << "\n--- LIBRARY MEMBERS ---\n";

    while(temp != NULL)
    {
        cout << "ID: " << temp->id;
        cout << "  Name: " << temp->name << endl;

        temp = temp->next;
    }
}


// CIRCULAR QUEUE - Waiting List
void addWaitingStudent()
{
    int id;

    cout << "Enter Student ID: ";
    cin >> id;

    if((crear + 1) % 10 == cfront)
    {
        cout << "Waiting list is full.\n";
        return;
    }

    if(cfront == -1)
        cfront = 0;

    crear = (crear + 1) % 10;
    waitingQueue[crear] = id;

    cout << "Student added to waiting list.\n";
}


// Remove from Circular Queue
void serveWaitingStudent()
{
    if(cfront == -1)
    {
        cout << "Waiting list is empty.\n";
        return;
    }

    cout << "Student ID " << waitingQueue[cfront]
         << " can now get the book.\n";

    if(cfront == crear)
    {
        cfront = -1;
        crear = -1;
    }
    else
    {
        cfront = (cfront + 1) % 10;
    }
}


// ---------- MAIN ----------
int main()
{
    int choice;

    do
    {
        cout << "\n================================\n";
        cout << "     LIBRARY MANAGEMENT SYSTEM\n";
        cout << "================================\n";

        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Add Issue Request\n";
        cout << "5. Process Issue Request\n";
        cout << "6. Return Book\n";
        cout << "7. Recently Returned Books\n";
        cout << "8. Add Library Member\n";
        cout << "9. Display Members\n";
        cout << "10. Add Student to Waiting List\n";
        cout << "11. Serve Waiting Student\n";
        cout << "12. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                issueRequest();
                break;

            case 5:
                processRequest();
                break;

            case 6:
                returnBook();
                break;

            case 7:
                recentReturns();
                break;

            case 8:
                addMember();
                break;

            case 9:
                displayMembers();
                break;

            case 10:
                addWaitingStudent();
                break;

            case 11:
                serveWaitingStudent();
                break;

            case 12:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 12);

    return 0;
}
