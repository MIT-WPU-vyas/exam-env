#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std;

class record
{
    int rollno, marks;
    char name[20];
    friend class student;
};

class hashing
{
    int rollno, pos;
    public: hashing()
    {
        rollno=-1;
        pos=-1;
    }
    friend class student;
};

class student
{
    record rec;
    hashing h[10];
    
    int s, relt;
    public: student()
    {
        s=sizeof(record);
        for(int i=0; i<10; i++)
        {
            h[i].rollno=-1;
            h[i].pos=-1;
        }
        relt=0;
    }
    
    void create_wor();
    void create_wr();
    void modify();
    void retrieve();
    void display();
    void displayall();
    void deleteRecord();
};

void student::create_wor()
{
    char ans;
    fstream f;
    f.open("student.txt", ios::binary|ios::in);
    
    do
    {
        cout<<"\nEnter the details : \n";
        cout<<"Roll no.: ";
        cin>>rec.rollno;
        cout<<"Name \t: ";
        cin>>rec.name;
        cout<<"Marks \t: ";
        cin>>rec.marks;
        
        int loc=rec.rollno%10;
        
        if(h[loc].rollno==-1)
        {
            h[loc].rollno=rec.rollno;
            h[loc].pos=relt;
            f.write((char*)&rec, s);
            relt=relt+1;
        }
        else
        {
            int nloc=(loc+1)%10;
            while(nloc!=loc)
            {
                if(h[nloc].rollno==-1)
                {
                    h[nloc].rollno=rec.rollno;
                    h[nloc].pos=relt;
                    f.write((char*)&rec, s);
                    relt=relt+1;
                    break;
                }
                nloc=(nloc+1)%10;
            }
            if(nloc==loc)
            {
                cout<<"\nHash table is full!";
                break;
            }
        }
        
        cout<<"\nDo you want to add next student record?(y/n) : ";
        cin>>ans;
    }while(ans=='y'||ans=='Y');
    
    f.close();
}

void student::create_wr()
{
    char ans;
    hashing temp;
    fstream f;
    f.open("student.txt", ios::binary|ios::out);
    
    do
    {
        cout<<"\nEnter the details : \n";
        cout<<"Roll no.: ";
        cin>>rec.rollno;
        cout<<"Name \t: ";
        cin>>rec.name;
        cout<<"Marks \t: ";
        cin>>rec.marks;
        
        int loc=rec.rollno%10;
        
        if(h[loc].rollno==-1)
        {
            h[loc].rollno=rec.rollno;
            h[loc].pos=relt;
            f.write((char*)&rec, s);
            relt=relt+1;
        }
        else
        {
            if(loc!=(h[loc].rollno%10))
            {
                temp.rollno=h[loc].rollno;
                temp.pos=h[loc].pos;
                h[loc].rollno=rec.rollno;
                h[loc].pos=relt;
                f.write((char*)&rec, s);
                relt=relt+1;
                
                int nloc=(loc+1)%10;
                while(nloc!=loc)
                {
                    if(h[nloc].rollno==-1)
                    {
                        h[nloc].rollno=temp.rollno;
                        h[nloc].pos=temp.pos;
                        break;
                    }
                    nloc=(nloc+1)%10;
                }
                if(nloc==loc)
                {
                    cout<<"\nHash table is full!";
                    break;
                }
            }
            else
            {
                int nloc=(loc+1)%10;
                while(nloc!=loc)
                {
                    if(h[nloc].rollno==-1)
                    {
                        h[nloc].rollno=rec.rollno;
                        h[nloc].pos=relt;
                        f.write((char*)&rec, s);
                        relt=relt+1;
                        break;
                    }
                    nloc=(nloc+1)%10;
                }
                if(nloc==loc)
                {
                    cout<<"\nHash table is full!";
                    break;
                }
            }
        }
        
        cout<<"\nDo you want to add next student record?(y/n) : ";
        cin>>ans;
    }while(ans=='y'||ans=='Y');
    
    f.close();
}

// Retrieve (Search) a record
void student::retrieve()
{
    int key, i, found=0;
    cout<<"\nEnter roll number to search: ";
    cin>>key;
    
    int loc=key%10;
    if(h[loc].rollno==key)
    {
        fstream f;
        f.open("student.txt", ios::binary|ios::in);
        f.seekg(h[loc].pos*s, ios::beg);
        f.read((char*)&rec, s);
        cout<<"\nRecord found!";
        cout<<"\nRoll No: "<<rec.rollno;
        cout<<"\nName: "<<rec.name;
        cout<<"\nMarks: "<<rec.marks;
        f.close();
        found=1;
    }
    else
    {
        i=(loc+1)%10;
        while(i!=loc)
        {
            if(h[i].rollno==key)
            {
                fstream f;
                f.open("student.txt", ios::binary|ios::in);
                f.seekg(h[i].pos*s, ios::beg);
                f.read((char*)&rec, s);
                cout<<"\nRecord found!";
                cout<<"\nRoll No: "<<rec.rollno;
                cout<<"\nName: "<<rec.name;
                cout<<"\nMarks: "<<rec.marks;
                f.close();
                found=1;
                break;
            }
            i=(i+1)%10;
        }
    }
    
    if(found==0)
        cout<<"\nRecord not found!";
}

void student::modify()
{
    int key, i, found=0;
    cout<<"\nEnter roll number to modify: ";
    cin>>key;
    
    int loc=key%10;
    if(h[loc].rollno==key)
    {
        fstream f;
        f.open("student.txt", ios::binary|ios::in|ios::out);
        f.seekg(h[loc].pos*s, ios::beg);
        f.read((char*)&rec, s);
        
        cout<<"\nCurrent Record:";
        cout<<"\nRoll No: "<<rec.rollno;
        cout<<"\nName: "<<rec.name;
        cout<<"\nMarks: "<<rec.marks;
        
        cout<<"\n\nEnter new details:";
        cout<<"\nName: ";
        cin>>rec.name;
        cout<<"Marks: ";
        cin>>rec.marks;
        
        f.seekp(h[loc].pos*s, ios::beg);
        f.write((char*)&rec, s);
        f.close();
        
        cout<<"\nRecord modified successfully!";
        found=1;
    }
    else
    {
        i=(loc+1)%10;
        while(i!=loc)
        {
            if(h[i].rollno==key)
            {
                fstream f;
                f.open("student.txt", ios::binary|ios::in|ios::out);
                f.seekg(h[i].pos*s, ios::beg);
                f.read((char*)&rec, s);
                
                cout<<"\nCurrent Record:";
                cout<<"\nRoll No: "<<rec.rollno;
                cout<<"\nName: "<<rec.name;
                cout<<"\nMarks: "<<rec.marks;
                
                cout<<"\n\nEnter new details:";
                cout<<"\nName: ";
                cin>>rec.name;
                cout<<"Marks: ";
                cin>>rec.marks;
                
                f.seekp(h[i].pos*s, ios::beg);
                f.write((char*)&rec, s);
                f.close();
                
                cout<<"\nRecord modified successfully!";
                found=1;
                break;
            }
            i=(i+1)%10;
        }
    }
    
    if(found==0)
        cout<<"\nRecord not found!";
}

void student::display()
{
    int key, i, found=0;
    cout<<"\nEnter roll number to display: ";
    cin>>key;
    
    int loc=key%10;
    if(h[loc].rollno==key)
    {
        fstream f;
        f.open("student.txt", ios::binary|ios::in);
        f.seekg(h[loc].pos*s, ios::beg);
        f.read((char*)&rec, s);
        cout<<"\nRoll No: "<<rec.rollno;
        cout<<"\nName: "<<rec.name;
        cout<<"\nMarks: "<<rec.marks;
        f.close();
        found=1;
    }
    else
    {
        i=(loc+1)%10;
        while(i!=loc)
        {
            if(h[i].rollno==key)
            {
                fstream f;
                f.open("student.txt", ios::binary|ios::in);
                f.seekg(h[i].pos*s, ios::beg);
                f.read((char*)&rec, s);
                cout<<"\nRoll No: "<<rec.rollno;
                cout<<"\nName: "<<rec.name;
                cout<<"\nMarks: "<<rec.marks;
                f.close();
                found=1;
                break;
            }
            i=(i+1)%10;
        }
    }
    
    if(found==0)
        cout<<"\nRecord not found!";
}

void student::displayall()
{
    fstream f;
    f.open("student.txt", ios::binary|ios::in);
    
    cout<<"\n----- Hash Table -----";
    cout<<"\nIndex\tRoll No\tPosition";
    for(int i=0; i<10; i++)
    {
        cout<<"\n"<<i<<"\t"<<h[i].rollno<<"\t"<<h[i].pos;
    }
    
    cout<<"\n\n----- Student Records -----";
    cout<<"\nRoll No\tName\t\tMarks";
    
    for(int i=0; i<relt; i++)
    {
        f.seekg(i*s, ios::beg);
        f.read((char*)&rec, s);
        cout<<"\n"<<rec.rollno<<"\t"<<rec.name;
        if(strlen(rec.name)<8)
            cout<<"\t";
        cout<<"\t"<<rec.marks;
    }
    
    f.close();
}

void student::deleteRecord()
{
    int key, i, found=0;
    cout<<"\nEnter roll number to delete: ";
    cin>>key;
    
    int loc=key%10;
    if(h[loc].rollno==key)
    {
        h[loc].rollno=-1;
        h[loc].pos=-1;
        cout<<"\nRecord deleted successfully!";
        found=1;
    }
    else
    {
        i=(loc+1)%10;
        while(i!=loc)
        {
            if(h[i].rollno==key)
            {
                h[i].rollno=-1;
                h[i].pos=-1;
                cout<<"\nRecord deleted successfully!";
                found=1;
                break;
            }
            i=(i+1)%10;
        }
    }
    
    if(found==0)
        cout<<"\nRecord not found!";
    
}

int main()
{
    student s;
    int choice, method;
    
    cout<<"\n----- Student Database using Hashing -----\n";
    cout<<"\nChoose hashing method:";
    cout<<"\n1. Linear Probing without Replacement";
    cout<<"\n2. Linear Probing with Replacement";
    cout<<"\nEnter your choice: ";
    cin>>method;
    
    if(method == 1)
        s.create_wor();
    else if(method == 2)
        s.create_wr();
    else
    {
        cout<<"\nInvalid choice!";
        return 0;
    }
    
    do
    {
        cout<<"\n\n----- MENU -----";
        cout<<"\n1. Display All Records";
        cout<<"\n2. Search a Record";
        cout<<"\n3. Modify a Record";
        cout<<"\n4. Display a Record";
        cout<<"\n5. Delete a Record";
        cout<<"\n6. Exit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        
        switch(choice)
        {
            case 1:
                s.displayall();
                break;
            case 2:
                s.retrieve();
                break;
            case 3:
                s.modify();
                break;
            case 4:
                s.display();
                break;
            case 5:
                s.deleteRecord();
                break;
            case 6:
                cout<<"\nThank you for using Student Database!";
                break;
            default:
                cout<<"\nInvalid choice!";
        }
    }while(choice!=6);
    
    return 0;
}


//O(1) best 
//O(n) worst
