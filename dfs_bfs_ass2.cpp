#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

class gnode {
    int id;
    string name;
    gnode * next;
    friend class graph;
};

class graph{
    private:
    gnode *head[20];
    int n;

    public:
    graph(){
        cout << "Enter the no. of vertices : ";
        cin >> n;

        for(int i = 0; i< n;i++){
            head[i] = new gnode();
            cout << "Enter the name of the Student : ";
            cin >> head[i] -> name;
            head[i] -> id = i;
            head[i] -> next = NULL;
        }
    }

    void create_adj() {
        char ch;
        int v;
        gnode * temp;
            for(int i = 0; i< n; i++){
                temp = head[i];
                do {
                cout << "Enter a vertex ID that is a friend of " << head[i]->name << " (ID " << i << "): ";
                cin >> v;

                if (v < 0 || v >= n) {
                    cout << "Invalid vertex ID. Please try again." << endl;
                    continue;
                }

                if (v == i) {
                    cout << "Self-loops are not allowed." << endl;
                    continue;
                }

                else {
                    gnode* newNode = new gnode();
                    newNode -> id = v;
                    temp->next = newNode;
                    temp = temp->next;
                 }

                cout << "Do you want to add more friends for " << head[i]->name << "? (y/n): ";
                cin >> ch;
            } while (ch == 'y' || ch == 'Y');
        }
    }

    void displayGraph() {
        cout << "Displaying the Graph" << endl;
        for (int i = 0; i < n; i++) {
            gnode* temp = head[i];
            cout << temp->name << " (ID " << temp->id << ") -> ";
            temp = temp->next;
            while (temp) {
                cout << temp->name << " (ID " << temp->id << ") -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
    }

    void BFS(int start) {
        bool visited[20] = {0};
        queue<int> q;
        visited[start] = 1;
        q.push(start);

        cout << "BFS Traversal starting from " << head[start]->name << ": "<< endl;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << head[v]->id << " : ";
            cout << head[v]->name << " "<<endl;

            for (gnode* temp = head[v]->next; temp; temp = temp->next) {
                if (!visited[temp->id]) {
                    visited[temp->id] = 1;
                    q.push(temp->id);
                }
            }
        }

        cout << endl;
    }

    void dfs(int v, bool visited[]) {
        visited[v] = true;
        cout << head[v]->name << " ";

        for (gnode* temp = head[v]->next; temp; temp = temp->next) {
            if (!visited[temp->id]) {
                dfs(temp->id, visited);
            }
        }
    }

    void dfs(int start) {
        bool visited[20] = {false};
        cout << "dfs traversal starting from " << head[start]->name << ": ";
        dfs(start, visited);
        cout << endl;
    }


    void dfs_nr(int start){
        bool visited[20] = {false};
        stack<int> s;
        s.push(start);
        visited[start] = 1;
        while(!s.empty()) {
        int v = s.top();
        s.pop();
        cout << head[v]->id << " : ";
        cout << head[v]->name << " "<<endl;
        for (gnode* temp = head[v]->next; temp; temp = temp->next) {
                if(!visited[temp->id]){
                s.push(temp->id);
                visited[temp->id] = 1;
            }
        }
    }
    }


};



int main() {
    int start;
    graph g;
    g.create_adj();
    g.displayGraph();
    cout << "Enter the ID of the student from where you want ot start the Traversal" << endl;

    cin >> start;
    g.dfs(start);
    g.dfs_nr(start);
    g.BFS(start);
    return 0;
}



// O(V+E)
