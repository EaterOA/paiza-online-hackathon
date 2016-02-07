/* combine_bucket.cpp
 *
 * Uses bucket sort to arrange and filter prices. Because max price (P) is only
 * 1000000 (roughly ~N), bucket sort can be done in linear time.
 *
 * After sorting, searching for closest pair for each day will take ~N
 * operations by pairing elements from each end of the list, and moving
 * pointers towards each other. In practice, it's slightly faster due to
 * initial binary search as well as duplicate prices being filtered out
 * from the initial sort.
 *
 * Fast enough for max input test cases.
 *
 * Complexity: O(DN)
 */

#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 500000
#define MAXD 300
#define MAXP 1000000

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

    // bucket sort
    int buckets[MAXP+1] = {0};
    for (int i = 0; i < N; i++) {
        buckets[prices[i]]++;
    }
    int count = 0;
    for (int i = 0; i < MAXP+1; i++) {
        if (buckets[i] == 1) {
            prices[count++] = i;
        } else if (buckets[i] >= 2) {
            // at most 2 items of the same price are needed
            prices[count++] = i;
            prices[count++] = i;
        }
    }

    // close in on both ends to find closest pairs
    for (int i = 0; i < D; i++) {
        int* start = prices;
        int* end = (upper_bound(prices, prices+count, targets[i])) - 1;
        while (start < end) {
            while (*start + *end > targets[i]) {
                end--;
            }
            if (start < end) {
                int sum = *start + *end;
                if (sum > closest[i]) {
                    closest[i] = sum;
                    if (sum == targets[i]) {
                        break;
                    }
                }
            }
            start++;
        }
    }

    for (int i = 0; i < D; i++) {
        cout << closest[i] << "\n";
    }
}
