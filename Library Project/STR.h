typedef struct
{
    char title[100];
    char author[100];
    char publisher[100];
    char DateOfPublication[100];
    char Category[100];
    char ISBN[100];
    int copies;
    int AvaCopies;
} book;
typedef struct
{
    char FirstName[100];
    char LastName[100];
    int ID;
    char street[100];
    char building[50];
    char city[25];
    char phone[15];
    char age[4];
    char Email[75];
} member;
typedef struct
{
    int borrowID;
    char borrowISBN[100];
    char DateToReturn[50];
    char DateBorrowed[15];
    char DateReturned[15];
} borrow;
