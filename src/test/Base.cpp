//
// Created by wqn on 19-4-3.
//

#include <iostream>

using namespace std;


class Base {

public:


    virtual void f() { cout << "Base1::f" << endl; }



    virtual void g() { cout << "Base1::g" << endl; }



    virtual void h() { cout << "Base1::h" << endl; }



};



typedef void(*Fun)(void);




int main() {

 Base b;

 Fun pFun = NULL;

 cout << "虚函数表地址：" << (int*)(&b) << endl;

 cout << "虚函数表 — 第一个函数地址：" << (int*)*(int*)(&b) << endl;

 // Invoke the first virtual function

 pFun = (Fun)*((int*)*(int*)(&b));

 pFun();


//     Derive d;

//    int **pVtab = (int **) &d;


//    //Base1's vtable
//
//
//    pFun = (Fun)*((int*)*(int*)((int*)&d+0)+0);
//
//    //pFun = (Fun) pVtab[0][0];
//
//     pFun();
//
//
//   //pFun = (Fun)*((int*)*(int*)((int*)&d+0)+1);
//     pFun = (Fun) pVtab[0][1];
//
//     pFun();
//
//
//
//
//     //pFun = (Fun)*((int*)*(int*)((int*)&d+0)+2);
//
//    pFun = (Fun) pVtab[0][2];
//
//     pFun();
//
//
//
//
//    //Derive's vtable
//
//     //pFun = (Fun)*((int*)*(int*)((int*)&d+0)+3);
//
//     pFun = (Fun) pVtab[0][3];
//
//     pFun();
//
//
//
//
//     //The tail of the vtable
//
//    pFun = (Fun) pVtab[0][4];
//
//     cout << pFun << endl;
//
//
//     //Base2's vtable
//
//
//   //pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
//
//     pFun = (Fun) pVtab[1][0];
//
//     pFun();
//
//
//
//
//     //pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
//
//     pFun = (Fun) pVtab[1][1];
//
//     pFun();
//
//
//
//
//     pFun = (Fun) pVtab[1][2];
//
//     pFun();
//
//
//
//
//     //The tail of the vtable
//
//     pFun = (Fun) pVtab[1][3];
//
//     cout << pFun << endl;
//
//
//     //Base3's vtable
//
//
//     //pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
//
//     pFun = (Fun) pVtab[2][0];
//
//     pFun();
//
//
//
//
//     //pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
//
//     pFun = (Fun) pVtab[2][1];
//
//     pFun();
//
//
//
//     pFun = (Fun) pVtab[2][2];
//
//     pFun();
//
//
//
//
//    //The tail of the vtable
//
//     pFun = (Fun) pVtab[2][3];
//
//     cout << pFun << endl;
//
//


     return 0;

}



