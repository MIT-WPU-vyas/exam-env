#include <iostream>
#include <string.h>

using namespace std;

class User {
private: 
    char name[50]; 
    long int MobileNumber;
    float BillAmount;

    static void Adjust(User arr[], int n, int i) {
        while (2*i + 1 <= n) {
            int j = 2 * i + 1;
            if (j + 1 <= n && arr[j + 1].BillAmount > arr[j].BillAmount) {
                j = j + 1;
            }
            if (arr[i].BillAmount >= arr[j].BillAmount) {
                break;
            } else {
                User temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i = j;
            }
        }
    }

public:
    User() {
        strcpy(name, "");
        MobileNumber = 0;
        BillAmount = 0.0;
    }

    void acceptData() {
        cout << "Enter the name: ";
        cin >> name;
        cout << "Enter the Mobile Number: ";
        cin >> MobileNumber;
        cout << "Enter the Bill Amount: ";
        cin >> BillAmount;
    }

    void displayData() const {
        cout << "\n Name: " << name;
        cout << "\n Mobile Number: " << MobileNumber;
        cout << "\n Bill Amount: " << BillAmount;
        cout << "\n ------------------\n";
    }

    float getBillAmount() const {
        return BillAmount;
    }

    friend void HeapSort(User arr[], int n);
    friend void LinearSearch(User arr[], float target, int size);
    friend int partition(User arr[], int p, int r);
    friend void QuickSort(User arr[], int p, int r);
};

void HeapSort(User arr[], int n) {
    for (int i = (n/2) - 1; i >= 0; i--) {
        User::Adjust(arr, n-1, i);
    }

    while (n > 0) {
        User t = arr[0];
        arr[0] = arr[n-1];
        arr[n-1] = t;
        n--;
        User::Adjust(arr, n-1, 0);
    }
}

int partition(User arr[], int p, int r) {
    float pivot = arr[r].getBillAmount();
    int i = p - 1;
    
    for (int j = p; j < r; j++) {
        if (arr[j].getBillAmount() >= pivot) {
            i++;
            User temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    User temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;
    return i + 1;
}

void QuickSort(User arr[], int p, int r) {
    if (p < r) {
        int pi = partition(arr, p, r);
        QuickSort(arr, p, pi - 1);
        QuickSort(arr, pi + 1, r);
    }
}

void LinearSearch(User arr[], float target, int size) {
    bool found = false;
    for(int i = 0; i < size; i++) {
        if(arr[i].getBillAmount() == target) {
            cout << "Record Found at position: " << i + 1 << ":" << endl;
            arr[i].displayData();
            found = true;
        }
    }
    if(!found) {
        cout << "Target Not found: " << target << endl;
    }
}

int sequential_search(User arr[], float key, int size) {
    for (int i = 0; i < size; i++) {
        if(key == arr[i].getBillAmount()){
            return i;
        }
    }
    return -1;
}

int binary_search(User arr[], int low, int high, float key) {
    if(low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[mid].getBillAmount() == key) {
            return mid;
        }
        else if (key < arr[mid].getBillAmount()) {
            return binary_search(arr, low, mid-1, key);
        }
        else {
            return binary_search(arr, mid+1, high, key);
        }
    }
    return -1;
}


int main() {
    int n;
    cout << "Enter the number of Users: ";
    cin >> n;
    
    User* Users = new User[n];
    
    cout << "\nEnter User details:\n";
    for(int i = 0; i < n; i++) {
        cout << "\nUser " << i+1 << ":\n";
        Users[i].acceptData();
    }

    int choice;
    float searchAmount;
    int pos;

    do {
        cout << "\n\nMenu:";
        cout << "\n1. Display all records";
        cout << "\n2. Sort using HeapSort";
        cout << "\n3. Sort using QuickSort";
        cout << "\n4. Linear Search";
        cout << "\n5. Sequential Search";
        cout << "\n6. Binary Search";
        cout << "\n7. Exit";
        cout << "\nEnter your choice (1-7): ";
        
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "\nUser Records:";
                for(int i = 0; i < n; i++) {
                    Users[i].displayData();
                }
                break;

            case 2:
                HeapSort(Users, n);
                cout << "\nRecords sorted using HeapSort:";
                for(int i = 0; i < n; i++) {
                    Users[i].displayData();
                }
                break;

            case 3:
                QuickSort(Users, 0, n-1);
                cout << "\nRecords sorted using QuickSort:";
                for(int i = 0; i < n; i++) {
                    Users[i].displayData();
                }
                break;

            case 4:
                cout << "\nEnter bill amount to search: ";
                cin >> searchAmount;
                LinearSearch(Users, searchAmount, n);
                break;

            case 5:
                cout << "\nEnter bill amount to search: ";
                cin >> searchAmount;
                pos = sequential_search(Users, searchAmount, n);
                if(pos != -1) {
                    cout << "Record found at position: " << pos + 1 << endl;
                    Users[pos].displayData();
                } else {
                    cout << "Record not found!" << endl;
                }
                break;

            case 6:
                cout << "\nEnter bill amount to search: ";
                cin >> searchAmount;
                pos = binary_search(Users, 0, n-1, searchAmount);
                if(pos != -1) {
                    cout << "Record found at position: " << pos + 1 << endl;
                    Users[pos].displayData();
                } else {
                    cout << "Record not found!" << endl;
                }
                break;

            case 7:
                cout << "Byeeeeeeee";
                break;

            default:
                cout << "\n Enter a choice which is valid.";
        }
    } while(choice != 7);

    return 0;
}
