#include <stdio.h>
#include <algorithm>

using namespace std;

bool isCatalan(int* tar, int len){
    int cnt_zero = 0, cnt_one = 0;
    for(int i = 0; i < len; i ++){
        if(tar[i] == 0) cnt_zero++;
        if(tar[i] == 1) cnt_one++;
        if(cnt_zero < cnt_one) return false;
    }
    return true;
}

int main(){
    int n, cnt = 0;
    scanf("%d", &n);
    int *people = new int[n], *catalan = new int[n];
    for(int i = 0; i < n; i ++){
        scanf("%d", &people[i]);
        catalan[i] = i>=n/2?1:0;
    }
    sort(people, people+n);
    int *firstRow = new int[n/2], *secondRow = new int[n/2];
    do{
        int *tmp_f = firstRow, *tmp_s = secondRow;
        if(isCatalan(catalan, n)){
            for(int i = 0; i < n; i ++){
                if(catalan[i]==0) {
                 *tmp_f = people[i];
                 tmp_f ++;
                }
                if(catalan[i]==1) {
                    *tmp_s = people[i];
                    tmp_s ++;
                }
            }
            for(int i = 0; i < n/2; i ++){
                printf("%d ", firstRow[i]);
            }
            for(int i = 0; i < n/2; i ++){
                printf("%d", secondRow[i]);
                if(i<n/2-1) printf(" ");
            }
            printf("\n");
            cnt ++;
        }    
    } while(next_permutation(catalan, catalan+n));
    printf("%d", cnt);
    return 0;
}