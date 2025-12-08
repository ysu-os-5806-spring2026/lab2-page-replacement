#include "pager.h"

class SecondChance : public Pager {
public:
    int hand = 0;

    SecondChance(int n) : Pager(n) {}

    int select_victim(const std::vector<int>& future, int idx) override {
        while (true) {
            if (!frames[hand].referenced) {
                int victim = hand;
                hand = (hand + 1) % frame_count;
                return victim;
            }
            frames[hand].referenced = false;
            hand = (hand + 1) % frame_count;
        }
    }
};
