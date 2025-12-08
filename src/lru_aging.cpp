#include "pager.h"

class LRUAging : public Pager {
public:
    LRUAging(int n) : Pager(n) {}

    int select_victim(const std::vector<int>& future, int idx) override {
        unsigned int smallest = std::numeric_limits<unsigned int>::max();
        int victim = 0;

        for (int i = 0; i < frame_count; i++) {
            if (frames[i].age < smallest) {
                smallest = frames[i].age;
                victim = i;
            }
        }
        return victim;
    }

    void aging_tick() {
        for (auto &f : frames) {
            f.age >>= 1;
            if (f.referenced) f.age |= 0x80000000; // set MSB
            f.referenced = false;
        }
    }
};
