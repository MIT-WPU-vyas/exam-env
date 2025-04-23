#include <iostream>
#include<fstream>
#include <string>

using namespace std;

class record {
    int rollno, marks;
    char name[20];
    friend class student;
};

class hashing {
    int rollno, pos;
	public:
		hashing() {
			rollno = -1;
			pos = -1;
		}
		friend class student;
};

class student {
    record rec;
    hashing h[10];
    int s, relt;

public:
    student();
    void create_wr();
    void displayall();
    void display_hash_table();
    void create_wor();
};

int main(){
    student s;
    int n;
    do{
		cout<< endl << "Enter the function to perform:"<<endl
				<< "1. Write records(wr)" << endl
				<< "2. Write records(wor)" << endl
				<< "3. Display records" << endl
				<< "4. Hash Table" << endl
				<< "5. Exit" << endl
				<< "Choice: ";
		cin>>n;

		switch(n){
			case 1:
				cout<<"Writing records"<<endl;
				s.create_wr();

				break;

			case 2:
				cout<<"Writing records (wor)\n";
				s.create_wor();
				break;
			case 3:

				cout<<"Displaying records \n";
				s.displayall();
				break;
			case 4:
				cout<<"Hash Table \n";
				s.display_hash_table();
				break;

			case 5:
				cout << endl << "Exiting...";
				break;

			default:
				cout<<"Invalid choice!\n";

		}
    }while(n != 5);
    return 0;
}

student::student() {
    s = sizeof(record);
    for(int i = 0; i < 10; i++) {
        h[i].rollno = -1;
        h[i].pos = -1;
    }
    relt = 0;
}

void student::create_wr() {
    char ans;
    int nloc;
    hashing temp;
    fstream f;

    f.open("student.txt");

    int loc;
    do {
        cout << "\nEnter the details:\n";
        cout << "Roll no.: ";
        cin >> rec.rollno;
        cout << "Name: ";
        cin >> rec.name;
        cout << "Marks: ";
        cin >> rec.marks;

        loc = rec.rollno % 10;
        if (h[loc].rollno == -1) {
            h[loc].rollno = rec.rollno;
            h[loc].pos = relt;
            f.write((char*)&rec, s);
            relt++;
        } else {
            temp.rollno = rec.rollno;
            temp.pos = relt;
            f.write((char*)&rec, s);
            relt++;
            if (loc != (h[loc].rollno % 10)) {
                temp.rollno = h[loc].rollno;
                temp.pos = h[loc].pos;
                h[loc].rollno = rec.rollno;
                h[loc].pos = relt - 1;
            }
            nloc = (loc + 1) % 10;
            while (nloc != loc) {
                if (h[nloc].rollno == -1) {
                    h[nloc].rollno = temp.rollno;
                    h[nloc].pos = temp.pos;
                    relt++;
                    break;
                }
                nloc = (nloc + 1) % 10;
            }
        }

        cout << "\nDo you want to add next student record? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    f.close();
}

void student::create_wor() {
    char ans;
    fstream f;

    f.open("student.txt");

    int loc;
    do {
        cout << "\nEnter the details:\n";
        cout << "Roll no.: ";
        cin >> rec.rollno;
        cout << "Name: ";
        cin >> rec.name;
        cout << "Marks: ";
        cin >> rec.marks;

        loc = rec.rollno % 10;
        while (h[loc].rollno != -1) {
            loc = (loc + 1) % 10;
        }
        h[loc].rollno = rec.rollno;
        h[loc].pos = relt;
        f.write((char*)&rec, s);
        relt++;

        cout << "\nDo you want to add next student record? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    f.close();
}


void student::displayall() {
    fstream f;
    record rec;  // Declare an object to read records

    f.open("student.txt", ios::in);  // Open in input mode
    if (!f) {
        cout << "Error opening file!\n";
        return;
    }

    cout << "\nAll Student Records:\n";

    while (f >> rec.rollno >> rec.name >> rec.marks) {  // Read data properly
        cout << "\nRoll No.: " << rec.rollno << "\n";
        cout << "Name: " << rec.name << "\n";
        cout << "Marks: " << rec.marks << "\n";
    }

    f.close();
}


void student::display_hash_table() {
    cout << endl << "Hash Table:" << endl;;
    cout << "Index \t Roll No. \t Position" << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << " \t " << h[i].rollno << " \t \t " << h[i].pos <<endl;
    }
}
