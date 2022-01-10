#include<bits/stdc++.h>

struct A{
    int a;
    A(int v){a = v;}

    void func(){
        A obj(*this); 
        std::cout << obj.a << std::endl;
    }
};

int main(void){
    A yeah(3);
    yeah.func();
    return 0;
}