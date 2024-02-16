//************************************************************
//			   WELCOME
//************************************************************


#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>


void cal(void);



//************************************************************
//	CLASS NAME : DAT
//	DETAILS    : IT CONTROLS ALL THE DATE FUNCTIONS
//************************************************************
class dat
{public:
  void extend_date(int,int,int);
  void current_date(void);
int day,month,year,dob;
}    ;


//************************************************************
//	CLASS NAME : SHIP
//	DETAILS    : IT CONSISTS OF THE SHIPS AVAILABLE
//                   AND THEIR DETAILS
//************************************************************
class ship
{
 public:
  void add_ship(char[],char[]);
  void addition(void);
  void ship_list(void);
  int found_ship(char[]);

  char ships_no[10],ship_name[50];
}shipob;


//************************************************************
//	FUNCTION NAME : PASSW
//	DETAILS       : USED TO CHECK AUTHENTICITY
//************************************************************
void passw()
{int gam,r,pass[5],o,mas,x;
loop2:
x=0;
char f[5]={'9','5','6','0','0'};
mas=0;
clrscr();
cout<<"\nENTER PASSWORD\n";
loop:
gam=0;
for(o=0;o<5;o++)
{
pass[o]=getch();
printf("*");

if(pass[o]==f[o])
{continue;}

else
{gam=1;}}
if(gam==1)
{cout<<"\nInvalid  code\n";
 mas++;
 }

 if(mas!=x&&mas<5)
 {x=mas;
 goto loop;
 }

 if(mas>=5)
 {cout<<"\nInvalid code entered more than 5 times\n";
  for(int y=10;y>0;y--)
 {clrscr();
  cout<<"\nSystem locked for 10 seconds\n";
  cout<<y<<" seconds left\n";
  sleep(1);
 }
 clrscr();
 cout<<"\nWanna Try again or Exit\n";
 cout<<"1.Exit              2.Try again\n" ;
 cin>>r;
 if(r==1)
 exit(0);
 else
 goto loop2;
 }
 }


//************************************************************
//	CLASS NAME : TICKET
//	DETAILS    : IT CONTROLS ALL THE  FUNCTIONS
//		     RELATED TO BOOKING AND CANCELLING
//		     TICKETS
//************************************************************
class ticket
{
 public:
  void reservation(void);
  void cancellation(void);
  void reservation_list(void);
  void shpass_info(void);
 char pname[26],psex,pfrom[15],pto[15],ch;
  long int pkms,page,pfare;
 private:
  int res_no,kms;
  char name[20],sex,sh_no[10];
  int age,fare;
  int dd,mm,yy;
  char from[20],to[20];
}tob;




//**********************************************************
//	FUNCTION NAME : DAT
//	DETAILS       : USED TO GET CURRENT DATE
//**********************************************************
void dat::current_date(void)
{
 struct date d;
 getdate(&d);
 day=d.da_day;
 month=d.da_mon;
 year=d.da_year;
}



//************************************************************
//	FUNCTION NAME : EXTEND_DAT
//	DETAILS       : USED TO GET NEXT DATE
//************************************************************
void dat::extend_date(int dday,int dmonth,int dyear)
{
 static int m[]={31,29,31,30,31,30,31,31,30,31,30,31};
 dday++;
  if((dday>m[dmonth-1])||(dyear%4!=0&&dmonth==2&&dday>28))
  {
   dday=1;
   dmonth++;
  }
  if(dmonth>12)
  {
   dmonth=1;
   dyear++;
  }
   day=dday;
   month=dmonth;
   year=dyear;
}



//************************************************************
//	FUNCTION NAME : ADD_SHIP()
//	DETAILS       : IT ADDS SHIPS AVAILABLE TO SHIP.DAT
//************************************************************
void ship::add_ship(char sh1no[10],char shipname[50])
{
 fstream file;
 file.open("ship.dat",ios::app|ios::binary);

 strcpy(ship_name,shipname);
 strcpy(ships_no,sh1no);

 file.write((char*)&shipob,sizeof(ship));
 file.close();
}



//************************************************************
//	FUNCTION NAME : ADDITION()
//	DETAILS       : IT ADDS AVAILABLE SHIPS
//                      USING ADD_SHIP()
//************************************************************
void ship::addition(void)
{
 fstream file;
 file.open("ship.dat",ios::in|ios::binary);

 if(!file.fail())
 return;

 file.close();

 add_ship("b21","Star Cruise");
 add_ship("b22","Royal Cerribbes Cruise");
 add_ship("b23","Paradise Cruise");
 add_ship("b24","Royal British Cruise");
 add_ship("b25","Sunrise Cruise");

}



//************************************************************
//	FUNCTION NAME : SHIP_LIST()
//	DETAILS       : DISPLAYS LIST OF AVAILABLE SHIPS
//************************************************************
void ship::ship_list(void)
{
 fstream file;
 file.open("ship.dat",ios::in|ios::binary) ;

 gotoxy(15,1);
 cout<<"List of the ships";
 cout<<"\n**********************************************";
 gotoxy(2,4);
 cout<<"Ship no.              Ship name ";
 gotoxy(1,5);
 cout<<"**********************************************";
 int row=7;

 while(file.read((char*)&shipob,sizeof(ship)))
 {
  gotoxy(4,row);
  cout<<ships_no;
  gotoxy(20,row);
  cout<<ship_name;
  row++;
 }

 file.close();
}



//************************************************************
//	FUNCTION NAME : FOUND_SHIP()
//	DETAILS       : CHECKS IF SHIP EXISTS IN THE RECORDS
//************************************************************
int ship::found_ship(char sh1no[5])
{
 fstream file;
 file.open("ship.dat",ios::in|ios::binary);

 int found=0;

 while(file.read((char*)&shipob,sizeof(ship)))
 {
  if(!strcmpi(sh1no,ships_no))
   {
    found=1;
    break;
   }
 }
 file.close();
 return found;
}



//************************************************************
//	FUNCTION NAME : RESERVATION()
//	DETAILS       : USED TO RESERVE TICKETS
//************************************************************
void ticket::reservation(void)
{
 clrscr();
 char sh1no[10];
 shipob.ship_list();
 cout<<endl<<"\n\nEnter the ship no. :\n";
 cin>>sh1no;
 if(!shipob.found_ship(sh1no))
 {
  cout<<"\n\n Ship no is invalid ";
  getch();
  cal();
  return;
 }

 clrscr();
 int d1,m1,y1,d2,m2,y2,d3,m3,y3,d4,m4,y4;
 int d,m,y;
 dat dt;

 cout<<"\nYou can reserve ticket only for 3 days,following the current date\n";

 dt.current_date();
 d1=dt.day;
 m1=dt.month;
 y1=dt.year;

 cout<<"1:"<<d1<<"/"<<m1<<"/"<<y1<<"\n";

 dt.extend_date(d1,m1,y1);
 d2=dt.day;
 m2=dt.month;
 y2=dt.year;
 cout<<"2:"<<d2<<"/"<<m2<<"/"<<y2<<"\n";

 dt.extend_date(d2,m2,y2);
 d3=dt.day;
 m3=dt.month;
 y3=dt.year;
 cout<<"3:"<<d3<<"/"<<m3<<"/"<<y3<<"\n";

 dt.extend_date(d3,m3,y3);
 d4=dt.day;
 m4=dt.month;
 y4=dt.year;
 cout<<"4:"<<d4<<"/"<<m4<<"/"<<y4<<"\n";

 int sno=0;
 cout<<"\nEnter sno. of the date of reservation :\n";
 cin>>sno;

 if(sno<1||sno>4)
 {
  cout<<"\nInvalid data";
  getch();
  return;
 }

 switch(sno)
 {
  case 1: d=d1;
	  m=m1;
	  y=y1;
	  break;

  case 2: d=d2;
	  m=m2;
	  y=y2;
	  break;

  case 3: d=d3;
	  m=m3;
	  y=y3;
	  break;

  case 4: d=d4;
	  m=m4;
	  y=y4;
	  break;

  default: break;
  }

  int reservation1=0;

  fstream file;
  file.open("ticket.dat",ios::in|ios::binary);

  while(file.read((char*)&tob,sizeof(ticket)))
  {
   if((dd==d&&mm==m&&yy==y)&&!strcmpi(sh_no,sh1no))
   reservation1=res_no;
  }

  file.close();

  reservation1++;

  clrscr();

  cout<<"\nEnter name of passenger:";
  gets(pname);
  cout<<"\nEnter age:";
  cin>>page;
  if(page<=5)
  {
   cout<<"\nNo ticket required upto age 5";
   getch();
   cal();

  }

  do
  {
   cout<<"\nEnter sex(M/F):";
   cin>>psex;
  }while(toupper(psex)!='M'&& toupper(psex)!='F');

  cout<<"\nTravelling From:";
  gets(pfrom);
  cout<<"\nTo:";
  gets(pto);
  cout<<"\nEnter kms. :";
  cin>>pkms;
  pfare=pkms*3;
  clrscr();

  gotoxy(5,5);
  cout<<"******************************************************";

  gotoxy(22,7)     ;
  cout<<"International Cruise pvt ltd";

  gotoxy(10,9);
  cout<<"Reservation no."<<reservation1<<"  Date:"<<d<<"/"<<m<<"/"<<y;

  gotoxy(10,10);
  cout<<"Ship no. :"<<sh1no;

  gotoxy(35,12);
  cout<<"From:"<<pfrom<<" To:"<<pto;

  gotoxy(35,13);
  cout<<"Kms."<<pkms;

  gotoxy(10,15);
  cout<<"Passenger name:"<<pname;

  gotoxy(10,16);
  cout<<"Passenger age:"<<page<<"  Sex :"<<psex;

  gotoxy(10,18);
  cout<<"Total fare:"<<pfare;

  gotoxy(5,20);
  cout<<"******************************************************";

  cout<<"\n\n\n";

  do
  {
   cout<<"Do you want to save ticket(y/n):";
   cin>>ch;
  }while(toupper(ch)!='Y'&& toupper(ch)!='N');

  if(toupper(ch)=='N')
  return;

  ticket t;

  file.open("ticket.dat",ios::app|ios::binary);
  t.res_no=reservation1;
  t.kms=pkms;
  strcpy(t.name,pname);
  strcpy(t.sh_no,sh1no);
  strcpy(t.from,pfrom);
  strcpy(t.to,pto);
  t.sex=psex;
  t.age=page;
  t.fare=pfare;
  //cout<<t.fare<<endl<<endl;
  t.dd=d;
  t.mm=m;
  t.yy=y;
  file.write((char*)&t,sizeof(ticket));
  file.close();
}


//************************************************************
//	FUNCTION NAME : CANCELLATION()
//	DETAILS       : USED TO CANCEL TICKET
//************************************************************
void ticket::cancellation(void)
{
 clrscr();
 char sh1no[10];
 shipob.ship_list();
 cout<<"\nEnter the ship no. :\n";
 cin>>sh1no;
 if(!shipob.found_ship(sh1no))
 {
  cout<<"\nShip no is invalid";

  getch();
  cal();
  return;
 }

 clrscr();

 int d1,m1,y1,d2,m2,y2,d3,m3,y3,d4,m4,y4;
 int d,m,y;
 dat dt;

 dt.current_date();
 d1=dt.day;
 m1=dt.month;
 y1=dt.year;
 cout<<"1:"<<d1<<"/"<<m1<<"/"<<y1<<"\n";

 dt.extend_date(d1,m1,y1);
 d2=dt.day;
 m2=dt.month;
 y2=dt.year;
 cout<<"2:"<<d2<<"/"<<m2<<"/"<<y2<<"\n";

 dt.extend_date(d2,m2,y2);
 d3=dt.day;
 m3=dt.month;
 y3=dt.year;
 cout<<"3:"<<d3<<"/"<<m3<<"/"<<y3<<"\n";

 dt.extend_date(d3,m3,y3);
 d4=dt.day;
 m4=dt.month;
 y4=dt.year;
 cout<<"4:"<<d4<<"/"<<m4<<"/"<<y4<<"\n";

 int sno=0;
 cout<<"Enter sno. of the date for ticket cancellation:";
 cin>>sno;
 if(sno<1||sno>4)
 {
  cout<<"\nInvalid data";

  getch();
  cal();
  return;
 }

 switch(sno)
 {
  case 1: d=d1;
	  m=m1;
	  y=y1;
	  break;

  case 2: d=d2;
	  m=m2;
	  y=y2;
	  break;

  case 3: d=d3;
	  m=m3;
	  y=y3;
	  break;

  case 4: d=d4;
	  m=m4;
	  y=y4;
	  break;

  default: break;
  }

  int reservation1=0,found=0;
  char ch;
  cout<<"Enter reservation no of the ticket to be cancelled:";
  cin>>reservation1;

  fstream file,temp8;
  file.open("ticket.dat",ios::in|ios::binary);
  temp8.open("temp8.dat",ios::out|ios::binary);

  while(file.read((char*)&tob,sizeof(ticket)))
  {
   if((dd==d&&mm==m&&yy==y)&&!strcmpi(sh_no,sh1no)&&reservation1==res_no)
    {
      cout<<"Displaying ticket:";
      found=1;
      clrscr();

   gotoxy(5,5);
   cout<<"******************************************************";

   gotoxy(22,7)      ;
   cout<<"International Cruise pvt ltd";

   gotoxy(10,9);
   cout<<"Reservation no."<<reservation1<<"        Date:"<<d<<"/"<<m<<"/"<<y;

   gotoxy(10,10);
   cout<<"Ship no. :"<<sh1no;

   gotoxy(35,12);
   cout<<"From:"<<from<<"  To:"<<to;

   gotoxy(35,13);
   cout<<"Kms."<<kms;

   gotoxy(10,15);
   cout<<"Passenger name:"<<name;

   gotoxy(10,16);
   cout<<"Passenger age:"<<age<<" Sex :"<<sex;

   gotoxy(10,18);
   cout<<"Total fare:"<<fare;

   gotoxy(5,20);
   cout<<"*****************************************************";

   gotoxy(1,25);
   clreol();

   cout<<"\nDo you want to cancel ticket(y/n):";
   cin>>ch;

   if(toupper(ch)=='Y')
   {
    gotoxy(2,25);
    clreol();
    cout<<"Ticket cancelled";
   }

   else if(toupper(ch)=='N')
   return;
   }

   else
   temp8.write((char*)&tob,sizeof(ticket));
   }

   file.close();
   temp8.close();
   remove("ticket.dat");
   rename("temp8.dat","ticket.dat");

   if(!found)
   {
    cout<<"\nTicket not found:";
    getch();

   }
}




//************************************************************
//	FUNCTION NAME : RESRVATION_LIST()
//	DETAILS       : USED TO GET LIST OF RESERVED TICKETS
//************************************************************
void ticket::reservation_list(void)
{
 clrscr();
 char sh1no[5];
 shipob.ship_list();

 cout<<"\nEnter the ship no. for the reservation list\n";
 cin>>sh1no;

 if(!shipob.found_ship(sh1no))
 {
  cout<<"\nShip no is invalid";

  getch();
  cal();
  return;
 }
 clrscr();

 int d1,m1,y1,d2,m2,y2,d3,m3,y3,d4,m4,y4;
 int d,m,y;
 dat dt;

 dt.current_date();
 d1=dt.day;
 m1=dt.month;
 y1=dt.year;
 cout<<"1:"<<d1<<"/"<<m1<<"/"<<y1<<"\n";

 dt.extend_date(d1,m1,y1);
 d2=dt.day;
 m2=dt.month;
 y2=dt.year;
 cout<<"2:"<<d2<<"/"<<m2<<"/"<<y2<<"\n";

 dt.extend_date(d2,m2,y2);
 d3=dt.day;
 m3=dt.month;
 y3=dt.year;
 cout<<"3:"<<d3<<"/"<<m3<<"/"<<y3<<"\n";

 dt.extend_date(d3,m3,y3);
 d4=dt.day;
 m4=dt.month;
 y4=dt.year;
 cout<<"4:"<<d4<<"/"<<m4<<"/"<<y4<<"\n";

 int sno=0;
 cout<<"\nEnter sno. of the date for reservation list \n";
 cin>>sno;
 if(sno<1||sno>4)
 {
  cout<<"Invalid data";

  getch();
  cal();
  return;
 }

 switch(sno)
 {
  case 1: d=d1;
	  m=m1;
	  y=y1;
	  break;

  case 2: d=d2;
	  m=m2;
	  y=y2;
	  break;

  case 3: d=d3;
	  m=m3;
	  y=y3;
	  break;

  case 4: d=d4;
	  m=m4;
	  y=y4;
	  break;

  default: break;
  }

  clrscr();
  fstream file;
  file.open("ticket.dat",ios::in|ios::binary);

  gotoxy(15,1)  ;
  cout<<"Reservation list of the passengers";

  cout<<"\n**********************************************************";
  cout<<"\nShip no. :"<<sh1no<<"  Date:"<<d<<"/"<<m<<"/"<<y;

  gotoxy(2,5);
  cout<<"Res. no.    Passenger name         From               To ";

  gotoxy(1,6);
  cout<<"**********************************************************";

  int row=8,found=0;

  while(file.read((char*)&tob,sizeof(ticket)))
  {
   if((dd==d&&mm==m&&yy==y)&&!strcmpi(sh_no,sh1no))
   {
    found=1;

    gotoxy(4,row);
    cout<<res_no;

    gotoxy(14,row);
    cout<<name;

    gotoxy(41,row) ;
    cout<<from;

    gotoxy(56,row);
    cout<<to;

    row++;

    if(row==25)
    {
     getch();
     clrscr();

     for(int i=8;i<=24;i++)
     {
      gotoxy(1,i);
      clreol();
     }
     row=8;
    }
   }
  }
  file.close();
  if(!found)
  {
   cout<<"\nNo reservation";
   getch();
   return;
  }
  cout<<"\n\n\nPress any key to continue.......";
  getch();
}





//************************************************************
//	FUNCTION NAME : SHPASS_INFO()
//	DETAILS       : USED TO GET PASSENGER INFO
//************************************************************
void ticket::shpass_info(void)
{
 clrscr();
 char sh1no[5];
 shipob.ship_list();
 cout<<"Enter the ship no. :\n"       ;
 cin>>sh1no;

 if(!shipob.found_ship(sh1no))
 {
  cout<<"Ship no is invalid\n";
  getch();
  return;
 }

 clrscr();

 int d1,m1,y1,d2,m2,y2,d3,m3,y3,d4,m4,y4;
 int d,m,y;
 dat dt;

 dt.current_date();
 d1=dt.day;
 m1=dt.month;
 y1=dt.year;
 cout<<"1:"<<d1<<"/"<<m1<<"/"<<y1<<"\n";

 dt.extend_date(d1,m1,y1);
 d2=dt.day;
 m2=dt.month;
 y2=dt.year;
 cout<<"2:"<<d2<<"/"<<m2<<"/"<<y2<<"\n";

 dt.extend_date(d2,m2,y2);
 d3=dt.day;
 m3=dt.month;
 y3=dt.year;
 cout<<"3:"<<d3<<"/"<<m3<<"/"<<y3<<"\n";

 dt.extend_date(d3,m3,y3);
 d4=dt.day;
 m4=dt.month;
 y4=dt.year;
 cout<<"4:"<<d4<<"/"<<m4<<"/"<<y4<<"\n";

 int sno=0;
 cout<<"\nEnter sno. of the date for passenger information \n";
 cin>>sno;
 if(sno<1||sno>4)
 {
  cout<<"Invalid data";

  getch();
  cal();
  return;
 }

 switch(sno)
 {
  case 1: d=d1;
	  m=m1;
	  y=y1;
	  break;

  case 2: d=d2;
	  m=m2;
	  y=y2;
	  break;

  case 3: d=d3;
	  m=m3;
	  y=y3;
	  break;

  case 4: d=d4;
	  m=m4;
	  y=y4;
	  break;

  default: break;
 }

 int reservation1=0,found=0;

 cout<<"\nEnter reservation no of the ticket:\n";
 cin>>reservation1;

 fstream file;
 file.open("ticket.dat",ios::in|ios::binary);

 while(file.read((char*)&tob,sizeof(ticket)))
 {
  if((dd==d&&mm==m&&yy==y)&&!strcmpi(sh_no,sh1no)&&reservation1==res_no)
  {
   found=1;
   clrscr();
   gotoxy(5,5);

   cout<<"**********************************************************";

   gotoxy(23,7);
   cout<<"International Cruise pvt ltd";

   gotoxy(10,9);
   cout<<"Reservation no. "<<res_no<<"            Date:"<<dd<<"/"<<mm<<"/"<<yy;

   gotoxy(10,10)     ;
   cout<<"Ship no :"<<sh_no;

   gotoxy(28,12);
   cout<<"From:"<<from<<"   To:"<<to;

   gotoxy(30,13);
   cout<<"Kms. :"<<kms;

   gotoxy(10,16);
   cout<<"Passenger name :"<<name;

   gotoxy(10,17);
   cout<<"Passenger age :"<<age<<"\t Sex :"<<sex;

   gotoxy(10,18);
   cout<<"Total fare:"<<fare;

   gotoxy(5,21)       ;
   cout<<"**********************************************************";

   gotoxy(5,22);
   cout<<"Press any key to continue.....";
   getch();
   break;
   }
  }
  file.close();

  if(!found)
  {
   cout<<"\nTicket not found";
   getch();
  }
}





//************************************************************
//	FUNCTION NAME : TEXTCOLOOR()
//	DETAILS       : USED TO CHANGE COLOUR SCHEME
//                      OF PROGRAM
//************************************************************
void textcoloor()
{clrscr();

 int tcolor,bcolor;
 cout<<" COLORS (text mode)\n";
 cout<<"            ³     ³Back-³Fore-\n";
 cout<<"Constant    ³Value³grnd?³grnd?\n";
 cout<<"ÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍØÍÍÍÍÍØÍÍÍÍÍ\n";
 cout<<"BLACK       ³  0  ³ Yes ³ Yes\n" ;
 cout<<"BLUE        ³  1  ³ Yes ³ Yes\n" ;
 cout<<"GREEN       ³  2  ³ Yes ³ Yes\n";
 cout<<"CYAN        ³  3  ³ Yes ³ Yes\n";
 cout<<"RED         ³  4  ³ Yes ³ Yes\n";
 cout<<"MAGENTA     ³  5  ³ Yes ³ Yes\n";
 cout<<"BROWN       ³  6  ³ Yes ³ Yes\n";
 cout<<"LIGHTGRAY   ³  7  ³ Yes ³ Yes\n";
 cout<<"DARKGRAY    ³  8  ³ No  ³ Yes\n";
 cout<<"LIGHTBLUE   ³  9  ³ No  ³ Yes\n";
 cout<<"LIGHTGREEN  ³ 10  ³ No  ³ Yes\n";
 cout<<"LIGHTCYAN   ³ 11  ³ No  ³ Yes\n";
 cout<<"LIGHTRED    ³ 12  ³ No  ³ Yes\n";
 cout<<"LIGHTMAGENTA³ 13  ³ No  ³ Yes\n";
 cout<<"YELLOW      ³ 14  ³ No  ³ Yes\n";
 cout<<"WHITE       ³ 15  ³ No  ³ Yes\n";
 cout<<"ÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄ \n\n";
cout<<"Enter textcolor\n";
cin>>tcolor;
cout<<"Enter backgroundcolor\n";
cin>>bcolor;
if(tcolor==bcolor)return;
textcolor(tcolor);
textbackground(bcolor);


}





//************************************************************
//	FUNCTION NAME : ERROR()
//	DETAILS       : USED TO RESET FILES IN CASE OF ERROR
//************************************************************
void error()
{clrscr();
int k;
cout<<"\n\nWhat do you want?\n" ;
cout<<"1.Refresh ship details\n" ;
cout<<"2.Clear reserved tickets\n";
cout<<"3.Go back\n";
 cin>>k;
 if(k==1)
{remove("ship.dat");
shipob.addition();
}
if(k==2)
{remove("ticket.dat");
}
if(k==3)
{return;}
}




//************************************************************
//	FUNCTION NAME : MAIN()
//	DETAILS       : INITIALISES THE PROGRAM
//************************************************************
void main()
{clrscr();
 textcolor(2);
 textbackground(0);
 passw();
 cal();
 }





//***********************************************************
//	FUNCTION NAME : CAL()
//	DETAILS       : CONTROLS ALL THE FUNCTIONS
//***********************************************************
void cal(void)
{  char ch,a=30,a1=31;
    shipob.addition();
 while(1)
 {
  clrscr();
  gotoxy(23,6);
  cout<<"***INTERNATIONAL CRUISE PVT. LTD.***";
  gotoxy(29,7);
  for(int i=1;i<=22;i++)
  {
   if(i%2)
    cout<<a;
   else
    cout<<a1;
  }

  gotoxy(29,8);
  cout<<"1::SHIP LIST";

  gotoxy(29,9);
  cout<<"2::RESERVATION";

  gotoxy(29,10);
  cout<<"3::CANCELLATION";

  gotoxy(29,11);
  cout<<"4::RESERVATION LIST";

  gotoxy(29,12);
  cout<<"5::PASSENGER INFO.";

  gotoxy(29,13);
  cout<<"6::QUIT";

  gotoxy(2,15);
  cout<<"In case system is corrupted,press 9:::::ALL RECORDS WILL BE DELETED";
  gotoxy(29,14);
  cout<<"0::For Interface settings";

  gotoxy(29,18)         ;
  cout<<"Enter your choice :";
  ch=getche();

  if(ch=='6')
  exit(0);

  switch(ch)
  {
   case '1': {clrscr();
   shipob.ship_list();
	   gotoxy(1,25);
	   cout<<"Press any key to continue....";
	   getch();
	   break;}

   case '2': {tob.reservation();
	      break;}

   case '3':{ tob.cancellation();
	     break;}

   case '4':{ tob.reservation_list();
	     break;}

   case '5': {tob.shpass_info();
	      break;
	      }

   case '9': {error();
	     break;}

   case '0': {textcoloor();
	     break;}

   default: break;
  }  }
}
