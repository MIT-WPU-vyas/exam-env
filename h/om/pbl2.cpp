/*
============================================================================
Name        : pbl2.cpp
Author      : Om
Subject     : Project Based Learning
Description : Facebook Friends Connection
============================================================================
*/

#include <iostream>

using namespace std;

class node{
    int id;
    string name;
    node *next;
    friend class graph;
    friend class queue;
    friend class stack;

};

class queue{
    int q[20];
    int front,rear;
    friend class BST;

    public:
        queue(){
            front = -1;
            rear = -1;
        }
        void insert(int );
        int del();
        int empty();
};

class stack{
    int st[20];
    int top;
    friend class graph;
    public:
        stack(){
            top = -1;
        }
        void push(int);
        int pop();
        int empty();
};

class graph{
    node* head[14];
    int visited[20];
    public:
        graph(){
            cout<<"Enter the Number of Vertices:";
            cin>> n;
            cout << endl;

            if (n > 14) {  // Prevent out-of-bounds access
                cout << "Error: Maximum number of vertices is 14." << endl;
                exit(1);
            }

            for(int i=0; i<n; i++){
                head[i] = new node();
                cout << "User ID " << i << endl;
                cout<< "Enter User Name:";
                fflush(stdin);
                getline(cin, head[i]->name);
                cout << endl;
                head[i]->id = i;
                head[i]->next = NULL;
            }
        }
		void create_adj_list();
		void display();
		node* search(int v_id);
		void DFT();
		void DFT_rec(int v);
		void DFT_non_rec();
		void BFT_non_rec();
		int n;
};


int main() {
    graph g1;

    int c;
    do {
    	cout << "Please Enter the Operation:" << endl
    			<< "1. Create Graph" << endl
				<< "2. Display Graph" << endl
				<< "3. Recursive Depth First Traversal" << endl
				<< "4. Non-Recursive Depth First Traversal" << endl
				<< "5. Non-Recursive Breadth First Traversal" << endl
				<< "6. Exit" << endl
				<< "Choice:";
    	cin >> c;

    	switch(c) {

    		case 1:
    			cout << endl;
    			g1.create_adj_list();
    			cout << endl;
    			break;

    		case 2:
    		    cout << endl;
    		    g1.display();
    		    cout << endl;
    		    break;

    		case 3:
    		    cout << endl;
    		    g1.DFT();
    		    cout << endl;
    		    break;

    		case 4:
    		    cout << endl;
    		    g1.DFT_non_rec();
    		    cout << endl;
    		    break;

    		case 5:
    		    cout << endl;
    		    g1.BFT_non_rec();
    		    cout << endl;
    		    break;

    		case 6:
    			break;

    		default:
    			cout << endl << "Please Enter the Correct Inputs" << endl;
    			break;
    	}
    }while(c != 6);

    return 0;
}

void queue :: insert (int temp){
    rear++;
    q[rear]=temp;
}

int queue :: del(){
    front++;
    return q[front];
}

int queue :: empty(){
    if (front==rear)
        return 1;
    else
        return 0;
}


void stack :: push(int temp){
    top++;
    st[top] = temp;
}

int stack :: pop(){
    int t;
    t = st[top];
    top--;
    return (t);
}

int stack :: empty(){
    if (top == -1)
        return 1;
    else
        return 0;
}


void graph :: create_adj_list(){
    char ch;
    for (int i = 0; i<n; i++){
        node *temp = head[i];
        while(true){
            cout << endl << "Enter 'y' if there exists any vertex connected with "<< head[i]->id << " :";
            cin >> ch;
            if(ch =='Y' ||  ch=='y'){
                node *curr = new node();
                cout << "Enter ID of the Connected Vertex: ";
                cin >> curr->id;
                curr->name = head[curr->id]->name;
                curr->next = NULL;
                temp->next = curr;
                temp = curr;
            }
            else
                break;
        }
    }
}

void graph :: display(){
    for(int i =0;i<n;i++){
        cout<< "The Connections of the user "<< head[i]->id <<" are "<<endl;
        node *temp = head[i]->next;
        if(temp!=NULL){
            while(temp!=NULL){
                cout << "User ID: "<< temp->id << endl;
                cout << "User Name: "<< temp->name << endl;
                temp = temp->next;
                cout << endl;
            }
        }
        else{
            cout<<"No Connections" <<endl;
        }
    }
}

void graph :: DFT(){
    int v;
    cout<<"Enter starting vertex for DFT: ";
    cin>>v;
    for(int i=0;i<n;i++){
        visited[i]=0;
    }
    visited[v]=1;
    DFT_rec(v);

}

void graph :: DFT_rec(int v){
    cout<<" "<<v<<" "<<head[v]->name;
    node* temp = head[v]->next;
    while(temp!=NULL){
        if(visited[temp->id] == 0){
            visited[temp->id] = 1;
            DFT_rec(temp->id);
        }
        temp = temp->next;
    }
}

void graph :: DFT_non_rec(){
    stack s;
    int v;
    cout<<"Enter the Starting Vertex:";
    cin>>v;
    for(int i=0; i<n; i++){
        visited[i]=0;
    }
    visited[v] = 1;
    s.push(v);
    while(!s.empty()){
        v=s.pop();
        cout<<" "<<v<<" "<< head[v]->name;
        node* temp = head[v]->next;
        while(temp!=NULL){
            if(visited[temp->id]==0){
                visited[temp->id]=1;
                s.push(temp->id);
            }
            temp=temp->next;
        }
    }
}

void graph :: BFT_non_rec(){
    queue q;
    int v;
    cout<<"Enter the Starting Vertex:";
    cin>>v;
    for(int i=0; i<n; i++){
        visited[i]=0;
    }
    visited[v] = 1;
    q.insert(v);
    while(q.empty()==0){
        v=q.del();
        cout<<" "<<v<<" "<< head[v]->name;
        node* temp = head[v]->next;
        while(temp!=NULL){
            if(visited[temp->id]==0){
                visited[temp->id]=1;
                q.insert(temp->id);
            }
            temp=temp->next;
        }
    }
}
