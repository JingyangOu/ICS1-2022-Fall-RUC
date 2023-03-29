#include <bits/stdc++.h>

const int MAXN=1e5+10;

char s[MAXN];

int main(){
    std::cin.getline(s,MAXN);
    int mask=1<<5,len=strlen(s)
    for(int i = 0; i < len; ++i){
        if(std::isalpha(s[i]))
            s[i] ^=mask ;
    }
    printf("%s\n", s);
    return 0;
}
