#include <stdio.h>
struct G { int u, c; };
char* r(struct G *g) {
    if(g->u==g->c) return "Draw";
    if((g->u==1&&g->c==3)||(g->u==2&&g->c==1)||(g->u==3&&g->c==2)) return "Win";
    return "Lose";
}
int main() {
    struct G g;
    while(1) {
        printf("1-R 2-P 3-S 0-Exit: "); scanf("%d", &g.u);
        if(g.u==0) break;
        g.c = g.u % 3 + 1;
        printf("C:%d %s\n", g.c, r(&g));
    }
}