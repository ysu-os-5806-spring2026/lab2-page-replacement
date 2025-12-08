#include "pager.h"

class FIFO : public Pager {
public:
    FIFO(int n) : Pager(n) {}

    int select_victim(const std::vector<int>& future, int idx) override {
        int victim = 0;
        int oldest = frames[0].load_time;

        for (int i = 1; i < frame_count; i++) {
            if (frames[i].load_time < oldest) {
                oldest = frames[i].load_time;
                victim = i;
            }
        }
        return victim;
    }
};
