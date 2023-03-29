#include <iostream>
#include <cmath>

typedef unsigned ElemTypeA;
typedef float ElemTypeB;

struct Node {
    ElemTypeA exp;
    ElemTypeB base;

    Node() = default;
    Node(ElemTypeA e, ElemTypeB b) : exp(e), base(b) {}
};

ElemTypeB calcOnce(Node node);
ElemTypeB calc();

int main() {
    ElemTypeB result = calc();
    std::cout << result << std::endl;
    return 0;
}

ElemTypeB calc() {
    int n;
    std::cin >> n;
    Node * data = new Node[n];
    for(int i = 0; i < n; i++) {
        ElemTypeA a;
        ElemTypeB b;
        std::cin >> a >> b;
        data[i] = Node(a, b);
    }

    ElemTypeB result=0;
    for(int i = 0; i < n; i++) {
        result += calcOnce(data[i]);
    }

    delete [] data;
    return result;
}
float quickpow(unsigned exp, float base)
{
    if (exp == 0)
        return 1;
    else
    {
        float newbase = quickpow(exp / 2, base);
        if (exp % 2 == 1)
            return newbase * newbase * base;
        else
            return newbase * newbase;
    }
}
ElemTypeB calcOnce(Node node) {
    ElemTypeB result= quickpow(node.exp, node.base);
    return result;
}
