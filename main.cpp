/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;
int main() {
    int q; 
    cin >> q;
    
    stack<int> stack1, stack2;
    
    while (q--) {
        int query;
        cin >> query;
        
        if (query == 1) {
            int x;
            cin >> x;
            stack1.push(x); 
        } 
        else if (query == 2) {
            if (stack2.empty()) {
                while (!stack1.empty()) {
                    stack2.push(stack1.top());  
                    stack1.pop();
                }
            }
            if (!stack2.empty()) {
                stack2.pop();  
            }
        } 
        else if (query == 3) {
            if (stack2.empty()) {
                while (!stack1.empty()) {
                    stack2.push(stack1.top()); 
                    stack1.pop();
                }
            }
            if (!stack2.empty()) {
                cout << stack2.top() << endl; 
            }
        }
    }

    return 0;
}

