#include <iostream>
#include <string>
using namespace std;

class avl_node{
    string word ;
    string meaning;
    avl_node *left ,*right;

    public :
        friend class avlTree;
};

class avlTree{
    public:
        avl_node *root;
        int height(avl_node*);
        int diff(avl_node*);
        avl_node *rr_rot(avl_node *);
        avl_node *ll_rot(avl_node *);
        avl_node *lr_rot(avl_node *);
        avl_node *rl_rot(avl_node *);
        avl_node *balance(avl_node *);
        void insert();
        avl_node *insert(avl_node *,avl_node *);
        void display(avl_node *,int );
        avl_node *search(avl_node *,string);
        int comp =0;
        void update(string);
        avlTree(){
            root=NULL;
        }
};

avl_node *avlTree::search(avl_node *parent, string key) {
    comp=comp+1;
    if (parent == NULL) {
        cout << "Word not found!\n";
        return parent;
    }
    if (key == parent->word) {
        cout << "Word: " << parent->word << "\nMeaning: " << parent->meaning << "\n";
        return parent;
    } else if (key < parent->word) {
        return search(parent->left, key);
    } else {
        return search(parent->right, key);
    }
}


void avlTree::update(string key) {
    avl_node *node = search(root, key);
    if (node) {
        cout << "Enter new meaning: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, node->meaning);
        cout << "Meaning updated successfully!\n";
    }
}



avl_node * avlTree :: ll_rot(avl_node *parent){
    avl_node *temp=parent->left;
    parent->left = temp->right;
    temp->right =parent;
    return temp;
}
avl_node * avlTree :: rr_rot(avl_node *parent){
    avl_node *temp=parent->right;
    parent->right = temp->left;
    temp->left =parent;
    return temp;
}

avl_node * avlTree :: lr_rot(avl_node *parent){
    avl_node *temp=parent->left;
    parent->left = rr_rot(temp);
    return ll_rot(parent);
}
avl_node * avlTree :: rl_rot(avl_node *parent){
    avl_node *temp=parent->right;
    parent->right = ll_rot(temp);
    return rr_rot(parent);
}
int avlTree::diff(avl_node *temp){
    int l_height=height(temp->left);
    int r_height=height(temp->right);
    int b_factor = l_height-r_height;
    return b_factor;
}
int avlTree:: height(avl_node *temp){
    int h=0;
    if(temp!= NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
avl_node* avlTree:: balance(avl_node *temp){
    int bal_factor = diff (temp);
    if (bal_factor > 1){ 
        if (diff (temp->left) > 0){
            temp = ll_rot (temp);
            cout<<" ll rotation performed\n";
        }
        else{
            temp = lr_rot(temp);
            cout<<" lr rotation performed\n";
        }
    }
    else if (bal_factor < -1){
        if (diff (temp->right) > 0){
            temp = rl_rot (temp);
            cout<<" rl rotation performed\n";
        }
        else{
            temp = rr_rot (temp);
            cout<<" rr rotation performed\n";
        }

    }
    return temp;
}

void avlTree :: insert(){
    char ch;
    do{
        avl_node *temp = new avl_node;
        cout<<"Enter word and its meaning :";
        cin>>temp->word>>temp->meaning;
        root = insert(root,temp);
        cout<<"do you want to add another node (y/n):";
        cin>>ch; 
    }while (ch == 'y');
}

avl_node * avlTree::insert(avl_node *root,avl_node *temp){
    if(root == NULL){
        root = new avl_node;
        root->word=temp->word;
        root->meaning=temp->meaning;
        root->left=NULL;
        root->right=NULL;
        return root;
    }
    else if (temp->word < root->word){
        root->left = insert(root->left,temp);
        root=balance(root);
    }
    else if (temp->word >= root->word){
        root->right = insert(root->right,temp);
        root=balance(root);
    }
    return root;

}

void avlTree :: display(avl_node *ptr,int level){
    if(ptr!=NULL){
        display(ptr->right, level + 1);
        cout<<"\n";
        if (ptr == root){
            cout<<"Root -> ";
        }
        for (int i = 0; i < level && ptr != root; i++){
            cout<<"\t\t";
        }
        cout<<ptr->word;
        display(ptr->left, level + 1);

    }

}

int main() {
    avlTree a;
    int choice;
    string k;
    do {
        cout << "\nAVL Tree Operations:\n";
        cout << "1. Insert\n";
        cout << "2. Display\n";
        cout << "3. Search\n";
        cout << "4. Update meaning\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                a.insert();
                break;
            case 2:
                a.display(a.root, 1);
                break;
            case 3:
                cout<<"Enter word to be searched :";
                cin>>k;
                a.search(a.root,k );
                cout<<"Number of comparisions are :"<<a.comp<<endl;
                a.comp=0;
                break;
            case 4:
                cout<<"Enter word to be searched :";
                cin>>k;
                a.update(k);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    } while (choice != 5);
    return 0;
}