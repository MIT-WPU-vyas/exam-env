// Consider a friend’s network on Facebook social web site. Model it as a graph to
// represent each node as a user and a link to represent the friend relationship between
// them using adjacency list representation and perform DFS &amp; BFS traversals .
// a. Create the Graph using Adjacency list ( Friend name , ID)
// b. Display the Graph
// c. Perform the recursive and non-recursive Traversal using Depth First Traversal (Using ID)
// d. Perform the non-recursive Traversal using Breadth First Traversal


#include <iostream>
#include <string>
#include <queue>

using namespace std;
class node{
    int id;
    string name;
    node * next;
    friend class graph;
};

class stack1 {
    int st[20];
    int top;
public:
    stack1() { top = -1; }
    
    void push(int temp) {
        if (top < 19) {
            st[++top] = temp;
        }
        else {
            cout << "Stack Overflow\n";
        }
    }
    int pop() {
        if (top >= 0)
            return st[top--];
        else 
        {
            cout << "Stack Underflow\n";
            return -1;
        }
    }
    bool empty() { 
        return top == -1; 
        }
};


class graph{
    node* head[14];
    int n;
    int visited[20];
    public:
        graph(){
            cout<<"enter no. of vertices: ";
            cin>> n;
            for(int i=0; i<n; i++){
                head[i] = new node();
                cout<< "enter user name of " << i << " : ";
                cin>> head[i]->name;
                head[i]->id = i;
                head[i]->next = NULL;
            }
            cout<< "Vertices stored\n";
        }
    void create_adj_list();
    void display();
    node* search(int v_id);
    void DFT();
    void DFT_rec(int v);
    void DFT_non_rec();
    void BFT_non_rec();
    
};

void graph :: create_adj_list(){
    char ch;
    for (int i = 0; i<n; i++){
        node *temp = head[i];
        while(1){
            cout<< "\nIs there any vertex connected with "<< head[i]->id  << " : ";
            cin>> ch;
            if(ch=='Y' | ch=='y'){
                node *curr = new node();
                cout<<"Enter connected vertex id: ";
                cin>> curr->id;
                
                if (curr->id == i){
                    cout<<"self loop not allowed!!";
                    delete curr;
                }
                else {
                    curr->name = head[curr->id]->name;
                    curr->next = NULL;
                    temp->next = curr;
                    temp = curr;
                } 

            }
            else
                break;
        }
    }
}

void graph :: display(){
    for(int i =0;i<n;i++){
        node *temp = head[i]->next;
        cout<< "the connections of users "<< head[i]->id <<" are "<<endl;
        if(temp!=NULL){
            while(temp!=NULL){
                cout<<"user id: "<<temp->id<< " user name: "<< temp->name << endl;
                temp = temp->next;
            }
        }
        else{
            cout<<"no connections" <<endl;
        }
    }
}

void graph :: DFT(){
    for (int i=0;i<n;i++){
        visited[i]=0;
    }
    int k;
    cout<<"Enter starting vertex id :";
    cin >> k;
    DFT_rec(k);
    
    
}

void graph :: DFT_rec(int v){
    cout<<" "<<v<<" "<<head[v]->name;
    visited[v]=1;
    node* temp = head[v]->next;
    while(temp!=NULL){
        if(! visited[temp->id]){
            visited[temp->id] = 1;
            DFT_rec(temp->id);
        }
        temp = temp->next;
    }
}

void graph :: DFT_non_rec(){
    stack1 s;
    int k;
    cout<<"Enter start vertex for DFT(non-rec) : ";
    cin>>k;
    for(int i=0; i<n; i++){
        visited[i]=0;
    }
    visited[k] = 1;
    s.push(k);
    while(s.empty()!=1){
        k=s.pop();
        cout<<" "<<k<<" "<< head[k]->name;
        node* temp = head[k]->next;
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
    queue<int> q;
    int v;
    cout<<"Enter starting vertex for BFT(non-rec):";
    cin>>v;
    for(int i=0; i<n; i++){
        visited[i]=0;
    }
    visited[v] = 1;
    q.push(v);
    while(q.empty()==0){
        v=q.front();
        q.pop();
        cout<<" "<<v<<" "<< head[v]->name;
        node* temp = head[v]->next;
        while(temp!=NULL){
            if(visited[temp->id]==0){
                visited[temp->id]=1;
                q.push(temp->id);
            }
            temp=temp->next;
        }
    }
}



int main() {
    graph g1;
    cout<<"\n\n\n--------Creation of graph------------- \n";
    g1.create_adj_list();
    
    cout<<"\n\n\n--------Display of graph-------------- \n";
    g1.display();

    cout<<"\n\n\n--------Depth first traversal (recurr) of graph-------------- \n";
    g1.DFT();

    cout<<"\n\n\n--------Depth first traversal (non-recurr) of graph-------------- \n";
    g1.DFT_non_rec();

    cout<<"\n\n\n--------Depth first traversal (non-recurr) of graph-------------- \n";
    g1.BFT_non_rec();
    


    return 0;
}
