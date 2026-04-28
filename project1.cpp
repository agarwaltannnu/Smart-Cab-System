#include <bits/stdc++.h>


#define V 20
#define INF 99999

using namespace std;

vector<vector<int>> Floyd_Warshall(vector<vector<int>> graph) {
    vector<vector<int>> distance(V, vector<int>(V, 0));

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            distance[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    return distance;
}

int main() {
    vector<vector<int>> g(V, vector<int>(V, INF));
    g[0][2]=g[2][0]=2;
    g[0][4]=g[4][0]=2;
    g[4][5]=g[5][4]=3;
    g[2][3]=g[3][2]=4;
    g[3][10]=g[10][3]=2;
    g[1][8]=g[8][1]=5;
    g[1][6]=g[6][1]=1;
    g[6][7]=g[7][6]=6;
    g[2][7]=g[7][2]=2;
    g[8][9]=g[9][8]=4;
    g[4][9]=g[9][4]=2;
    g[5][14]=g[14][5]=2;
    g[11][12]=g[12][11]=1;
    g[16][12]=g[12][16]=1;
    g[8][12]=g[12][8]=3;
    g[8][17]=g[17][8]=8;
    g[7][18]=g[18][7]=7;
    g[8][13]=g[13][8]=2;
    g[13][14]=g[14][13]=4;
    g[14][15]=g[15][14]=2;
    g[9][19]=g[19][9]=4;
    g[10][15]=g[15][10]=1;
    g[15][19]=g[19][15]=2;
    g[14][19]=g[19][14]=6;
    g[14][18]=g[18][14]=3;
    g[17][19]=g[19][17]=2;
    g[18][19]=g[19][18]=2;
    unordered_map<char, int> autos;  // storing indices of autos
    autos['A'] = 0;
    autos['B'] = 1;
    autos['C'] = 2;
    autos['D'] = 3;
    autos['E'] = 4;
    //arr will contain shortest distance between pair of vertices
    vector<vector<int>> arr = Floyd_Warshall(g);
    for (int i = 0; i < V; i++) {
        arr[i][i] = 0;
    }

    char choice;
    int curr, togo;
    cout << "Enter the location you are currently at: ";
    cin >> curr;
    cout << "Enter the location you want to go to: ";
    cin >> togo;

    // Define a priority queue for autos
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> autoQueue;

    for (auto i : autos) {
        char auto_name = i.first;
        int auto_index = i.second;

        // Calculate the distance from the auto to the current location
        int distanceToCurrent = arr[auto_index][curr];
        autoQueue.push({distanceToCurrent, auto_name});
    }

    while(!autoQueue.empty())
    {
        char choice;
        cout << "Auto " << autoQueue.top().second << " will pick you up" << endl;
        cout << "Do you want to continue the this with this Auto(Y/N)? "<<endl;
        cin >> choice;
        if(choice=='Y' || choice=='y')
        {
            int mini = autoQueue.top().first;
            cout << "Distance to be traveled is " << mini + arr[curr][togo] << " km" << endl; 
            // Assuming a rate of 10 Rs per km
            cout << "Cost to be paid is " << 10 * (arr[curr][togo]) << " Rs" << endl;  
            break;
        }
        else
        {
            autoQueue.pop();
        }
    }
    if (autoQueue.empty()) {
        cout << "No autos are available at the moment." << endl;
    }
    return 0;
}
