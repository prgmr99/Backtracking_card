#include <iostream>
#include <algorithm>

using namespace std;

int N = 9;
int Arr[9][4];
int arr[9];
int CNT = 0;
vector<pair<int, int>> p;
// 회전 수도 페어로 만들면 좋지 않을까?
// 우선은 회전 수 정보는 제외하고 구현해보자.

// promising function
// 여기서 퍼즐 매칭을 시켜야 해.
// 지금 k를 넘겨주고 받는 것이 문제가 있는 것 같아.
// index 변수를 받아야 할 것 같은데
bool check1(int k) {
    bool check = true;
    int flag = 0;
    
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            if(k == 3 || k == 6) {
                if((Arr[k][i] == p[i].first && Arr[k-3][j] == p[i].second) ||
                   (Arr[k][i] == p[i].second && Arr[0][j] == p[i].first)) {
                    check = true;
                    break;
                }
                else
                    check = false;
            }
            else if(k == 4 || k == 5 || k == 7 || k == 8) {
                if(((Arr[k][i] == p[i].first && Arr[k-1][j] == p[i].second) ||
                   (Arr[k][i] == p[i].second && Arr[k-1][j] == p[i].first)) &&
                   ((Arr[k][i] == p[i].first && Arr[k-3][j] == p[i].second) ||
                    (Arr[k][i] == p[i].second && Arr[k-3][j] == p[i].first))) {
                    check = true;
                    break;
                }
                else
                    check = false;
            }
            else if(k == 2) {
                if(check1(1))
                    check = true;
                else
                    check = false;
            }
            else {
                if((Arr[k][i] == p[i].first && Arr[k+1][j] == p[i].second) ||
                   (Arr[k][i] == p[i].second && Arr[k+1][j] == p[i].first)) {
                    check = true;
                    flag = 1;
                    break;
                }
                else
                    check = false;
            }
        }
        if(flag == 1)
            break;
    }
    flag = 0;
    return check;
}

bool promising(int index) {
    bool check = true;
    
    int k = 0;
    if(index == 0)
        check = true;
    
    // 항상 이전 조건문들을 만족해야하니까
    while(k<index && check) {
        if(!check1(k)) {
            check = false;
        }
        k++;
    }
    return check;
}
// 넘겨받은 index에 따라 false를 정해줘야 해.

// DFS function
void puzzle(int index) {
    int j;
    
    if(index == N - 1) {
        // 한 줄로 puzzle 출력하는 부분
        CNT++;
        for(int i = 0;i < N;i++)
            cout << arr[i] << " ";
        cout << '\n';
    }
    
    // 교재랑 다른 부분
    for(j=0;j<9;j++) {
        arr[index] = j+1;
        if(promising(index))
            puzzle(index+1);
    }
}


// Main function
int main(void) {
    p.push_back(make_pair(1,2));
    p.push_back(make_pair(3,4));
    p.push_back(make_pair(5,6));
    p.push_back(make_pair(7,8));
    
    
    for(int i=0;i<9;i++) {
        for(int j=0;j<4;j++) {
            cin >> Arr[i][j];
        }
    }
    
    // 각각의 index에 대해서 puzzle 함수를 돌려야 해
    puzzle(0);
    // 경우의 수 출력
    cout << CNT << '\n';
    return 0;
}
