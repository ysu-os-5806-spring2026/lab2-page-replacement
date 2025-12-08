#include "pager.h"

class Optimal : public Pager {
public:
    Optimal(int n) : Pager(n) {}

    int select_victim(const std::vector<int>& future, int idx) override {
        int victim = -1;
        int farthest = -1;

        for (int i = 0; i < frame_count; i++) {
            int p = frames[i].page;
            int next_use = -1;

            for (int j = idx + 1; j < future.size(); j++) {
                if (future[j] == p) {
                    next_use = j;
                    break;
                }
            }

            if (next_use == -1) return i; // never used again

            if (next_use > farthest) {
                farthest = next_use;
                victim = i;
            }
        }
        return victim;
    }
};
