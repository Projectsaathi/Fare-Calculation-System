//required header files
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <string.h>
#include <windows.h>
#include<dos.h>
void newpass();
void list();
void search();
void edit();
void del();
void quit();
FILE *fp,*ft;
struct passenger
{
char pname[40];
char pcode[10];
int age;
char sex;
int adults;
int children;
int old;
char origin[30];
char dest[30];
char dod[10];
char mode;
int dist;
float charge;
float total;
};
struct passenger p;
void SetColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawRectangle(){
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < 78; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(78,0);
    printf("%c",187);
    for(i = 1; i < 25; i++){
        gotoxy(78, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(78, 25);
    printf("%c",188);
    for(i = 77; i > 0; i--){
        gotoxy(i,25);
        if(i == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(0,25);
    printf("%c",200);
    for(i = 24; i > 0; i--){
        gotoxy(0,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 1; i < 78; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 25; i++){
        gotoxy(35,i);
        printf("%c",186);
    }

}

void clearWindow(){
    int i,j;
    for(i = 37; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}

long int recsize;
int main()
{
	int choice;
	while(1)
	{
		system("cls");
		printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("\n\t[ AUTOMETED TICKATING AND FARE CALCULATION SYSTEM  ]");
		printf("\n\n\t\tDhangadhi Engineering College");
		printf("\n\t\t      Dhangadhi,kailali");
		printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("\n\t\t*****************************");
		printf("\n\t\t\tMain Menu");
		printf("\n\t\t*****************************");
		printf("\n\t-----------------------------------------");
		printf("\n\n\t1.NEW PASSENGES DATA ENTRY ");
		printf("\n\n\t2.DISPLAY ALL PASSENGERS RECORDS");
		printf("\n\n\t3.EDID PASSENGERS RECORD");
		printf("\n\n\t4.DELETE PASSENGERS RECORD");
		printf("\n\n\t5.SEARCH PASSENGER RECORD");
		printf("\n\n\t6.EXIT");
		printf("\n\t--------------------------------------");
		printf("\n\t\tEnter your choice(1-6):");
		scanf("\n\n\t%d",&choice);
		switch(choice)
		{
			case 1:  
			newpass();
			 break;
			case 2: 
			 list();
			 break;
			case 3: 
			 edit();
			 break;
			case 4: 
			 del();
			 break;
			case 5:  
			search();
			 break;
			case 6:  
		    exit(0);
		    printf("Envalide choice.....");
}
	}
		}

void newpass()
{
	char another;
	fp=fopen("ticket.dat","rb+");
	if(fp==NULL)
	{
		fp=fopen("ticket.dat","wb+");
		if(fp==NULL)
		{
			puts("Cannot open file");
			exit(0);
		}
	}
recsize=sizeof(p);
fseek(fp,0,SEEK_END);
another='Y';
while(another=='Y'|| another=='y')
	{
	system("cls");
	printf("\n\t*****************************");
	printf("\n\t\tPassengers Details:");
	printf("\n\t*****************************");
	printf("\n\n\t->Enter passenger name:");
	fflush(stdin);
	gets(p.pname);
	printf("\n\t->Enter passenger code:");
	scanf("%s",p.pcode);
	printf("\n\t->Enter age:");
	scanf("%d",&p.age);
	printf("\n\t->Enter sex(M for male and F for female):");
	fflush(stdin);
	scanf("%c",&p.sex);
	printf("\n\t->Enter no. of adults:");
	scanf("%d",&p.adults);
	printf("\n\t->Enter no. of children:");
	scanf("%d",&p.children);
	printf("\n\t->Enter no. of Old people:");
	scanf("%d",&p.old);
	printf("\n\t->Enter place of departure:");
	fflush(stdin);
	gets(p.origin);
	printf("\n\t->Enter destination place:");
	fflush(stdin);
	gets(p.dest);
	printf("\n\t->Enter date of departure(dd-mm-yy):");
	scanf("%s",p.dod);
	printf("\n\t->Enter mode of transportation(B->Bus,T->Train,A->Aviation):");
	fflush(stdin);
	scanf("%c",&p.mode);
	printf("\n\t->Enter distance in km:");
	scanf("%d",&p.dist);
	printf("\n\t->Enter fare per km:");
	scanf("%f",&p.charge);
	p.total=(p.adults+p.children+p.old)*p.charge*p.dist;
	fwrite(&p,recsize,1,fp);
	printf("\n->One record saved.Add another record(Y/N)?:");
	fflush(stdin);
	another=getche();
	}
fclose(fp);
}

void list()
{
	system("cls");
	fp=fopen("ticket.dat","rb+");
	recsize=sizeof(p);
	rewind(fp);
	while(fread(&p,recsize,1,fp)==1)
	{
		printf("\n\t*****************************");
		printf("\n\n\t\tDisplay Menu");
		printf("\n\t*****************************");
		printf("\n\t->Passenger name        : %s",p.pname);
		printf("\n\t->Passenger Code        : %s",p.pcode);
		printf("\n\t->Age(in yrs)           : %d",p.age);
		printf("\n\t->Sex                   : %c",toupper(p.sex));
		printf("\n\t->No. of adults         : %d",p.adults);
		printf("\n\t->No. of children       : %d",p.children);
		printf("\n\t->NO.of Old people      : %d",p.old);
		printf("\n\t->Departure place       : %s",p.origin);
		printf("\n\t->Target Place          : %s",p.dest);
		printf("\n\t->Date of departure     : %s",p.dod);
		printf("\n\t->Mode of transportaion : %c",toupper(p.mode));
		if(toupper(p.mode)=='B')printf(" (Bus)");
		else if(toupper(p.mode)=='T')printf(" (Train)");
		else printf(" (Aviation)");
		printf("\n\t->Distance(in kms)      : %d",p.dist);
		printf("\n\t->Charge per km         : %2.2f",p.charge);
		printf("\n\t->Travelling fare       : %2.2f",p.total);
		printf("\n----------------------------------------------------");
		printf("\n\tPress a key for next record....");
		printf("\n----------------------------------------------------");
		getch();
	}
fclose(fp);
getch();
}

void edit()
{
	char code[10];
	int f=0;
	fp=fopen("ticket.dat","rb+");
	if(fp==NULL)
	{
		fp=fopen("ticket.dat","wb+");
		if(fp==NULL)
		{
			puts("Cannot open file");
			exit(0);
		}
	}
system("cls");
printf("\n\t****************************");
printf("\n\t\tEdit menu");
printf("\n\t***************************");
printf("\n\n\t#Enter passenger code:");
scanf("%s",code);
recsize=sizeof(p);
rewind(fp);
while(fread(&p,recsize,1,fp)==1)
	{
	if(strcmp(p.pcode,code)==0)
		{
		f=1;
		printf("\nThe exixting information is as follows:\n");
		printf("\n\t->Passenger name        : %s",p.pname);
		printf("\n\t->Passenger Code        : %s",p.pcode);
		printf("\n\t->Age(in yrs)           : %d",p.age);
		printf("\n\t->Sex                   : %c",toupper(p.sex));
		printf("\n\t->No. of adults         : %d",p.adults);
		printf("\n\t->No. of children       : %d",p.children);
		printf("\n\t->NO.of Old people      :%d",p.old);
		printf("\n\t->Departure place       : %s",p.origin);
		printf("\n\t->Target Place          : %s",p.dest);
		printf("\n\t->Date of departure     : %s",p.dod);
		printf("\n\t->Mode of transportaion : %c",toupper(p.mode));
		if(toupper(p.mode)=='B')printf(" (Bus)");
		else if(toupper(p.mode)=='T')printf(" (Train)");
		else printf(" (Aviation)");
		printf("\n->Distance(in kms)      : %d",p.dist);
		printf("\n->Charge per km         : %2.2f",p.charge);
		printf("\n->Travelling fare       : %2.2f",p.total);
		printf("\n----------------------------------------------------");
		printf("\nPress a key to proceed....");
		printf("\n----------------------------------------------------");
		getch();

//.......Enter new data..............

		printf("\n\tEnter the new data of Passenger.....\n\n");
		printf("\n\t****************************");
		printf("\n\tNew record of passenger:");
		printf("\n\t****************************");
		printf("\n\t->Enter passenger name:");
		fflush(stdin);
		gets(p.pname);
		printf("\n\t->Enter passenger code:");
		scanf("%s",p.pcode);
		printf("\n\t->Enter age:");
		scanf("%d",&p.age);
		printf("\n\t->Enter sex(M for male and F for female):");
			fflush(stdin);
		scanf("%c",&p.sex);
		printf("\n\t->Enter no. of adults:");
		scanf("%d",&p.adults);
		printf("\n\t->Enter no. of children:");
		printf("\n\t->Enter no. of Old people:");
		scanf("%d",&p.old);
		scanf("%d",&p.children);
		printf("\n\t->Enter place of departure:");
		fflush(stdin);
		gets(p.origin);
		printf("\n\t->Enter destination place:");
		fflush(stdin);
		gets(p.dest);
		printf("\n\t->nEnter date of departure(dd-mm-yy):");
		scanf("%s",p.dod);
		printf("\n\t->Enter mode of transportation(B->Bus,T->Train,A->Aviation):");
		fflush(stdin);
		scanf("%c",&p.mode);
		printf("\n\t->Enter distance in km:");
		scanf("%d",&p.dist);
		printf("\n\t->Enter fare per km:");
		scanf("%f",&p.charge);
		p.total=(p.adults+p.children+p.old)*p.charge*p.dist;
		fseek(fp,-recsize,SEEK_CUR);
		fwrite(&p,recsize,1,fp);
		printf("\n\nData modified!.Press a key to return to main menu...");
		getch();
		break;
		}
	}
	if(f==0)
	{
	printf("\nInvalid passenger code");
	getch();
	}
fclose(fp);
}


void del()
{
char code[10];
char ans;
int f=0;
fp=fopen("ticket.dat","rb+");
if(fp==NULL)
	{
		fp=fopen("ticket.dat","wb+");
		if(fp==NULL)
		{
			puts("Cannot open file");
			exit(0);
		}
	}
system("cls");
printf("\n\t****************************");
printf("\n\t\tDelete menu");
printf("\n\t***************************");
printf("\n\n\tEnter passenger code to delete:");
scanf("%s",code);
recsize=sizeof(p);
rewind(fp);
while(fread(&p,recsize,1,fp)==1)
	{
	if(strcmp(p.pcode,code)==0)
		{
			f=1;
			printf("\n\t->The exixting information is as follows:\n");
			printf("\n\t->Passenger name        : %s",p.pname);
			printf("\n\t->Passenger Code        : %s",p.pcode);
			printf("\n\t->Age(in yrs)           : %d",p.age);
			printf("\n\t->Sex                   : %c",toupper(p.sex));
			printf("\n\t->No. of adults         : %d",p.adults);
			printf("\n\t->No. of children       : %d",p.children);
			printf("\n\t->NO.of Old people      : %d",p.old);
			printf("\n\t->Departure place       : %s",p.origin);
			printf("\n\t->Target Place          : %s",p.dest);
			printf("\n\t->Date of departure     : %s",p.dod);
			printf("\n\t->Mode of transportaion : %c",toupper(p.mode));
			if(toupper(p.mode)=='B')printf(" (Bus)");
			else if(toupper(p.mode)=='T')printf(" (Train)");
			else printf(" (Aviation)");
			printf("\n\t->Distance(in kms)      : %d",p.dist);
			printf("\n\t->Charge per km         : %2.2f",p.charge);
			printf("\n\t->Travelling fare       : %2.2f",p.total);
			printf("\n----------------------------------------------------");
			printf("\n\n\tAre you sure to delete this record(Y/N)?");
			fflush(stdin);
			scanf("%c",&ans);

			if(ans=='y' || ans=='Y')
				{
					ft=fopen("ttemp.dat","wb+");
					rewind(fp);
					while(fread(&p,recsize,1,fp)==1)
						{
							if(strcmp(p.pcode,code)!=0)
							fwrite(&p,recsize,1,ft);
						}
						fclose(fp);
				fclose(ft);
				remove("ticket.dat");
				rename("ttemp.dat","ticket.dat");
				printf("\n\n\tRecord deleted successfully.Press any key...");
				getch();
				break;
				}
				break;
		}
	}
	if(f==0)
	{	
		printf("\n\tInvalid passenger code");
		getch();
}
fclose(fp);
}


void search()
{
	char code[10];
	int f=0;
	fp=fopen("ticket.dat","rb+");
	if(fp==NULL)
	{
		fp=fopen("ticket.dat","wb+");
		if(fp==NULL)
		{
			puts("Cannot open file");
			exit(0);
		}
	}
	system("cls");
	printf("\n\t****************************");
	printf("\n\t\tSearch menu");
	printf("\n\t***************************");
	printf("\n\n\tEnter passenger code:");
	scanf("%s",code);
	recsize=sizeof(p);
	rewind(fp);	
	while(fread(&p,recsize,1,fp)==1)
	{
		if(strcmp(p.pcode,code)==0)
		{
			f=1;
			printf("\n\t->The exixting information is as follows:\n");
			printf("\n\t->Passenger name        : %s",p.pname);
			printf("\n\t->Passenger Code        : %s",p.pcode);
			printf("\n\t->Age(in yrs)           : %d",p.age);
			printf("\n\t->Sex                   : %c",toupper(p.sex));
			printf("\n\t->No. of adults         : %d",p.adults);
			printf("\n\t->No. of children       : %d",p.children);
			printf("\n\t->Departure place       : %s",p.origin);
			printf("\n\t->Target Place          : %s",p.dest);
			printf("\n\t->Date of departure     : %s",p.dod);
			printf("\n\t->Mode of transportaion : %c",toupper(p.mode));
			if(toupper(p.mode)=='B')printf(" (Bus)");
			else if(toupper(p.mode)=='T')printf(" (Train)");
			else printf(" (Aviation)");
			printf("\n\t->Distance(in kms)      : %d",p.dist);
			printf("\n\t->Charge per km         : %2.2f",p.charge);
			printf("\n\t->Travelling fare       : %2.2f",p.total);
			printf("\n----------------------------------------------------");
			printf("\nPress a key to return....");
			printf("\n----------------------------------------------------");
			getch();
			break;
		}
	}
	if(f==0)
	{
		printf("\n\nInvalid passenger code...........");
		getch();
	}
fclose(fp);
}
	
void quit()
{
	system("cls");
	printf("Thank you for using our program");
	printf("Press a key to exit.......");
	getch();
	exit(0);
}

