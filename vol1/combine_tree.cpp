/* combine_tree.cpp
 *
 * Simple solution using a tree set. As each price is inserted, the tree can be
 * searched for the highest element that, when paired with the current element,
 * yields the closest value to the day's target. This is repeated for each day.
 *
 * Too slow for max input test cases.
 *
 * Complexity: O(DNlogN)
 */

#include <iostream>
#include <set>

using namespace std;

#define MAXN 500000
#define MAXD 300

int main()
{
    int N, D;
    cin >> N >> D;

    int prices[MAXN];
    int targets[MAXD];
    int closest[MAXD] = {0};

    for (int i = 0; i < N; i++)
        cin >> prices[i];
    for (int i = 0; i < D; i++)
        cin >> targets[i];

    set<int> existing;
    existing.insert(prices[0]);
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < D; j++) {
            if (targets[j] < prices[i])
                continue;
            set<int>::iterator pairing = (existing.upper_bound(targets[j] - prices[i]));
            if (pairing != existing.begin()) {
                pairing--;
                if (pairing != existing.end() && *pairing + prices[i] > closest[j]) {
                    closest[j] = *pairing + prices[i];
                }
            }
        }
        existing.insert(prices[i]);
    }

    for (int i = 0; i < D; i++) {
        cout << closest[i] << "\n";
    }
}
