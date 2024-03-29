#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAX_N = 1005;
int man_list[MAX_N][MAX_N];
int woman_list[MAX_N][MAX_N];
int inverse_woman_list[MAX_N][MAX_N];
int man_partner[MAX_N];
int next_proposal[MAX_N];
int woman_partner[MAX_N];
void stableMatching(int n) {


    memset(woman_partner, -1, sizeof(woman_partner));
    memset(next_proposal, 0, sizeof(next_proposal));

    for (int w = 0; w != n; ++w) {
        for (int i = 0; i != n; ++i) {
            inverse_woman_list[w][woman_list[w][i]] = i;
        }
    }
    queue<int> freeman;
    for (int i = 0; i != n; i++)
        freeman.push(i);
        
    while (!freeman.empty()) {
        int m = freeman.front();
        freeman.pop();
        for (int i = next_proposal[m]; i != n; ++i) {
            int w = man_list[m][i];
            if (woman_partner[w] == -1) {
                woman_partner[w] = m;
                man_partner[m] = w;
                next_proposal[m] = i + 1;
                break;
            }
            else {
                int em = woman_partner[w];
                if (inverse_woman_list[w][m] < inverse_woman_list[w][em]) {
                    woman_partner[w] = m;
                    man_partner[m] = w;
                    next_proposal[m] = i + 1;
                    freeman.push(em);
                    break;
                }
            }
        }
    }
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &man_list[i][j]);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &woman_list[i][j]);
            }
        }

        stableMatching(n);

        printf("%d\n", n);
        for (int m = 0; m != n; ++m) {
            printf("%d %d\n", m, man_partner[m]);
        }
    }
    return 0;
}
