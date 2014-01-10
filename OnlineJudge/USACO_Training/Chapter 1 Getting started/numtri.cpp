/*
ID: tangjin2
LANG: C++
TASK: numtri
*/
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
int r;
struct node{int vue, cnt;} num[1001][1001]={};
int main()
{
   ifstream cin( "numtri.in", ios::in);
   ofstream cout("numtri.out", ios::out);
   int i, j;
   cin >> r;
   for(i = 1; i <= r; ++i)
      for(j = 1; j <= i; ++j)
      {
         cin >> num[i][j].vue;
         num[i][j].cnt = num[i][j].vue;
      }
  for(i = 1; i <= r; ++i)
     for(j = 1; j <= i; ++j)
        if(num[i - 1][j - 1].cnt > num[i - 1][j].cnt) num[i][j].cnt += num[i - 1][j - 1].cnt;
        else num[i][j].cnt += num[i - 1][j].cnt;
  for(i = 2; i <= r; ++i) if(num[r][i].cnt > num[r][1].cnt) num[r][1].cnt = num[r][i].cnt;
  cout << num[r][1].cnt << endl;
  cin.clear();cout.clear();
  cin.close();cout.close();
  return 0;
}
