#include<fstream.h>
#include<process.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>

//function declaration
int check_exist();
void insert();
void search_name();
void search_no();
void search_budget();
void search();
void display_packs();
void display_ticket();
void customer_details();
void delete_name();
void delete_serial();
void del();
void line(int,char);
void login();
int get_cno();
void book_ticket();
void cancel_ticket();

//----------------------------------classes----------------------------------
					//creating a class named packges
class package
{
	private:
		char package_name[20];
		int serial_no;
		char transport_mode[20];
		char description[50];
		float price_per_head;
		long tel_no;

	public:

		void getdata(char pkn[],int sno)     //function to getdata
		{
			cout<<"Serial number     : ";
			serial_no=sno;
			cout<<serial_no<<endl;
			strcpy(package_name,pkn);
			cout<<"Mode of transport : ";
			gets(transport_mode);
			cout<<"Description       : ";
			gets(description);
			cout<<"Price per Head    : Rs.";
			cin>>price_per_head;
		}

		void display()                      //to display data
		{
			cout<<"\nSerial Number	  	: ";
			cout<<serial_no;
			cout<<"\n\nPackage Name		: ";
			puts(package_name);
			cout<<"\nMode of Transport	: ";
			puts(transport_mode);
			cout<<"\nDestinations		: ";
			puts(description);
			cout<<"\nPrice Per Head		: Rs.";
			cout<<price_per_head;
		}

		float return_price()               //to return the value of price
		{
			return price_per_head;
		}

		char* return_name()                //to return package name
		{
			return (package_name);
		}

		long return_sno()                 //to return serial no
		{
			return (serial_no);
		}
};

					//creating a class named customer
class customer
{
	private:
		int chk_no, date, month, year;
		char package_name[20];
		char name[10][10];
		char address[40],gen[10][2], contact_no[11];
		int age[10];
		int ph_no,totmem,pkg_no,child;
		float totfare;

	public:

		int accept(int chk,char *);
		void display();
		void ticket();
		void info();

		int no_memb()             //to return total number of members
		{
			return totmem;
		}

		int no_child()           //to return no. of children
		{
			return child;
		}


		int return_chk()        //to return chk no.
		{
			return chk_no;
		}

		void setfare(float tf)     //to calculate total fare
		{
			totfare=tf;
			cout<<"\nTotal Fare	: Rs."<<totfare<<endl;
		}

};
//------------------------------------MAIN-----------------------------------
void main()
{
	int ch;
	customer c;
	do
	{
		clrscr();
		cout<<"MAIN MENU\n";
		cout<<"1. Book a ticket"<<endl;
		cout<<"2. Display the packages"<<endl;
		cout<<"3. Search for packages"<<endl;
		cout<<"4. Issue Ticket"<<endl;
		cout<<"5. Cancel ticket"<<endl;
		cout<<"6. Members' Login"<<endl;
		cout<<"7. exit"<<endl;
		cout<<"Enter your choice	:  ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				book_ticket();
				break;

			case 2:
				display_packs();
				break;

			case 3:
				search();
				break;

			case 4:
				display_ticket();
				break;

			case 5:
				cancel_ticket();
				break;

			case 6:
			login();
			 //	cout<<"under construction";
				break;

			case 7:

				break;

			default:
				cout<<"Enter a valid digit\n";
		}
		getch();
	}while(ch!=7);
}



//----------------------------------FUNCTIONS--------------------------------

int customer::accept(int chk,char * pn)
{
	cout<<"\n\nCHK number     : ";
	chk_no=chk;
	cout<<chk_no<<endl;
	cout<<"\nNumber of members	: ";
	cin>>totmem;
	if(totmem<=0)
		return 0;
	//chk=100000;
	strcpy(package_name,pn);
	cout<<"\nEnter the details of the members  : ";
	child=0;
	for(int i=0; i<totmem; ++i)
	{
		cout<<"\nMember "<<i+1;
		cout<<"\nName  		: ";
		gets(name[i]);
		cout<<"\nAge  		: ";
		cin>>age[i];
		if(age[i]<=12)
		child++;
		cout<<"\nGender [M/F]	: ";
		cin>>gen[i];
	}
	cout<<"\nPreferred date of journey	: ";
	cin>>date;
	cout<<"\nMonth				: ";
	cin>>month;
	cout<<"\nYear				: ";
	cin>>year;
	cout<<"\nAddress			: ";
	gets(address);
	cout<<"\nContact number	    		: ";
	cin>>contact_no;
	return 1;
}

void  customer::display()
{
	cout<<"\nName\tAge\tGender"<<endl;
	for(int i=0; i<totmem; ++i)
	{
		cout<<"\nName	: ";
		cout<<name[i];
		cout<<"\nAge	: ";
		cout<<"\t"<<age[i];
		cout<<"\nGender	: ";
		cout<<"\t"<<gen[i];
		cout<<endl;
	}
}

void  customer::ticket()
{

	package p;
	cout<<"Date of journey  : "<<date<<"/"<<month<<"/"<<year<<endl;
	cout<<"CHK number       : "<<chk_no<<endl;
	cout<<"Package Name	: "<<package_name;
	cout<<endl;
	cout<<"\nName\tAge\tGender"<<endl;
	for(int i=0; i<totmem; ++i)
	{
		cout<<name[i];
		cout<<"\t"<<age[i];
		cout<<"\t"<<gen[i];
		cout<<endl;
	}
	cout<<"\n\nTotal Cost	: Rs."<<totfare;
}


int check_exist(char pn[],int&sn)
{
	package t;
	int found=0;
	fstream file;
	sn=0;
	file.open("PACKAGES.TXT",ios::in|ios::binary);
	file.read((char*)&t,sizeof(t));
	if(file.fail())      		//file is empty
	{
		file.close();
		return found;
	}
	while(!file.eof())
	{
		if(strcmp(pn,t.return_name())==0)
		{
			found=1;
			break;
		}
		sn=t.return_sno();
		file.read((char*)&t,sizeof(t));
	}
	file.close();
	return found;
}


void insert()
{
	clrscr();
	fstream pack;
	char p_name[20];
	int sno;
	package a;
	cout<<endl;
	char ans;
	cout<<"Insert new packages ....";
	cout<<"\nEnter the details  : \n";
	line(40,'-');
	cout<<endl;
	do
	{
	    //	clrscr();
		cout<<"\nPackage name      : ";
		gets(p_name);
		int exist=check_exist(p_name,sno);
		pack.open("PACKAGES.TXT", ios::app | ios::binary);
		int n;
		if(exist==1)
		{
			cout<<"Package Exists!!!!";
			return;
		}
		a.getdata(p_name,++sno);
		pack.write((char*)&a,sizeof(a));
		cout<<"Do yo want to enter more? [Y/N] : ";
		cin>>ans;
		ans=toupper(ans);
		pack.close();
	}
	while(ans!='N');

}



void search_name()
{
	fstream file;
	file.open("PACKAGES.TXT",ios::in|ios::binary);
	package p;
	int found=0;
	char name[10];
	cout<<"\nEnter the name of the package	  :   ";
	cin>>name;
	file.read((char*)&p,sizeof(p));
	while(!file.eof())
	{

		if(strcmp(name,p.return_name())==0)
		{
			found=1;
			cout<<endl;
			p.display();
			cout<<endl;
			line(40,'-');
		       //	getch();
			break;
		}
	}
	if(found==0)
		cout<<"\nRecord not found";
	getch();
	file.close();
}

void search_no()
{
	fstream file;
	file.open("PACKAGES.TXT",ios::in|ios::binary);
	package p;
	int found=0;
	int serial_no;
	cout<<"\nEnter the serial number of the package	  :  ";
	cin>>serial_no;
	file.read((char*)&p,sizeof(p));
	while(!file.eof())
	{
		if(serial_no==p.return_sno())
		{
			found=1;
			cout<<endl;
		//line(40,'-');
			p.display();
			cout<<endl;
			line(40,'-');
			break;
		}
		file.read((char*)&p,sizeof(p));
	}
	if(found==0)
		cout<<"\tPackage not found";
	getch();
	file.close();

}

void search_budget()
{
	fstream file;
	file.open("PACKAGES.TXT",ios::in|ios::binary);
	package p;
	int found=0;
	float budget;
	cout<<"\nEnter the approximate budget	: Rs.";
	cin>>budget;
	file.read((char*)&p,sizeof(p));
	while(!file.eof())
	{

		do
		{
			if(budget>p.return_price())
			{
			       //	for(int k=0; k<2; ++k)
			       //	{
				cout<<"\n\n";
				found++;
				cout<<endl;
				//line(40,'-');
				p.display();
				cout<<endl;
				line(40,'-');
			      //	}
			       //	getch();
//				break;
			}
			else
			{
				found=0;
				break;
			}
		}while(found);
	}
	if(found==0)
	cout<<"\tRecord not found";
	getch();
	file.close();
}

void search()
{
	clrscr();
	cout<<"*\t SEARCH A RECORD\t *";
	int ans;
	do
	{
	clrscr();
	cout<<"\nPress";
	cout<<"\n1.to search by package name\n";
	cout<<"\n2.to search by serial number\n";
	cout<<"\n3.to search by approximate budget\n";
	cout<<"\n4.Go to main menu\n\n";
	cout<<"Enter your choice : ";
	cin>>ans;
	switch(ans)
	{
		case 1:
			search_name();
			break;
		case 2:
			search_no();
			break;
		case 3:
			search_budget();
			break;
		case 4:
			exit(0);
			break;

		default:
			cout<<"Invalid Digit entered\n";
			cout<<"Press a valid digit";
			cin>>ans;
			break;
	}
	}while(ans<=4);


}


void display_packs()
{
	clrscr();
	fstream pack;
	package e;
	pack.open("PACKAGES.TXT",ios::in | ios::binary);
	cout<<"\nThe Packages are  : "<<endl;
	line(40,'-');
	pack.read((char*)&e,sizeof(e));
	while(!pack.eof())
	{
		for(int k=0; k<2; ++k)
		{
			cout<<endl;
			e.display();
			cout<<endl;
			line(40,'-');
			pack.read((char*)&e,sizeof(e));
		}
		getch();
		clrscr();
	}
	pack.close();
}



void display_ticket()
{
	clrscr();
	fstream details;
	int chk;
	customer c;
	int found=0;
	details.open("BOOKINGS.TXT",ios::in | ios::binary);
	cout<<"\nEnter the CHK number	: ";
	cin>>chk;
 /*	if(chk==c.return_chk())
	{
		int chk_no;
		cout<<"\nEnter the serial number of the package	  :  ";
		cin>>serial_no;*/
	while(!details.eof())
	{
		details.read((char*)&c,sizeof(c));
		if(chk==c.return_chk())
		{
			found=1;
			cout<<endl;
			//line(40,'-');
			c.ticket();
			cout<<endl;
			line(40,'-');
			break;
		}
	}
	if(found==0)
  //		cout<<"\tPackage not found";
   /*
       //	cout<<"\nThe Bookings are  : "<<endl;
       //	line(40,'-');
       //	details.read((char*)&c,sizeof(c));
       //	while(!details.eof())
 //	{
		cout<<endl;
		c.ticket();
		cout<<endl;
		line(40,'-');
		details.read((char*)&c,sizeof(c));
	}}
	else*/
		cout<<"\nEntered CHK number is invalid";
	details.close();
}

void customer_details()
{
	clrscr();
	fstream details;
	customer c;
	details.open("BOOKINGS.TXT",ios::in | ios::binary);
	cout<<"\nThe Bookings are  : "<<endl;
	line(40,'-');
	int k=0;
	details.read((char*)&c,sizeof(c));
	while(!details.eof())
	{
		k++;
		cout<<endl;
		c.ticket();
		cout<<endl;
		line(40,'-');
		details.read((char*)&c,sizeof(c));
		if(k==2)
		{
			getch();
			clrscr();
			k=0;
		}
	}
	details.close();
}


void delete_name()
{
	package t;
	int found=0;
	fstream file1, file2;
	file1.open("PACKAGES.TXT",ios::in | ios::binary);
	file2.open("temp.txt",ios::out | ios::trunc | ios::binary);
	char name[10];
	char ch;
	cout<<"\nEnter the name of the package	  :   ";
	cin>>name;
	file1.read((char*)&t,sizeof(t));
	while(!file1.eof())
	{
		if(strcmp(name,t.return_name())==0)
		{
			found=1;
			cout<<endl;
			//line(40,'-');
			t.display();
			cout<<endl;
			line(40,'-');
			cout<<"\nSure to delete the record?\n";
			cin>>ch;
			if(ch=='n')
				file2.write((char*)&t, sizeof(t));
			else
				cout<<"\n\n-------- RECORD DELETED --------";
		}
		else
			file2.write((char*)&t, sizeof(t));
		file1.read((char*)&t,sizeof(t));
	}
	if(found==0)
		cout<<"\nRecord not found";
	file1.close();
	file2.close();
	remove("PACKAGES.TXT");
	rename("Temp.txt","PACKAGES.TXT");
	cout<<"\nUpdated details:\n";
	file2.open("PACKAGES.TXT",ios::in|ios::binary);
	file2.read((char*)&t, sizeof(t));
	while(!file2.eof())
	{
		cout<<endl;
		//line(40,'-');
		t.display();
		cout<<endl;
		line(40,'-');
		file2.read((char*)&t, sizeof(t));
		cout<<endl;
	}

	file2.close();
}


void delete_serial()
{
	package t;
	int found=0;
	char ch;
	fstream file1, file2;
	file1.open("PACKAGES.TXT",ios::in | ios::binary);
	file2.open("temp.txt",ios::out | ios::trunc | ios::binary);
	int serial_no;
	cout<<"\nEnter the serial number of the package	  :  ";
	cin>>serial_no;
	file1.read((char*)&t,sizeof(t));
	while(!file1.eof())
	{
		if(serial_no==t.return_sno())
		{
			found=1;
			cout<<endl;
		//line(40,'-');
			t.display();
			cout<<endl;
			line(40,'-');
			cout<<"\nSure to delete the record?\n";
			cin>>ch;
			if(ch=='n')
				file2.write((char*)&t, sizeof(t));
			else
				cout<<"\n\n-------- RECORD DELETED --------";
		}
		else
			file2.write((char*)&t, sizeof(t));
		file1.read((char*)&t, sizeof(t));
	}
	file1.close();
	file2.close();
	if(found==0)
		cout<<"\nSerial number not found";
	remove("PACKAGES.TXT");
	rename("Temp.txt","PACKAGES.TXT");
	cout<<"\nUpdated details:\n";
	file2.open("PACKAGES.TXT",ios::in|ios::binary);
	file2.read((char*)&t, sizeof(t));
	while(!file2.eof())
	{
		cout<<endl;
		//line(40,'-');
		t.display();
		cout<<endl;
		line(40,'-');
		file2.read((char*)&t, sizeof(t));
		cout<<endl;
	}

	file2.close();
}

void del()
{

	clrscr();
	cout<<"*\tDELETE A RECORD\t*";
	int ans;
	do{
	cout<<"\nPress";
	cout<<"\n1.to delete by package name\n";
	cout<<"\n2.to delete by serial number\n";
	cout<<"\n3.Go to Main Menu\n\n";
	cout<<"Enter your choice : ";
	cin>>ans;
	switch(ans)
	{

		case 1:
			delete_name();
			break;

		case 2: delete_serial();
			break;

		case 3:
			break;

		default:
			cout<<"\n\nChoose valid option";
			break;
	}
	}while(ans<3);
}




void line(int n, char ch)
{
	for(int i=0; i<n; ++i)
		cout<<ch;
}

void login()
{
	int ch;
	/*
	char user_id[5], password[10];
	clrscr();
	cout<<"\n\nEnter user name	:   ";
	cin>>user_id[5];
	cout<<"\n\Enter Password	:   ";
	for(int i=0; ch!='\0'; i++)
	{
		ch=getch();
		cout<<"*";
	}
	//password[10];
	cout<<"*";
	//if(strcmp(user_id,"Tours")==0)
	//{
	  //	if(strcmp(password,"12345")==0)
	for(i=0; i<=7; ++i)

	if(user_id!="Tours" && ch!="123456")
	{
		cout<<"Wrong Password. Access Denied";
		//exit(0);
	}

	//}
	else*/
	{
	do
	{
		clrscr();
		cout<<"MAIN MENU\n";
		cout<<"1. Insert new packages"<<endl;
		cout<<"2. Search for packages"<<endl;
		cout<<"3. Delete a package"<<endl;
		cout<<"4. Display the packages"<<endl;
		cout<<"5. View Customer Details"<<endl;
		cout<<"6. exit"<<endl;
		cout<<"Enter your choice	:  ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				insert();
				break;
			case 2:
				search();
				break;
			case 3:
				del();
				break;
			case 4:
				display_packs();
				break;
			case 5:
				customer_details();
				break;
			case 6:
				exit(0);
				break;
			default:
				cout<<"Enter a valid digit\n";
		}
		getch();
	}while(ch!=5);}
}


int get_cno()
{
	fstream bookings;
	bookings.open("BOOKINGS.TXT", ios::in | ios::binary);
	int chk=0;
	package p;
	customer c;
	bookings.read((char*)&c,sizeof(c));
	while(!bookings.eof())
	{
		chk=c.return_chk();
		bookings.read((char*)&c, sizeof(c));
	}
	bookings.close();
	return chk;
}


void book_ticket()
{
	int s_no,found=0;
	float fare,net_fare=0;
	char ch;
	int chk=get_cno();
	customer c;
	package p;
	cout<<"\nEnter Serial Number of the package	: ";
	cin>>s_no;
	fstream search;
	search.open("PACKAGES.TXT", ios::in | ios::binary);
	search.read((char*)&p,sizeof(p));
	while(!search.eof())
	{
		if(s_no==p.return_sno())
		{
			found=1;
			cout<<endl;
			p.display();
			cout<<endl;
			line(40,'-');
			break;
		}
		search.read((char*)&p,sizeof(p));
	}
	search.close();
	if(found==0)
	{
		cout<<"\tPackage not found";
		return;
	}
	fstream bookings;
	bookings.open("BOOKINGS.TXT", ios::app|ios::binary);
	do
	{
		c.accept(++chk,p.return_name());
		cout<<"\n\nDo you want to confirm the above details? [Y/N]	:  ";
		cin>>ch;
		ch=toupper(ch);
		if(ch=='Y')
		{

			net_fare=p.return_price()*(c.no_memb()-c.no_child());
			net_fare+=p.return_price()*c.no_child()/2;
			c.setfare(net_fare);
			bookings.write((char*)&c,sizeof(c));
		}
		else
			cout<<"\n\nEnter again";
	}while(ch!='Y');
	bookings.close();

}

void cancel_ticket()
{
	clrscr();
	cout<<"*\tCANCEL A TICKET\t*";
	int chk;
	cout<<"\nEnter the 5 digit CHK number	: ";
	cin>>chk;
	int ans;
	char ch;
	customer c;
	int found=0;
	fstream file1, file2;
	file1.open("BOOKINGS.TXT",ios::in|ios::binary);
	file2.open("Temp2.txt",ios::out|ios::trunc|ios::binary);
	file1.read((char*)&c,sizeof(c));
	while(!file1.eof())
	{
		if(chk==c.return_chk())
		{
			found=1;
			cout<<endl;
			//line(40,'-');
			c.ticket();
			cout<<endl;
			line(40,'-');
			cout<<"\nSure to cancel the ticket?\n";
			cin>>ch;
			if(ch=='n')
				file2.write((char*)&c, sizeof(c));
			else
				cout<<"\n\n-------- TICKET CANCELLED --------";
		}
		else
			file2.write((char*)&c, sizeof(c));
		file1.read((char*)&c, sizeof(c));
	}
	file1.close();
	file2.close();
	if(found==0)
		cout<<"\nNumber already cancelled";

	remove("BOOKINGS.TXT");
	rename("Temp2.txt","BOOKINGS.TXT");
	cout<<"\nUpdated Booking:\n";
	file2.open("BOOKINGS.TXT",ios::in|ios::binary);
	file2.read((char*)&c, sizeof(c));
	while(!file2.eof())
	{
		cout<<endl;
		//line(40,'-');
		c.ticket();
		cout<<endl;
		line(40,'-');
		file2.read((char*)&c, sizeof(c));
		cout<<endl;
	}
	file2.close();
}

