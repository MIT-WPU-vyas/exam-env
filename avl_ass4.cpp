#include <iostream>
#include <string>
using namespace std;

class avl_node {
    string word, meaning;
    avl_node *left, *right;
public:
    friend class avlTree;
};

class avlTree {
public:
    avl_node *root;
    int height(avl_node *);
    int diff(avl_node *);
    avl_node *rr_rotation(avl_node *);
    avl_node *ll_rotation(avl_node *);
    avl_node *lr_rotation(avl_node *);
    avl_node *rl_rotation(avl_node *);
    avl_node* balance(avl_node *);
    void insert();
    avl_node* insert(avl_node *, avl_node *);
    void display(avl_node *, int);
    void inorder(avl_node *);
    void preorder(avl_node *);
    void postorder(avl_node *);
    avlTree() {
        root = NULL;
    }
};

int avlTree::height(avl_node *temp) {
    int h = 0;
    if (temp != NULL) {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

int avlTree::diff(avl_node *temp) {
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int b_factor = l_height - r_height;
    return b_factor;
}

avl_node *avlTree::rr_rotation(avl_node *parent) {
    avl_node *temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avl_node *avlTree::ll_rotation(avl_node *parent) {
    avl_node *temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

avl_node *avlTree::lr_rotation(avl_node *parent) {
    avl_node *temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}

avl_node *avlTree::rl_rotation(avl_node *parent) {
    avl_node *temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}

avl_node *avlTree::balance(avl_node *temp) {
    int bal_factor = diff(temp);
    
    if (bal_factor > 1) {
        if (diff(temp->left) > 0){
            temp = ll_rotation(temp);
            cout << "\n Performed LL rotation:" << endl;
        }
        else{
            temp = lr_rotation(temp);
            cout << "\n Performed LR rotation:" << endl;
        }
    }
    else if (bal_factor < -1) {
        if (diff(temp->right) > 0){
            temp = rl_rotation(temp);
            cout << "\n Performed RL rotation:" << endl;
        }
        else{
            temp = rr_rotation(temp);
            cout << "\n Performed RR rotation:" << endl;
        }
    }
    return temp;
}

void avlTree::insert() {
    char ch;
    do {
        avl_node *temp = new avl_node;
        cout << "Enter word and its meaning: ";
        cin >> temp->word >> temp->meaning;
        temp->left = NULL;
        temp->right = NULL;
        
        root = insert(root, temp);
        
        cout << "Do you want to add another word? (Y/N): ";
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');
}

avl_node* avlTree::insert(avl_node *root, avl_node *temp) {
    if (root == NULL) {
        root = temp;
        return root;
    }
    else if (temp->word < root->word) {
        root->left = insert(root->left, temp);
        root = balance(root);
    }
    else if (temp->word >= root->word) {
        root->right = insert(root->right, temp);
        root = balance(root);
    }
    cout << "The updated Tree is \n";
    display(this->root, 1);
    return root;
}


void avlTree:: display(avl_node *ptr, int level = 1){
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        cout << endl;
        if (ptr == root)
            cout<<"Root -> ";
        for (int i = 0; i < level && ptr != root; i++)
            cout<<"\t\t";
        cout<<ptr->word;
        display(ptr->left, level + 1);
    }
    cout << endl;
}

int main() {
    avlTree T;
    int choice;
    
    do {
        cout << "\n1. Insert new word";
        cout << "\n2. Display Tree";
        cout << "\n3. Exit";
        cout << "\nEnter your choice (1-3): ";
        
        cin >> choice;
        
        switch(choice) {
            case 1:
                T.insert();
                break;
                
            case 2:
                cout << "\nDictionary Structure:" << endl;
                T.display(T.root, 1);
                break;
                
                
            case 3:
                cout << "\n BYEEE !!! \n";
                break;
                
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while(choice != 3);
    
    return 0;
}

// Mar, May, Nov, Aug, Apr, Jan, Dec, Jul, Feb, Jun, Oct, Sep
//
//
// O(n log n)
