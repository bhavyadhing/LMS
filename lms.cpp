#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<iomanip>
#include<string>
#include<ios>
#include<fstream>
#include<cstdio> 

using namespace std;

class Book{
    char bNo[8];
    char bName[50];
    char aName[20];
public:
    void createBook(){
        cout << "\nNew Book Entry . . .\n";
        cout << "\nEnter Book Number : ";
        cin >> bNo;
        cout << "\nEnter Book Name : ";
        cin >> bName;
        cout << "\nEnter Author Name : ";
        cin >> aName;
        cout <<"\n\n\nBook Created . . ";
    }
    void showBook(){
        cout << "\nBook Number : " << bNo;
        cout << "\nBook Name : "; 
        cout << bName;
        cout << "\nAuthor Name : ";  
        cout << aName <<endl;
    }
    void modifyBook(){
        cout << "\nBook Number : " << bNo << endl;
        cout << "\nModify Book Name : "; 
        cin >> bName;
        cout << "\nModify Author Name : ";  
        cin >> aName;
    }
    char* returnBookNo(){
        return bNo;
    }
    void report(){
        cout << bNo << setw(30) << bName << setw(30) <<aName << endl;
    }
};


class Student{
    char admno[8];
    char name[20];
    char stbno[8];
    int token;
public:
    void createStudent(){
        cout << "\nNew Student Entry . . .\n";
        cout << "\nEnter Addmission Number : ";
        cin >> admno;
        cout << "\nEnter Student Name : ";
        cin >> name;
        token = 0;
        stbno[0] = '\0';
        cout <<"\n\n\nStudent Record Created . . ";
    }
    void showStudent(){
        cout << "\nAddmission Number : " << admno << endl;
        cout << "\nStudent Name : "; 
        cout << name;
        cout << "\nNumber of Books Issued";  
        if(token == 1){
            cout << "\nBook Number " << stbno << endl;
        }
        cout << endl;
    }
    void modifyStudent(){
        cout << "\nAddmission Number : " << admno;
        cout << "\nModify Student Name : "; 
        cin >> name;
    }
    char* returnAddNo(){
        return admno;
    }
    char* returnStudentBookNo(){
        return stbno;
    }
    int returnToken(){
        return token;
    }
    void addToken(){
        token = 1;
    }
    void resetToken(){
        token = 0;
    }
    void getStBookNo(char t[]){
        strcpy(stbno, t);
    }
    void report(){
        cout << admno << setw(30) << name << setw(30) << token << endl;
    }
};


void gotoxy(int x, int y)
{
    COORD c = {x, y};  
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


fstream fp, fp1;
Book bk;
Student st;


void writeBook(){
    char c;
    fp.open("book.txt", ios::out | ios::app);
    do{
        system("cls");
        bk.createBook();
        fp.write((const char*)&bk, sizeof(Book));
        cout << "\n\nTo Add More Record . . Press y Else n ";
        cin >> c;
    }while(c == 'y');
    fp.close();
}


void writeStudent(){
    char c;
    fp.open("student.txt", ios::out | ios::app);
    do{
        system("cls");
        st.createStudent();
        fp.write((const char*)&st, sizeof(Student));
        cout << "\n\nTo Add More Record . . Press y Else n ";
        cin >> c;
    }while(c == 'y');
    fp.close();
}


void displaySpecificBook(char n[]){
    system("cls");
    cout << "\nBook Details\n";
    int flag = 0;
    fp.open("book.txt", ios::in);
    while(fp.read((char*)&bk, sizeof(Book))){
        if(strcmp(bk.returnBookNo(), n) == 0){
            bk.showBook();
            flag = 1;
        }
    }
    fp.close();
    if(flag == 0){
        cout << "\n\nBook Does Not Exist";
    }
    getch();
}


void displaySpecificStudent(char n[]){
    system("cls");
    cout << "\nStudent Details\n";
    int flag = 0;
    fp.open("student.txt", ios::in);
    while(fp.read((char*)&st, sizeof(Student))){
        if(strcmp(st.returnAddNo(), n) == 0){
            st.showStudent();
            flag = 1;
        }
    }
    fp.close();
    if(flag == 0){
        cout << "\n\nStudent Does Not Exist";
    }
    getch();
}


void modifyBook(){
    char n[8];
    int found = 0;
    system("cls");
    cout << "\n\nModify Book Record . . .";
    cout << "\n\nEnter Book Number : ";
    cin >> n;
    fp.open("book.txt", ios::in | ios::out);
    while(fp.read((char *)&bk, sizeof(Book)) && found == 0){
        if(strcmp(bk.returnBookNo(), n) == 0){
            bk.showBook();
            cout << "\nEnter New Details . . . \n";
            bk.modifyBook();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((const char*)&bk, sizeof(Book));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if(found == 0){
        cout << "\n\nRecord Not Found";
    }
    getch();
}


void modifyStudent(){
    char n[8];
    int found = 0;
    system("cls");
    cout << "\n\nModify Student Record . . .\n";
    cout << "\n\nEnter Addmission Number : ";
    cin >> n;
    fp.open("student.txt", ios::in | ios::out);
    while(fp.read((char *)&st, sizeof(Student)) && found == 0){
        if(strcmp(st.returnAddNo(), n) == 0){
            st.showStudent();
            cout << "\nEnter New Details . . .";
            st.modifyStudent();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((const char*)&st, sizeof(Student));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if(found == 0){
        cout << "\n\nRecord Not Found";
    }
    getch();
}


void deleteBook(){
    char n[8];
    int flag = 0;
    system("cls");
    cout << "\n\nDelete Book . . .";
    cout << "\n\nEnter Book Number : ";
    cin >> n;
    fp.open("book.txt", ios::in | ios:: out);
    fstream fp2;
    fp2.open("temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while(fp.read((char * )&bk, sizeof(Book))){
        if(strcmp(bk.returnBookNo(), n) == 0){
            flag = 1;
        }
        else{
            fp2.write((const char *)&bk, sizeof(Book));
        }
    }
    fp2.close();
    fp.close();
    remove("book.txt");
    rename("temp.txt","book.txt");
    if(flag == 1){
        cout << "\n\n\tRecord Deleted";
    }
    else{
        cout <<"\n\n\tRecord Not Found";
    }
    getch();
}


void deleteStudent(){
    char n[8];
    int flag = 0;
    system("cls");
    cout << "\n\nDelete Student . . .";
    cout << "\n\nEnter Addmission Number : ";
    cin >> n;
    fp.open("student.txt", ios::in | ios:: out);
    fstream fp2;
    fp2.open("temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while(fp.read((char * )&st, sizeof(Student))){
        if(strcmp(st.returnAddNo(), n) == 0){
            flag = 1;
        }
        else{
            fp2.write((const char *)&st, sizeof(Student));
        }
    }
    fp2.close();
    fp.close();
    remove("student.txt");
    rename("temp.txt","student.txt");
    if(flag == 1){
        cout << "\n\n\tRecord Deleted";
    }
    else{
        cout <<"\n\n\tRecord Not Found";
    }
    getch();
}


void displayAllBooks(){
    system("cls");
    cout << "\nBook Details\n";
    cout << "================================================================\n";
    cout << "Book No                 Book Name                   Book Author\n";
    cout << "================================================================\n";
    fp.open("book.txt", ios::in);
    while(fp.read((char*)&bk, sizeof(Book))){
            bk.report();
    }
    fp.close();
    getch();    
}


void displayAllStudents(){
    system("cls");
    cout << "\nStudent Details\n";
    cout << "================================================================\n";
    cout << "Add NO                Student Name                   Book Issued\n";
    cout << "================================================================\n";

    fp.open("student.txt", ios::in);
    while(fp.read((char*)&st, sizeof(Student))){
            st.report();
    }
    fp.close();
    getch();    

}


void bookIssue(){
	char sn[8],bn[8];
	int found=0,flag=0;
	system("cls");
	cout<<"\n\nBOOK ISSUE...";
	cout<<"\n\n\tEnter Admission no.";
	cin>>sn;
	fp.open("student.txt",ios::in|ios::out);
	fp1.open("book.txt",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(Student))&& found==0){
		if(strcmpi(st.returnAddNo(),sn)==0){//compare admsn no.
			found=1;
			if(st.returnToken()==0){//if book not issued
			    cout<<"\n\n\tEnter The Book No.";
			    cin>>bn;
			    while(fp1.read((char*)&bk,sizeof(Book))&& flag==0){
				    if(strcmpi(bk.returnBookNo(),bn)==0){//compare book no.
			            flag=1;
                        st.addToken();
                        st.getStBookNo(bk.returnBookNo());//pass book no.
                        int pos=-1*sizeof(st);
                        fp.seekg(pos,ios::cur);
                        fp.write((char*)&st,sizeof(Student));
                        cout<<"\n\n\tBook Issued Successfully\n\n Please Note The Book Issue Date On Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 15 Rs Per Day";
		            }
		        }
		        if(flag==0){
			        cout<<"Book No. Does Not Exists";
		        }
	        } 
            else{
                cout<<"You Have Not Returned The Last Book";
            }
	    }
    }
    if(found==0){
        cout<<"Student Record Not Exists...";   
    }
    getch();
    fp.close();
    fp1.close();
}


void bookDeposit(){
	char sn[8],bn[8];
	int found=0,flag=0,day,fine;
	system("cls");
	cout<<"\n\nBOOK DEPOSIT...";
	cout<<"\n\n\tEnter Admission no. Of Student";
	cin>>sn;
	fp.open("student.txt",ios::in|ios::out);
	fp1.open("book.txt",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(Student))&& found==0){
		if(strcmpi(st.returnAddNo(),sn)==0){//compare admsn no.
			found=1;
			if(st.returnToken()==1){//if book issued
				while(fp1.read((char*)&bk,sizeof(Book))&& flag==0){
				    if(strcmpi(bk.returnBookNo(),st.returnStudentBookNo())==0){
			            flag=1;
					    bk.showBook();
					    cout<<"\n\n Book Deposited In No. Of Days";
					    cin>>day;
					    if(day>15){
				    	    fine=(day-15)*1;
				    	    cout<<"\n\n Fine = "<<fine;
					    }
					    st.resetToken();
    
					    int pos=-1*sizeof(st);
					    fp.seekg(pos,ios::cur);
					    fp.write((char*)&st,sizeof(Student));
					    cout<<"\n\n\tBook Deposited Successfully";		
		            }
		        }
                if(flag==0){
                    cout<<"Book No. Does Not Exists";
                }
	        } 
            else{
                cout<<"No Book Issued"; 
            }
	    }
    }
    if(found==0){
        cout<<"Student Record Not Exists...";
    }
    getch();
    fp.close();
    fp1.close();
 }


void start(){
    system("cls");
    gotoxy(35,11);
    cout << "Library" ;
    gotoxy(35,14);
    cout << "Management" ;
    gotoxy(35,17);
    cout << "System" ;
    cout << "\n\nDeveloper : Bhavya Dhing";
    getch();
}


void adminMenu(){
    
    int b;
    do{
        system("cls");
        cout << "\n\n\n\tAdministrator Menu";
        cout << "\n\n\t1. Create Student Record";
        cout << "\n\n\t2. Display All Student Records";
        cout << "\n\n\t3. Display Specific Student Record";
        cout << "\n\n\t4. Modify Student Record";
        cout << "\n\n\t5. Delete Student Record";
        cout << "\n\n\t6. Create Book";
        cout << "\n\n\t7. Display All Books";
        cout << "\n\n\t8. Display Specific Book";
        cout << "\n\n\t9. Modify Book Record";
        cout << "\n\n\t10. Delete Book Record";
        cout << "\n\n\t11. Back to Main Menu";
        cout << "\n\n\tPlease Select From 1 to 11 : ";
        
        cin >> b;
    
        if(b == 1){
            writeStudent();
        }
        else if(b == 2){
            displayAllStudents();
        }
        else if(b == 3){
            system("cls");
            char admn[8];
            cout << "\n\n\tEnter Addmission Number : ";
            cin >>  admn;
            displaySpecificStudent(admn);
        }
        else if(b == 4){
            modifyStudent();
        }
        else if(b == 5){
            deleteStudent();
        }
        else if(b == 6){
            writeBook();
        }
        else if(b == 7){
            displayAllBooks();
        }
        else if(b == 8){
            system("cls");
            char bno[8];
            cout << "\n\n\tEnter Book Number : ";
            cin >>  bno;
            displaySpecificBook(bno);
        }
        else if(b == 9){
            modifyBook();
        }
        else if(b == 10){
            deleteBook();
        }
        else if(b == 11){
            return;
        }
        else{
            cout << "Invalid Input, Try Again";
        }
    }while(b != 11);
}


int main(){
    int a;
    start();
    do{
        system("cls");
        cout << "\n\n\n\tMain Menu";
        cout << "\n\n\t1. Book Issue";
        cout << "\n\n\t2. Book Deposit";
        cout << "\n\n\t3. Administator Menu";
        cout << "\n\n\t4. Exit";
        cout << "\n\n\tPlease Select From 1, 2, 3 or 4 : ";
        
        cin >> a;

        if(a == 1){
            bookIssue();

        } 
        else if(a == 2){
            bookDeposit();
            
        }
        else if(a == 3){
            adminMenu();
        }
        else if(a == 4){
            exit(0);
        }
        else{
            cout << "Invalid Input, Try Again";
        }
    }while(a != 4);
    return 0;
}
