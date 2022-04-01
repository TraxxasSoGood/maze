#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

int rows, cols = 0;
vector<vector<char>> maze;


const char charEntree = '1';
const char charSortie = '2';


class Coordinate
{
public:
    int X;
    int Y;
    Coordinate(int x = 0, int y = 0){
     X = x, Y = y;
    }
};

Coordinate entree;
Coordinate sortie;


void readFile(std::string file) {
    ifstream fp(file);

    if (!fp) {
        cout << "impossible d'ouvrir le fichier" << endl;
    }

    string line, item;
    while ( getline( fp, line ) ){
        rows++;
        std::vector<char> row;
        for (char &c : line) {
            if (c != ',') {
                row.push_back(c);
            }
        }
        maze.push_back(row);
    }
    cols = line.size();

}
void afficher() {
    for(int i = 0; i<rows; i++) {
        for(int j = 0; j<cols; j++) {
            cout<<maze[i][j];
        }
        cout<<endl;
    }
}
bool resoure(int X, int Y) {
    if (maze[Y][X] == charSortie)
        return true;
    if (maze[Y][X] == '*' || maze[Y][X] == 'x')
        return false;
     else {
        maze[Y][X] = 'x';

        if(X+1<cols)
            if (resoure(X + 1, Y))
                return true;
        if(Y-1>=0)
            if (resoure(X, Y - 1))
                return true;
        if(X-1>=0)
            if ( resoure(X - 1, Y))
                return true;
        if(Y+1<rows)
            if (resoure(X, Y + 1))
                return true;

        //maze[Y][X] = ' ';
    }
     //afficher();
     //cout<<endl;
    return false;
}

bool entreeSortie() { //return 0 pas trouvee entree ou sortie
    bool e, s = false;
    for(int i = 0; i<rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(maze[i][j] == charEntree) {
                entree = Coordinate(j, i);
                e=true;
            }
            if(maze[i][j] == charSortie) {
                sortie = Coordinate(j, i);
                s=true;
            }
        }
    }
    return e && s;
}
int main(int argc, char* argv[])
{
    //cout<< argv[1];
    int numMap;
    std::string map;

        cout<< "1 : oval_01"<<endl;
        cout<< "2 : rect_01"<<endl;
        cout<< "3 : rect_02"<<endl;
        cout<< "4 : rect_03"<<endl;
        cout<< "5 : rect_04"<<endl;
        cout<< "6 : rect_05"<<endl;
        cin >> numMap;
        if(numMap==1) {
            map = "../maps/oval_01.map";
        } else if (numMap == 2) {
            map = "../maps/rect_01.map";
        } else if (numMap == 3) {
            map = "../maps/rect_02.map";
        } else if (numMap == 4) {
            map = "../maps/rect_03.map";
        } else if (numMap == 5) {
            map = "../maps/rect_04.map";
        } else if (numMap == 6) {
            map = "../maps/rect_05.map";
        }
        clock_t start, end;

        readFile(map);
        if (entreeSortie()) {
            start = clock();
            if (resoure(entree.X, entree.Y)) {
                printf("resolut \n");
            }
            end = clock();
            afficher();

            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << time_taken << endl;

        }

    return 0;
}