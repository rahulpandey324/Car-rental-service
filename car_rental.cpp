// made by:- Rahul Pandey
// class:- XII-D
//**Program to rent a car through the BigBoy Toyz franchise***

#include<iostream.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>

  class fleet
{
	char car_code[10];
	char car_name[20];
	char cust_name[25];
	char car_color[10];
	int rentpk;
	int fixed_rent;

		public:

	 void add()
	{
		cout<<"Enter the car name: ";
		gets(car_name);
		cout<<"Enter car code: ";
		gets(car_code);
		cout<<"Enter car color: ";
		gets(car_color);
		cout<<"Enter rent/km: ";
		cin>>rentpk;
		cout<<"Enter fixed rent: ";
		cin>>fixed_rent;
		cout<<car_name<<" has been added to our fleet !!";
	}

	 void display()
	{
		cout<<"\nCar name: "<<car_name;
		cout<<"\nCar code: "<<car_code;
		cout<<"\nCar color: "<<car_color;
		cout<<"\nRent/km: "<<rentpk;
		cout<<"\nFixed rent: "<<fixed_rent<<endl<<endl;
	}


	 char* return_code()
	{	return car_code;
	 }
	 char* return_car_name()
	{	return car_name;
	 }
	 long bill(long kms)
	{	return fixed_rent+(rentpk*kms);
	 }

	 void modify(int k)
	{	rentpk=k;
	 }
};

  //-----------------TO ADD CARS IN THE FLEET---------------

	 void add_newcar()
	{
		fleet obj;
		char ans;
		ofstream ofile("A.dat",ios::binary|ios::app);

		do
		{
			obj.add();
			ofile.write((char*)&obj,sizeof(obj));

			cout<<"\n\nDo you want to enter more cars?? (Y/N): ";
			cin>>ans;
		} while(ans=='y'||ans=='Y');
	  ofile.close();
	}

  //---------------------TO DISPLAY FLEET-------------------

	 void display_fleet()
  {
		fleet obj;
		ifstream ofile("A.dat",ios::binary);

		  while(ofile.read((char*)&obj,sizeof(obj)))
		  {
				obj.display();
		  }
		ofile.close();
  }

  //----------------------SEARCH A RECORD-------------------

	void search_record()
	{
		 fleet x;
		 fstream sfile("A.dat",ios::binary|ios::in|ios::out);
		 char ccode[10];

		 cout<<"Enter the car code to search= ";
		 gets(ccode);

		 while(sfile.read((char*)&x,sizeof(x)))
		 {
				if(*(x.return_code()) == *ccode)
				{
					x.display();
				 }
		  }
		  sfile.close();
	}
  //-----------------------TO RENT A CAR--------------------

  void renting_car()
  {
	  char cust_name[30];
	  char car_code[10];
	  long kms;

	  cout<<"Please enter your name: ";
	  gets(cust_name);

			  display_fleet();

	  cout<<"Enter the car code you want to rent: ";
	  gets(car_code);
	  cout<<"Enter the expected kms for rent: ";
	  cin>>kms;

	  fleet obj;
	  ifstream ofile("A.dat",ios::binary);

	  while(ofile.read((char*)&obj,sizeof(obj)))
	{
		 if(strcmpi(car_code,obj.return_code())==0)
		 { cout<<"----------------------------------"<<endl;
			cout<<"\t\tBILL"<<endl;
			cout<<"\t********************"<<endl;
			cout<<"\tCustomer's name: "<<cust_name<<endl;
			cout<<"----------------------------------"<<endl;

			obj.display();

			cout<<"\tTotal kilometer travelled: "<<kms<<" kms"<<endl;
			cout<<"\tRent of car: Rs "<<obj.bill(kms)<<endl;
			cout<<"----------------------------------"<<endl;
		 }

	}

		ofile.close();
  }

  //-----------------TO MODIFY RENT/Km OF A CAR--------------

  void rent_modify()
  {
		fleet obj; char code[5];
		cout<<"Enter car code: ";
		cin>>code;

		fstream ofile("A.dat",ios::binary|ios::in|ios::out);

		while(ofile.read((char*)&obj,sizeof(obj)))
		{

			if(strcmpi(code,obj.return_code())==0)
			{
				cout<<"\n~~~~~DETAILS~~~~~"<<endl;
				obj.display();
				cout<<"~~~~~~~~~~~~~~~~~";

				int k;
				cout<<endl;
				cout<<"Enter new rent/km: ";
				cin>>k;

				ofile.seekg(0,ios::cur);
				obj.modify(k);

				ofile.seekp(ofile.tellg() - sizeof(obj));
				ofile.write((char*)&obj,sizeof(obj));
				cout<<"New rent/km updated !!!!";

			 }
		}

		ofile.close();
  }


  //-------------------TO DELETE A CAR RECORD---------------

	void delete_car()
	{
		ifstream ifile("A.dat",ios::binary);

		ofstream ofile("temp.dat",ios::binary);

		fleet obj; char ccode[10];
		cout<<"Enter the car code of car to be deleted: ";
		cin>>ccode;

			while(ifile.read((char*)&obj,sizeof(obj)))
			{
					if(strcmpi(ccode,obj.return_code())!=0)
					{	ofile.write((char*)&obj,sizeof(obj));
						cout<<"Record deleted.....";
					 }
			}
		ifile.close();
		ofile.close();

		remove("A.dat");
		rename("temp.dat","A.dat");

	}

	//--------------------DELETE ALL RECORDS-----------------

	void delete_all()
	{
		ifstream pfile("A.dat",ios::binary);
		ofstream qfile("tem.dat",ios::binary);

		fleet obj;

		while(pfile.read((char*)&obj,sizeof(obj)))
		{
			 qfile.write((char*)&obj,sizeof(obj));
		}

		cout<<"/n all records are deleted...."<<endl;

		  pfile.close();
		  qfile.close();

		  remove("A.dat");
		}


	//-------------------TO CONTACT BIGBOY TOYZ--------------

	void contact()
  {
	cout<<"\n\t\t\t    We are BIGBOY TOYZ."<<endl;
	cout<<"\n1)We provide you with the best cars in the ";
	cout<<"world for renting purpose."<<endl;

	cout<<"\n2)Do contact us for any suggestions or any ";
	cout<<"feedback on 1800-123-6969 or mail us at bigboy@toyz.com"<<endl;

	cout<<"\n3)Address:15/A West Chanakyapuri,New delhi 110025"<<endl;
	cout<<"\n\nALL RIGHTS RESERVED. ";
	cout<<"A company brought to you by Pandey Inc."<<endl;
  }



void main()
{
  char optn='y';
	do
	{ cout<<"\t\t*******Renting through BIGBOY TOYZ********"   <<endl<<endl;
	  int choice;
	  cout<<"\t\t~~~~~~~~~~~~~~~~~~~OUR MENU~~~~~~~~~~~~~~~"   <<endl;
	  cout<<"\n\t\t     1. Rent a car!!\t8. Contact Us!!"<<endl;
	  cout<<"\n\t\t     2. Add a car record"<<endl;
	  cout<<"\n\t\t     3. Search a record"<<endl;
	  cout<<"\n\t\t     4. Delete a car record"<<endl;
	  cout<<"\n\t\t     5. Delete all records"<<endl;
	  cout<<"\n\t\t     6. Modify rent/km of a car"<<endl;
	  cout<<"\n\t\t     7. Display fleet"<<endl;
	  cout<<"\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  <<endl;
	  cout<<"_____________________________________________";
	  cout<<"\n\nEnter the choice(1-8): ";
	  cin>>choice;
	  cout<<endl;

	  cout<<"_____________________________________________"    <<endl;
	  switch(choice)
	  {
		 case 1:renting_car();
		 break;

		 case 2:add_newcar();
		 break;

		 case 3:search_record();
		 break;

		 case 4:delete_car();
		 break;

		 case 5:delete_all();
		 break;

		 case 6:rent_modify();
		 break;

		 case 7:display_fleet();
		 break;

		 case 8:contact();
		 break;

		 default: cout<<"Enter correct choice out of the given  one above!!";

		}
        cout<<endl;
		  cout<<"\nDo you want to continue to MAIN MENU..(y/n)? :";
		  cin>>optn;
		  cout<<endl;

	 }while(optn=='y'||optn=='Y');

		 cout<<endl;
		 cout<<"\t\t   THANKS....FOR USING OUR SERVICES !!!";
 }