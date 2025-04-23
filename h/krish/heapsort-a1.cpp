#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class records {
private:
    int mobile;
    string name;
    float amount;

public:
    records() : name(""), mobile(0), amount(0.0) {}

    records(int mobile, string name, float amount) {
        this->name = name;
        this->mobile = mobile;
        this->amount = amount;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Mobile: " << mobile << endl;
        cout << "Amount: " << amount << endl;
    }

    void accept() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter mobile: ";
        cin >> mobile;
        cout << "Enter amount: ";
        cin >> amount;
    }

    float getAmount() const {
        return amount;
    }

    int getMobile() const {
        return mobile;
    }
};

void adjust(vector<records> &customers, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && customers[left].getMobile() > customers[largest].getMobile()) {
        largest = left;
    }

    if (right < n && customers[right].getMobile() > customers[largest].getMobile()) {
        largest = right;
    }

    if (largest != i) {
        swap(customers[i], customers[largest]);
        adjust(customers, n, largest);
    }
}

void heapSort(vector<records> &customers, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        adjust(customers, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(customers[0], customers[i]);
        adjust(customers, i, 0);
    }
}

int linearSearch(const vector<records> &customers, int mobile) {
    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i].getMobile() == mobile) {
            return i;
        }
    }
    return -1;
} 

int Sequentialsearch(const vector<records> &customers, int mobile) {
    int pos , flag;
    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i].getMobile() == mobile) {
            pos = i;
            flag = 1;
            break;
        }
    }
    if (flag == 1){
        return pos;
    }
    else{
        return -1;
    }

}

int binarysearch_recur(const vector<records> &customers, int mobile, int low, int high) {
    if (low <= high) {
        int mid = (low + high) / 2;
        if (customers[mid].getMobile() == mobile) {
            return mid;
        } 
        else if (mobile < customers[mid].getMobile()) {
            return binarysearch_recur(customers, mobile, low, mid - 1);
        } 
        else {
            return binarysearch_recur(customers, mobile, mid + 1, high);
        }
    }
    return -1;
}

int partition(vector<records> &customers, int p, int r) {
    int x = customers[r].getMobile();
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (customers[j].getMobile() > x) {
            i++;
            swap(customers[i], customers[j]);
        }
    }
    swap(customers[i + 1], customers[r]);
    return i + 1;
}

void quicksort(vector<records> &customers, int p, int r) {
    if (p < r) {
        int q = partition(customers, p, r);
        quicksort(customers, p, q - 1);
        quicksort(customers, q + 1, r);
    }
}




int main() {
    int n;
    cout << "Enter the number of customers: ";
    cin >> n;

    vector<records> customer(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter records for customer " << i + 1 << ":" << endl;
        customer[i].accept();
    }

    int choice = 0 ;
    while (choice != 5){
        cout << "\nChoose an operation:" << endl;
        cout << "1. Heap Sort" << endl;
        cout << "2. Quick Sort" << endl;
        cout << "3. Linear Search by Mobile" << endl;
        cout << "4. Binary Search by Mobile" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                heapSort(customer, n);
                cout << "\nCustomers sorted by mobile using Heap Sort:" << endl;
                for (const auto &record : customer) {
                    record.display();
                    cout << endl;
                }
                break;

            case 2:
                quicksort(customer, 0, n - 1);
                cout << "\nCustomers sorted by mobile using Quick Sort:" << endl;
                for (const auto &record : customer) {
                    record.display();
                    cout << endl;
                }
                break;

            case 3: {
                int searchMobile;
                cout << "Enter the mobile number to search: ";
                cin >> searchMobile;
                int index = linearSearch(customer, searchMobile);
                if (index != -1) {
                    cout << "Record found:" << endl;
                    customer[index].display();
                } else {
                    cout << "Record not found with mobile: " << searchMobile << endl;
                }
                break;
            }

            case 4: {
                int searchMobile;
                cout << "Enter the mobile number to search: ";
                cin >> searchMobile;
                int index = binarysearch_recur(customer, searchMobile, 0, customer.size() - 1);
                if (index != -1) {
                    cout << "Record found:" << endl;
                    customer[index].display();
                } else {
                    cout << "Record not found with mobile: " << searchMobile << endl;
                }
                break;
            }

            case 5:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
    return 0;
}

