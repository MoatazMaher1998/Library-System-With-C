#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "STR.h"
int Valid_Mail(char Email[],member *M,int NMembers) //
{
    int i;
    strcat(Email,"\n");
    for(i=0; i<NMembers; i++)
    {
        {
            if(strcmp(Email,M->Email)==0)
            {
                return 1;
            }
        }
        M++;
    }
    return 0;
}
int ifString(int n,char Check[n]) //
{
    int i,letter=0,number=0,weird=0;
    for(i=0; i<n; i++)
    {
        if((Check[i]>='a'&&Check[i]<='z') || (Check[i] >= 'A' && Check[i] <= 'Z'))
        {
            letter=1;
        }
        if(Check[i]>='0'&&Check[i]<='9')
        {
            number=1;
        }
        else
        {
            weird=1;
            break;
        }
    }
    if(number==1 && letter==0 && weird==0)
    {
        return 1;
    }
    if(number==0 && letter==1 && weird==0)
    {
        return 0;
    }
    if(number==1 && letter==0 && weird==1)
    {
        return -1;
    }


}
void MostPop(int NBooks,book Books[],borrow Bo[],int NBorrow)
{
    int Array[NBooks],i,count,z;
    int x;
    x=0;
    char isbn[30];
    printf(" BOOK TITLE\t\tBOOK AUTHOR\t\tBOOK ISBN\n");
    for(i=0; i<NBooks; i++)
    {
        count=0;
        strcpy(isbn,Books[i].ISBN);
        for(z=0; z<NBorrow; z++)
        {
            if(strcasecmp(isbn,Bo[z].borrowISBN)==0)
            {
                count++;
            }
            Array[x]=count;
        }
        x++;
    }
    int y,m=1,max;
    while(m<5)
    {
        max=Array[0];
        for(y=0; y<x; y++)
        {
            if(Array[y]>max)
            {
                max=Array[y];
            }
        }
        for(y=0; y<x; y++)
        {
            if(m>5)
            {
                return;
            }
            if(Array[y]==max)
            {
                printf("-%s\t-%s\t-%s\n",Books[y].title,Books[y].author,Books[y].ISBN);
                m++;
                Array[y]=-1;
            }
        }
    }


}
void OverDueBooks(borrow *Bo,int NBorrow) //
{
    char sTime[15];
    char *ADD;
    int dayB,dayR;
    int monthB,monthR;
    int yearB,yearR;
    int i,count=0;
    printf("BOOK ISBN\tUSER ID\n");
    for(i=0; i<NBorrow; i++)
    {
        strcpy(sTime,Bo->DateToReturn);
        ADD=strtok(sTime,"/");
        dayB=atoi(ADD);
        ADD=strtok(NULL,"/");
        monthB=atoi(ADD);
        ADD=strtok(NULL,"/");
        yearB=atoi(ADD);
        gettime(&monthR,&dayR,&yearR,sTime);
        if(yearR>yearB && strcasecmp(Bo->DateReturned,"null"==0))
        {
            printf("*%s\t*%d\n",Bo->borrowISBN,Bo->borrowID);
            count++;
        }
        if(yearB==yearR)
        {
            if(monthR>monthB && strcasecmp(Bo->DateReturned,"null"==0))
            {
                printf("*%s\t*%d\n",Bo->borrowISBN,Bo->borrowID);
                count++;
            }
            if(dayR>dayB && strcasecmp(Bo->DateReturned,"null"==0))
            {
                printf("0*%s\t*%d\n",Bo->borrowISBN,Bo->borrowID);
                count++;
            }
        }
        Bo++;
    }
    printf("Total Number Of Overdue Books Is %d\n",count);
}
void Return_Book(borrow *Bo,int NBorrow,book *B,int NBooks)
{
    int i,id,checker;
    char DATE[20];
    char isbn[15];
    printf("Enter Your ID Please\nYour Choice-->");
    scanf("%d",&id);
    printf("Enter ISBN Of The Book You Want To Return\nYour Choice-->");
    scanf("%s",isbn);
    for(i=0; i<NBorrow; i++)
    {
        if(id==Bo->borrowID && strcasecmp(isbn,Bo->borrowISBN)==0 && strcasecmp(Bo->DateReturned,"NULL\n")==0)
        {
            gettime(&i,&i,&i,DATE);
            strcpy(Bo->DateReturned,DATE);
            strcat(Bo->DateReturned,"\n");
            for(i=0; i<NBooks; i++)
            {
                if(strcasecmp(isbn,B->ISBN)==0)
                {
                    B->AvaCopies++;
                    break;
                }
                B++;
            }
            printf("Book Has Been Returned Successfully\n\n");
            return;
        }
        Bo++;
    }
    printf("Invalid Information Please Check Again");
}
int Count_Borrow(borrow *Bo,int NBorrow,int ID)
{
    int i,count=0,m;
    for(i=0; i<NBorrow; i++)
    {
        m=strcasecmp(Bo->DateReturned,"NULL\n");
        if(ID==Bo->borrowID && m==0)
        {
            count++;
        }
        Bo++;
    }
    return count;
}
int month(char Day[])
{
    if(strcasecmp("jan",Day)==0)
    {
        return 1;
    }
    if(strcasecmp("feb",Day)==0)
    {
        return 2;
    }
    if(strcasecmp("mar",Day)==0)
    {
        return 3;
    }
    if(strcasecmp("apr",Day)==0)
    {
        return 4;
    }
    if(strcasecmp("may",Day)==0)
    {
        return 5;
    }
    if(strcasecmp("jun",Day)==0)
    {
        return 6;
    }
    if(strcasecmp("jul",Day)==0)
    {
        return 7;
    }
    if(strcasecmp("aug",Day)==0)
    {
        return 8;
    }
    if(strcasecmp("sep",Day)==0)
    {
        return 9;
    }
    if(strcasecmp("oct",Day)==0)
    {
        return 10;
    }
    if(strcasecmp("nov",Day)==0)
    {
        return 11;
    }
    if(strcasecmp("dec",Day)==0)
    {
        return 12;
    }
}
void gettime(int *Month,int *Day,int *Year,char Stime[])
{
    char *TakeTime;
    char Get[30];
    char Syear[10],Sday[10],Smonth[10];
    time_t current_time;
    char* c_time_string;
    current_time=time(NULL);
    c_time_string = ctime(&current_time);
    TakeTime=strtok(c_time_string," ");
    TakeTime=strtok(NULL," ");
    strcpy(Get,TakeTime);
    *Month=month(Get);
    itoa(*Month,Smonth,10);
    TakeTime=strtok(NULL," ");
    strcpy(Get,TakeTime);
    *Day=atoi(Get);
    itoa(*Day,Sday,10);
    TakeTime=strtok(NULL," ");
    TakeTime=strtok(NULL," ");
    strcpy(Get,TakeTime);
    *Year=atoi(Get);
    itoa(*Year,Syear,10);
    strcpy(Stime,Sday);
    strcat(Stime,"/");
    strcat(Stime,Smonth);
    strcat(Stime,"/");
    strcat(Stime,Syear);

}
void Addtime(int *Month,int *Day,int *Year,char ADate[])
{
    int i;
    char SMonth[20],SYear[20],SDay[20];
    for(i=0; i<15; i++)

    {
        if(*Month==12 && *Day==31)
        {
            (*Year)++;
            *Day=1;
            *Month=1;
        }

        if(*Month==1 || *Month==3 || *Month==5 || *Month==7 || *Month==8 || *Month==10 || *Month==12)
        {
            if(*Day<31)
            {
                (*Day)++;
            }
            if(*Day==31 && *Month!=12)
            {
                (*Month)++;
            }
        }
        if(*Month==4 || *Month==6 || *Month==9 || *Month==10)
        {
            if(*Day<30)
            {
                (*Day)++;
            }
            if(*Day==30)
            {
                (*Month)++;
            }
        }
        if(*Month==2)
        {
            if(*Day<29)
            {
                (*Day)++;
            }
            if(*Day==29)
            {
                (*Month)++;
            }
        }

    }
    itoa(*Month,SMonth,10);
    itoa(*Year,SYear,10);
    itoa(*Day,SDay,10);
    strcpy(ADate,SDay);
    strcat(ADate,"/");
    strcat(ADate,SMonth);
    strcat(ADate,"/");
    strcat(ADate,SYear);

}
int Delete_Member(member M[],int NMembers)
{
    int y,stop=-1;
    int i;
    printf("Enter ID Of The Member You Want To Delete\n");
    scanf("%d",&i);
    for(y=0; y<NMembers; y++)
    {
        if(i==M[y].ID)
        {
            printf("Member %s %s Has been deleted\n",M[y].FirstName,M[y].LastName);
            stop=y;
        }
    }
    if(stop==-1)
    {
        printf("Wrong ID Check Again");
        return 0;
    }
    member c;
    c=M[NMembers-1];
    M[NMembers- 1]=M[stop];
    M[stop]=c;
    return 1;
}
int Add_Member(member *NewMember,int NMembers,int LastID)
{
    int NoofMember=0;
    member *NP=NewMember;
    NewMember=NewMember+NMembers;
    char FName[50];
    char LName[50];
    char Building[50];
    char Street[25];
    char City[50];
    char phone[13];
    char Age[4];
    char Email[50];
    int checker;
    printf("\nEnter Your First Name:\n");
    fflush(stdin);
    gets(FName);
    checker=ifString(strlen(FName),FName);
    while(checker==1)
    {
        printf("wrong input!\n");
        gets(FName);
        checker=ifString(strlen(FName),FName);
    }
    strcpy(NewMember->FirstName,FName);
    printf("Enter Your surname:\n");
    gets(LName);
    checker=ifString(strlen(LName),LName);
    while(checker==1)
    {
        printf("wrong input!\n");
        gets(LName);
        checker=ifString(strlen(LName),LName);
    }
    strcpy(NewMember->LastName,LName);
    NewMember->ID=LastID+1;
    printf("Enter Your Building Number:\n");
    scanf("%s",Building);
    checker=ifString(strlen(Building),Building);
    while(checker!=1)
    {
        printf("wrong input\n");
        fflush(stdin);
        gets(Building);
        checker=ifString(strlen(Building),Building);
    }
    strcpy(NewMember->building,Building);
    printf("Enter Your Street Name:\n");
    fflush(stdin);
    gets(Street);
    checker=ifString(strlen(Street),Street);
    while(checker==1)
    {
        printf("wrong input!\n");
        gets(Street);
        checker=ifString(strlen(Street),Street);
    }
    strcpy(NewMember->street,Street);
    printf("Enter Your City:\n");
    scanf("%s",City);
    checker=ifString(strlen(City),City);
    while(checker==1)
    {
        printf("wrong input!\n");
        fflush(stdin);
        gets(City);
        checker=ifString(strlen(City),City);
    }
    strcpy(NewMember->city,City);
    printf("Enter Your Phone Number:\n");
    fflush(stdin);
    scanf("%s",phone);
    checker=ifString(strlen(phone),phone);
    while(strlen(phone)<11)
    {
        printf("11 rakam ya bheeem 2nta\n");
        scanf("%s",phone);
    }
    while(checker!=1)
    {
        printf("ma3lesh!\n");
        fflush(stdin);
        gets(phone);
        checker=ifString(strlen(phone),phone);
    }
    strcpy(NewMember->phone,phone);
    printf("How Old Are You?:\n");
    scanf("%s",Age);
    checker=ifString(strlen(Age),Age);
    while(checker!=1)
    {
        printf("wrong input!\n");
        fflush(stdin);
        gets(Age);
        checker=ifString(strlen(Age),Age);
    }
    strcpy(NewMember->age,Age);
    printf("Enter Your Email:\n");
    scanf("%s",Email);
    checker=Valid_Mail(Email,NP,NMembers);
    while(checker==1)
    {
        printf("Email already Used Please Enter A Valid One\n");
        scanf("%s",Email);
        checker=Valid_Mail(Email,NP,NMembers);
    }
    strcpy(NewMember->Email,Email);
    NoofMember++;
    printf("Your ID Is:%d",NewMember->ID);
    return NoofMember;
}
void Updater_Member(member *M,int Nmembers)
{
    int i=Nmembers;
    printf("\nUpdating Members List ....\n");
    FILE *k=fopen("Members.txt","w");
    while(i)
    {
        char Saver[15];
        itoa(M->ID,Saver,10);
        fprintf(k,"%s,%s,%s,%s,%s,%s,%s,%s,%s",M->LastName,M->FirstName,Saver,M->building,M->street,M->city,M->phone,M->age,M->Email);
        M++;
        i--;
    }
    fclose(k);
    printf("Updating Complete!\n");




}
void Updater_Borrowed_Book(borrow *Bo,int NBorrow)
{
    printf("\nUpdating Borrowed Books ....\n");
    int i=NBorrow;
    FILE *k=fopen("Borrowed Books.txt","w");
    while(i)
    {
        char A[15];
        itoa(Bo->borrowID,A,10);
        fprintf(k,"%s,%s,%s,%s,%s",Bo->borrowISBN,A,Bo->DateBorrowed,Bo->DateToReturn,Bo->DateReturned);
        Bo++;
        i--;
    }
    fclose(k);
    printf("Updating Complete!\n");

}
int Borrowing(book *B,int NBooks,member *M,int NMembers,borrow *Bo,int NBorrow)
{
    int NoOfAdd=0;
    int month,day,year;
    char STime[20],NTime[20];
    printf("---------------\nEnter Your ID Please\nID:");
    int id,i,flag=1,check;
    char isbn[40];
    scanf("%d",&id);
    for(i=0; i<NMembers; i++)
    {
        if(id==M->ID)
        {
            flag=0;
            printf("Name-->%s %s\nEmail-->%s\n",M->FirstName,M->LastName,M->Email,M->age);
        }
        M++;
    }
    if(flag!=0)
    {
        printf("Wrong ID Please Check Again!\n");
        return 0;
    }
    else
        check=Count_Borrow(Bo,NBorrow,id);
    if(check>=3)
    {
        printf("Sorry you Cant Borrow More Than 3 Books!");
        return 0;
    }
    printf("Enter ISBN Of The Book You Want:\nISBN:");
    scanf("%s",isbn);
    for(i=0; i<NBooks; i++)
    {
        int diff=strcasecmp(isbn,B->ISBN);
        if(diff==0)
        {
            flag=0;
            printf("Book Title-->%s\nDate Of Publication-->%s\nAuthor-->%s",B->title,B->DateOfPublication,B->author);
            break;
        }
        else flag=1;
        B++;
    }
    if(flag!=0)
    {
        printf("Wrong ISBN Please Check Again!\n");
        return 0;
    }
    if(B->AvaCopies==0)
    {
        printf("\n\nSorry This Book Isn't Available Now\n ");
        return 0;
    }
    printf("\nAre You Sure You Want To Borrow This Book?\n Press 1 To Confirm And 2 To Cancel\nYour Choice:");
    int ch;
    scanf("%d",&ch);
    while(ch==1)
    {
        gettime(&month,&day,&year,STime);
        Addtime(&month,&day,&year,NTime);
        B->AvaCopies--;
        Bo=Bo+NBorrow;
        Bo->borrowID=id;
        strcpy(Bo->borrowISBN,B->ISBN);
        strcpy(Bo->DateBorrowed,STime);
        strcpy(Bo->DateToReturn,NTime);
        strcpy(Bo->DateReturned,"NULL");
        strcat(Bo->DateReturned,"\n");
        ch--;
        NoOfAdd++;
    }
    return NoOfAdd;
}
int Delete_Book(book B[],int Nbooks) //
{
    int y,stop=-1;
    char i[50];
    printf("Enter ISBN Of The Book You Want To Delete\n");
    scanf("%s",i);
    for(y=0; y<Nbooks; y++)
    {
        int x=strcasecmp(B[y].ISBN,i);
        if(x==0)
        {
            printf("Book Found \n");
            stop=y;
        }
    }
    if(stop==-1)
    {
        printf("Book Not Found");
        return 0;
    }
    book c;
    c=B[Nbooks-1];
    B[Nbooks-1]=B[stop];
    B[stop]=c;
    printf("%s",B[9].ISBN);
    return 1;
}
void Updater_Book(book *S,int NBooks)
{
    printf("\nUpdating Books List ....\n");
    FILE *k=fopen("Books.txt","w");
    while(NBooks)
    {
        char A[5];
        char B[5];
        itoa(S->copies,A,10);
        itoa(S->AvaCopies,B,10);
        fprintf(k,"%s,%s,%s,%s,%s,%s,%s,%s",S->title,S->author,S->publisher,S->ISBN,S->DateOfPublication,A,B,S->Category);
        S++;
        NBooks--;
    }
    fclose(k);
    printf("Updating Complete!\n");




}
int Add_Book(book *Add,int NBooks) //
{
    int NoofAdds=0;
    // Add=Add+NBooks;
    char end[5]="\n";
    char Name[100];
    char Author[50];
    char Publisher[50];
    char ISBN[50];
    char Date[25];
    int Copies;
    int AvaCopies;
    int checker;
    char Category[50];
    fflush(stdin);
    printf("Enter Title Of The Book Please\n");
    gets(Name);
    strcpy(Add->title,Name);
    printf("Enter Author Of The Book:\n");
    gets(Author);
    checker=ifString(strlen(Author),Author);
    while(checker==1)
    {
        printf("ba2olak 2esmo yabny!\n");
        gets(Author);
        checker=ifString(strlen(Author),Author);
    }
    strcpy(Add->author,Author);
    printf("Enter Publisher Of The Book:\n");
    gets(Publisher);
    checker=ifString(strlen(Publisher),Publisher);
    while(checker==1)
    {
        printf("Wrong input!\n");
        gets(Publisher);
        checker=ifString(strlen(Publisher),Publisher);
    }
    strcpy(Add->publisher,Publisher);
    printf("Enter ISBN Of The Book:\n");
    gets(ISBN);
    checker=ifString(strlen(ISBN),ISBN);
    while(checker!=-1)
    {
        printf("Wrong ISBN Form!");
        gets(ISBN);
        checker=ifString(strlen(ISBN),ISBN);
    }
    printf("Enter Date Of Publication Of The Book:\n");
    gets(Date);
    checker=ifString(strlen(Date),Date);
    while(checker!=-1)
    {
        printf("Wrong Date Form!");
        gets(Date);
        checker=ifString(strlen(Date),Date);
    }
    strcpy(Add->DateOfPublication,Date);
    printf("Enter Number Of Copies Of The Book:\n");
    scanf("%d",&Copies);
    Add->copies=Copies;
    printf("Enter Number Of Available Copies Of The Book:\n");
    scanf("%d",&AvaCopies);
    Add->AvaCopies=AvaCopies;
    printf("Enter Category Of The Book:\n");
    scanf("%s",Category);
    strcpy(Add->Category,Category);
    strcat(Add->Category,end);
    NoofAdds++;
    return NoofAdds;


}
void print_Book(book *PrintBook,int NBooks)
{
    int i;
    for(i=0; i<NBooks; i++)
    {
        printf("Book Title:%s \n",PrintBook->title);
        printf("Book Author:%s \n",PrintBook->author);
        printf("Book Publisher:%s \n",PrintBook->publisher);
        printf("Book ISBN:%s \n",PrintBook->ISBN);
        printf("Book Date of publication ; %s \n",PrintBook->DateOfPublication);
        printf("Book Number of Copies=%d \n",PrintBook->copies);
        printf("Book Category:%s \n",PrintBook->Category);
        printf("Available Number Of Copies= %d \n _______________________\n",PrintBook->AvaCopies);
        PrintBook++;
    }

}
int  Counter(FILE *FileName,char File[50]) //
{

    int count=0;
    char c;
    FileName=fopen(File,"r");
    for (c=getc(FileName); c!= EOF; c=getc(FileName))
        if (c=='\n')
            count=count+1;
    fclose(FileName);

    return count;

}
void SearchBooks(book *SearchBook,int NBooks)
{
    int x,y;
    char h[100];
    char *check;
    printf("Select One Of The Following Options \n\n Press 1 To Search Using Book Title \n Press 2 To search Using Book ISBN \nYour Choice=");
    scanf("%d",&x);
    if(x==1)
    {
        int n=NBooks;
        printf("Please Enter The Title Of The Book:");
        fflush(stdin);
        gets(h);
        int flag=1;
        while(n)
        {
            check=strstr(SearchBook->title,h);
            if(check!=NULL)
            {
                printf("Book Title-->(%s)\nBook Author-->(%s)\nPublisher-->(%s)\nBook ISBN-->(%s)\nBook Date Of Publication-->(%s)\nBook Category-->(%sNumber Of Available Copies-->(%d)\n-------------------\n",SearchBook->title,SearchBook->author,SearchBook->publisher,SearchBook->ISBN,SearchBook->DateOfPublication,SearchBook->Category,SearchBook->AvaCopies);
                flag=0;
            }
            n--;
            SearchBook++;
        }
        if(flag==1)
        {
            printf("Book Not Found");
        }
    }

    if(x==2)

    {
        int n=NBooks;
        printf("Please Enter ISBN Of The Book:");
        fflush(stdin);
        gets(h);
        while(n)
        {
            y=strcasecmp(h,SearchBook->ISBN);
            if(y==0)
            {
                printf("\nBook title Is (%s)\nAnd It's Author is:%s\nAnd there are %d Books Available\n",SearchBook->title,SearchBook->author,SearchBook->AvaCopies);
                return;
            }
            n--;
            SearchBook++;
        }
        printf("Book Not Found");
    }




}
void Add_Copy(book *ArrayName,int Number)
{
    printf("\n Please Enter ISBN Of The Book \n");
    int flag=1;
    char I[30];
    fflush(stdin);
    gets(I);
    int n;
    while(Number)
    {
        n=strcmp(I,ArrayName->ISBN);
        if(n==0)
        {
            flag=0;
            int NCopies;
            printf("Enter Number Of Copies \n");
            scanf("%d",&NCopies);
            if(NCopies<0)
            {
                printf("Negative Numbers Aren't Allowed!! \a \a \a");
            }
            ArrayName->copies=ArrayName->copies + NCopies;
            ArrayName->AvaCopies=ArrayName->AvaCopies + NCopies;
            printf("Number Of Books =%d And %d Are Available",ArrayName->copies,ArrayName->AvaCopies);
            break;
        }
        Number--;
        ArrayName++;
    }
    if(flag==0 && ArrayName->AvaCopies!=0)
    {
        printf("Do You want to borrow it?\n");
    }
    else printf("Book Not Found!\n");




}
int main()
{
    FILE *b=fopen("Books.txt","r");
    char FileName[15]="Books.txt";
    int NoOfBooks=Counter(b,FileName);
    book Books[NoOfBooks+20];
    char *ADDING;
    char Line[550];
    int i=0;
    while (fgets(Line,550,b))
    {
        ADDING=strtok(Line,",");
        strcpy(Books[i].title,ADDING);
        ADDING=strtok(NULL,",");
        strcpy(Books[i].author,ADDING);
        ADDING=strtok(NULL,",");
        strcpy(Books[i].publisher,ADDING);
        ADDING=strtok(NULL,",");
        strcpy(Books[i].ISBN,ADDING);
        ADDING=strtok(NULL,",");
        strcpy(Books[i].DateOfPublication,ADDING);
        ADDING=strtok(NULL,",");
        Books[i].copies=atoi(ADDING);
        ADDING=strtok(NULL,",");
        Books[i].AvaCopies=atoi(ADDING);
        ADDING=strtok(NULL,",");
        strcpy(Books[i].Category,ADDING);
        i++;
    }
    fclose(b);
    //_______________________________________________________________//
    FILE *m=fopen("Members.txt","r");
    char FileName2[25]="Members.txt";
    int NoOfMembers=Counter(m,FileName2);
    member Members[NoOfMembers+20];
    i=0;
    char *ADDING2;
    char Line2[550];
    int IDUpdate=0;
    while (fgets(Line2,550,m))
    {
        ADDING2=strtok(Line2,",");
        strcpy(Members[i].LastName,ADDING2);
        ADDING2=strtok(NULL,",");
        strcpy(Members[i].FirstName,ADDING2);
        ADDING2=strtok(NULL,",");
        Members[i].ID=atoi(ADDING2);
        if(Members[i].ID>IDUpdate)
        {
            IDUpdate=Members[i].ID;
        }
        ADDING2=strtok(NULL,",");
        strcpy(Members[i].building,ADDING2);
        ADDING2=strtok(NULL,",");
        strcpy(Members[i].street,ADDING2);
        ADDING2=strtok(NULL,",");
        strcpy(Members[i].city,ADDING2);
        ADDING2=strtok(NULL,",");
        strcpy(Members[i].phone,ADDING2);
        ADDING2=strtok(NULL,",");
        strcpy(Members[i].age,ADDING2);
        ADDING2=strtok(NULL,",");
        strcpy(Members[i].Email,ADDING2);
        i++;
    }
    fclose(m);
    //_______________________________________________________________//
    FILE *Bo=fopen("Borrowed Books.txt","r");
    char FileName3[25]="Borrowed Books.txt";
    int NoOfBorrow=Counter(Bo,FileName3);
    borrow Borrowed[NoOfBorrow+20];
    char *ADDING3;
    char Line3[550];
    i=0;
    while (fgets(Line3,550,Bo))
    {
        ADDING3=strtok(Line3,",");
        strcpy(Borrowed[i].borrowISBN,ADDING3);
        ADDING3=strtok(NULL,",");
        Borrowed[i].borrowID=atoi(ADDING3);
        ADDING3=strtok(NULL,",");
        strcpy(Borrowed[i].DateBorrowed,ADDING3);
        ADDING3=strtok(NULL,",");
        strcpy(Borrowed[i].DateToReturn,ADDING3);
        ADDING3=strtok(NULL,",");
        strcpy(Borrowed[i].DateReturned,ADDING3);
        i++;
    }
    fclose(Bo);
    //_______________________________________________________________//
    printf("Press 1 If You Are A Registered Member\nPress 2 If You Are New Member\nYour Choice-->");
    int y=1,z,c=1;
    char x[10];
    int l=1;
    scanf("%s",x);
    int checker;
    checker=ifString(1,x);
    while(checker!=1)
    {
        printf("Enter Number!\n");
        scanf("%s",x);
        checker=ifString(1,x);
    }
    if(strcasecmp(x,"2")==0)
    {
        NoOfMembers=NoOfMembers+Add_Member(&Members,NoOfMembers,IDUpdate);
    }
    while (c==1)
    {
        printf("\n\n\nPress 1 For Book Management\nPress 2 For Member Management \nPress 3 For Borrow Management \nPress 4 For Administrative Actions \npress 5 To Save And Exit \nPress 6 To Exit Without Saving\nYour Choice-->");
        int c;
        scanf("%d",&c);

        if(c==1)
        {
            printf("\n\nPress 1 To Search For A Book\nPress 2 To Add Copies For A Book\nPress 3 To Add A New Book \nPress 4 To Delete A Book\nPress 5 To View All Books\nPress 6 To Get Back To Main Menu\nYour Choice-->");
            scanf("%d",&z);
            if(z==1)
            {
                SearchBooks(&Books,NoOfBooks);
            }
            if(z==2)
            {
                Add_Copy(&Books,NoOfBooks);
            }
            if(z==3)
            {
                NoOfBooks=NoOfBooks+Add_Book(&Books,NoOfBooks);
            }
            if(z==4)
            {
                NoOfBooks=NoOfBooks-Delete_Book(Books,NoOfBooks);
            }
            if(z==5)
            {
                print_Book(&Books,NoOfBooks);
            }
            if(z==6)
            {
                c=0;
            }

        }
        if(c==2)
        {
            printf("\n\nPress 1 To Delete A Member\nPress 2 To Get Back To Main Menu\nYour Choice-->");
            scanf("%d",&z);
            if(z==1)
            {
                NoOfMembers=NoOfMembers-Delete_Member(Members,NoOfMembers);
            }
            if(z==2)
            {
                c=0;
            }

        }
        if(c==3)
        {
            printf("\n\nPress 1 To Borrow A Book\nPress 2 To Return A Borrowed Book\nPress 3 To Get Back To Main Menu\nYour Choice-->");
            scanf("%d",&z);
            if(z==1)
            {
                NoOfBorrow=NoOfBorrow+Borrowing(&Books,NoOfBooks,&Members,NoOfMembers,&Borrowed,NoOfBorrow);
            }
            if(z==2)
            {
                Return_Book(&Borrowed,NoOfBorrow,&Books,NoOfBooks);
            }
            if(z==3)
            {
                c=0;
            }


        }
        if(c==4)
        {
            printf("\nPress 1 To See Overdue Books' List\nPress 2 To View Our Most Popular Books\nPress 3 To Get Back To Main Menu\nYour Choice-->");
            scanf("%d",&z);
            if(z==1)
            {
                OverDueBooks(&Borrowed,NoOfBorrow);
            }
            if(z==2)
            {
                MostPop(NoOfBooks,Books,Borrowed,NoOfBorrow);
            }
            if(z==3)
            {
                c=0;
            }


        }

        if(c==5)
        {
            Updater_Book(&Books,NoOfBooks);
            Updater_Borrowed_Book(&Borrowed,NoOfBorrow);
            Updater_Member(&Members,NoOfMembers);
        }
        if(c==0)
        {
            printf("---------------------------------------------------");
            c==1;
        }
        if(c!=0 && c!=5 && c!=6)
        {
            printf("\n \nPress 1 For Another Action And 2 To Exit\nYour Choice-->");
            scanf("%d",&c);
        }
        system("cls");
        if(c==2 || c==5 || c==6)
        {
            return 0;
        }
    }
}
