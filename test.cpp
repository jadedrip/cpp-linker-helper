#include <map>
#include <stdio.h>

int main(){
    std::map<int,int> m;
    m[0]=10;
    printf("%d", m.size());
    return 0;
}