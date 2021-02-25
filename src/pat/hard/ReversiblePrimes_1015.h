//
// Created by guojm on 2021/2/25.
//

#ifndef ALGORITHM_REVERSIBLEPRIMES_1015_H
#define ALGORITHM_REVERSIBLEPRIMES_1015_H
#include <cmath>
#include <iostream>
/**
 * 按进制反转后仍是素数
 * 关键在于判断素数的算法和进制反转的技巧
 * 反转：一开始是用链表分解数位，再逐位求和的方法去反转值，改良后采用多项式的方式
 * 判断素数: 对n从2到sqrt(n)取余，全部不为0则是素数
 * 关键字：进制运算，素数，快速判断素数
 */
namespace ReversiblePrimes_1015 {
    using namespace std;

    bool isPrime(int);
    int reverse(int,int);

//    struct Node{
//        int v = 0;
//        Node* next = nullptr;
//    };
//
//    struct Link{
//        int size = 0;
//        Node* root = nullptr;
//        Node* tail = nullptr;
//    };

    int main(){
        std::iostream::sync_with_stdio(false);
        cin.tie(nullptr);
        int N,D;
        cin>>N;
        while (true){
            if(N < 0){
                break;
            }
            cin>>D;
            if (isPrime(N) && isPrime(reverse(N,D)))
                cout<<"Yes";
            else
                cout<<"No";
            cin>>N;
            if (N > 0)
                cout<<"\n";
        }
        return 0;
    }

    bool isPrime(int n){
        if (n == 1)
            return false;
        int sn = sqrt(n);
        for (int i = 2; i < sn+1; ++i) {
            if(n % i == 0)
                return false;
        }
        return true;
    }

    /**
     * (((r1*d)+r2)*d+r3)*d ...
     * @param n
     * @param d
     * @return
     */
    int reverse(int n,int d){
        int result = 0;
        while (n){
            result = result*d + n%d;
            n /= d;
        }
        return result;
    }

//    int reverse(int n,int d){
//        Link link;
//        do{
//            int c = n%d;
//            n = n/d;
//            Node* node = new Node{
//                c,
//                nullptr
//            };
//            if (link.size == 0){
//                link.root = link.tail = node;
//            } else {
//                link.tail->next = node;
//                link.tail = link.tail->next;
//            }
//            link.size++;
//        } while (n != 0);
//        int result = 0;
//        //reverse
//        while (link.size > 0){
//            result += link.root->v * (int)pow(d,link.size-1);
//            link.root = link.root->next;
//            link.size--;
//        }
//        return result;
//    }

};


#endif //ALGORITHM_REVERSIBLEPRIMES_1015_H
