/*
ID: tangjin2
LANG: C++
TASK: milk3
*/
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
bool used[21]={}, hash[10001]={};
int lim[3]={}, stack[400][3]={}, head = 0, tail = 0;
int main()
{
   ifstream cin( "milk3.in", ios::in);
   ofstream cout("milk3.out", ios::out);
   int i, r, a, b, c;
   cin >> lim[0] >> lim[1] >> lim[2];
   stack[0][2] = lim[2];
   used[lim[2]] = true;
   hash[lim[2]] = true;
   while(head <= tail)
   {
      r = tail;
      for(i = head; i <= tail; ++i)
      {
         if(!stack[i][0]) used[stack[i][2]] = true;
         if(stack[i][0])
         {
            if(stack[i][1] < lim[1])
            {
               c = stack[i][2];
               if(stack[i][0] < lim[1] - stack[i][1]) a = 0, b = stack[i][0] + stack[i][1];
               else a = stack[i][0] + stack[i][1] - lim[1], b = lim[1];
               if(!hash[((a * 21) + b) * 21 + c])
               {
                  ++r;
                  stack[r][0] = a;
                  stack[r][1] = b;
                  stack[r][2] = c;
                  hash[((a * 21) + b) * 21 + c] = true;
               }
            }
            if(stack[i][2] < lim[2])
            {
               b = stack[i][1];
               if(stack[i][0] < lim[2] - stack[i][2]) a = 0, c = stack[i][0] + stack[i][2];
               else a = stack[i][0] + stack[i][2] - lim[2], c = lim[2];
               if(!hash[((a * 21) + b) * 21 + c])
               {
                  ++r;
                  stack[r][0] = a;
                  stack[r][1] = b;
                  stack[r][2] = c;
                  hash[((a * 21) + b) * 21 + c] = true;
               }
            }
         }
         if(stack[i][1])
         {
            if(stack[i][0] < lim[0])
            {
               c = stack[i][2];
               if(stack[i][1] < lim[0] - stack[i][0]) b = 0, a = stack[i][0] + stack[i][1];
               else b = stack[i][0] + stack[i][1] - lim[0], a = lim[0];
               if(!hash[((a * 21) + b) * 21 + c])
               {
                  ++r;
                  stack[r][0] = a;
                  stack[r][1] = b;
                  stack[r][2] = c;
                  hash[((a * 21) + b) * 21 + c] = true;
               }
            }
            if(stack[i][2] < lim[2])
            {
               a = stack[i][0];
               if(stack[i][1] < lim[2] - stack[i][2]) b = 0, c = stack[i][1] + stack[i][2];
               else b = stack[i][1] + stack[i][2] - lim[2], c = lim[2];
               if(!hash[((a * 21) + b) * 21 + c])
               {
                  ++r;
                  stack[r][0] = a;
                  stack[r][1] = b;
                  stack[r][2] = c;
                  hash[((a * 21) + b) * 21 + c] = true;
               }
            }
         }
         if(stack[i][2])
         {
            if(stack[i][0] < lim[0])
            {
               b = stack[i][1];
               if(stack[i][2] < lim[0] - stack[i][0]) c = 0, a = stack[i][0] + stack[i][2];
               else c = stack[i][0] + stack[i][2] - lim[0], a = lim[0];
               if(!hash[((a * 21) + b) * 21 + c])
               {
                  ++r;
                  stack[r][0] = a;
                  stack[r][1] = b;
                  stack[r][2] = c;
                  hash[((a * 21) + b) * 21 + c] = true;
               }
            }
            if(stack[i][1] < lim[1])
            {
               a = stack[i][0];
               if(stack[i][2] < lim[1] - stack[i][1]) c = 0, b = stack[i][1] + stack[i][2];
               else b = stack[i][1] + stack[i][2] - lim[1], c = lim[1];
               if(!hash[((a * 21) + b) * 21 + c])
               {
                  ++r;
                  stack[r][0] = a;
                  stack[r][1] = b;
                  stack[r][2] = c;
                  hash[((a * 21) + b) * 21 + c] = true;
               }
            }
         }
      }
      head = tail + 1;
      tail = r;
   }
   for(i = max(lim[2] - lim[1],0); i < lim[2]; ++i) if(used[i]) cout << i << " ";
   cout << i << endl;
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
}
