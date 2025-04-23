/*
============================================================================
Name        : pbl1.cpp
Author      : Om
Subject     : Project Based Learning
Description : Mobile Data
============================================================================
*/

#include <iostream>

using namespace std;

class mobileuser {
    long int number;
    string name;
    float billamount;

	public:
		mobileuser() {
			number = 0;
			name = "";
			billamount = 0;
		}
    friend class record;
};

class record {
    mobileuser u[10];

	public:
		void accept(int n) {
			for (int i = 0; i < n; i++) {
				cout << "Enter Record " << i+1 << endl;
				cout << "Name: ";
				cin >> u[i].name;
				cout << "Mobile Number: ";
				cin >> u[i].number;
				cout << "Bill Amount: ";
				cin >> u[i].billamount;
				cout << endl;
			}
		}

		void display(int n) {
			cout << "Name \tNumber \tBillamount" << endl;
			for (int i = 0; i < n; i++) {
				cout << u[i].name << "\t" << u[i].number << "\t" << u[i].billamount << endl;
			}
		}

		void adjust(int n, int i) {
			while ((2 * i + 1) < n) {
				int j = 2 * i + 1;
				if (j + 1 < n && u[j + 1].billamount > u[j].billamount) {
					j = j + 1;
				}
				if (u[i].billamount >= u[j].billamount) {
					break;
				} else {
					mobileuser temp = u[j];
					u[j] = u[i];
					u[i] = temp;
					i = j;
				}
			}
		}

		void heapsort(int n) {
			for (int i = (n / 2) - 1; i >= 0; i--) {
				adjust(n, i);
			}
			for (int i = n - 1; i > 0; i--) {
				mobileuser temp = u[0];
				u[0] = u[i];
				u[i] = temp;
				adjust(i, 0);
			}
		}

		void quicksort_r(int low,int high){
			int q=0;
			if(low<high){
				q=partition(low,high);
				quicksort_r(low,q-1);
				quicksort_r(q+1,high);
			}
		}

		int partition(int low,int high){
			int i,j;
			long int x=u[high].number;
			mobileuser temp;
			 i=low-1;
			 j=high;
			while(1){
			while(u[i].number>=x && i<high)i++;
			while(u[j].number<=x && j>low)j--;
			if(i<j){
				   temp=u[i];
					u[i]=u[j];
					u[j]=temp;
					return i+1;
			}else{
				break;
			}
				}
				temp=u[low];
				u[low]=u[j];
				u[j]=temp;
				return j;
		}

		void linear_search(long int key, int n) {
			for (int i = 0; i < n; i++) {
				if (key == u[i].number) {
					cout << "Mobile No.: " << u[i].number << endl;
					cout << "Name: " << u[i].name << endl;
					cout << "Bill Amount: " << u[i].billamount << endl;

					return;
				}
			}
			cout << "Record not found!" << endl;
		}

		void binary_search_nr(long int key, int n) {
			int low = 0;
			int high = n - 1;
			while (low <= high) {
				int mid = (low+high) / 2;
				if (u[mid].number == key) {
					cout << "Mobile No.: " << u[mid].number << endl;
					cout << "Name: " << u[mid].name << endl;
					cout << "Bill Amount: " << u[mid].billamount << endl;

					return;
				}
				else if (key > u[mid].number) {
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
			}
			cout << "Record not found!" << endl;
		}

		int binary_search_r(int low, int high, long int key) {
			if (low <= high) {
				int mid = (low + high) / 2;
				if (u[mid].number == key) {
					cout << "Mobile No.: " << u[mid].number << endl;
					cout << "Name: " << u[mid].name << endl;
					cout << "Bill Amount: " << u[mid].billamount << endl;

					return mid;
				} else if (key < u[mid].number) {
					return binary_search_r(low, mid - 1, key);
				} else {
					return binary_search_r(mid + 1, high, key);
				}
			}
			cout << "Record not found!" << endl;
			return -1;
		}
};

int main() {
    int n;
    cout << "Enter Number of records: ";
    cin >> n;
    record v;
    int choice;
    cout << endl;

   do {
    cout << endl << "Enter the Function:\n"
    		"1. Enter a Record\n"
    		"2. Display all Records\n"
    		"3. Heap Sort\n"
    		"4. Linear Search\n"
    		"5. Non-Reursive Binary Search\n"
    		"6. Recursive Binary Search\n"
    		"7. Quick Sort\n"
    		"8. Exit\n"
    		"Choice:";
    cin >> choice;
    cout << endl;
    long int ser_key;

    switch (choice) {
        case 1:
            v.accept(n);
            break;

        case 2:
            v.display(n);
            break;

        case 3:
            cout << "Sorting records..." << endl;
            v.heapsort(n);
            v.display(n);  // Optional: Display sorted records after sorting
            break;

        case 4:
            cout << "Enter mobile number to search: ";
            cin >> ser_key;
            v.linear_search(ser_key, n);
            break;

        case 5:
            cout << "Enter mobile number to search: ";
            cin >> ser_key;
            v.binary_search_nr(ser_key, n);
            break;

        case 6:
        	cout << "Enter Mobile Number to search:";
        	cin >> ser_key;
        	v.binary_search_r(0,n,ser_key);
        	break;

        case 7:
              cout << "Sorting records..." << endl;
              v.quicksort_r(0,n);
              v.display(n);
              break;

        default:
            cout << "Enter a valid choice!" << endl;
            break;
    }
   } while (choice != 8);

   return 0;
}
