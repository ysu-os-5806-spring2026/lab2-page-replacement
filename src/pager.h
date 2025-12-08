#ifndef PAGER_H
#define PAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <limits>

struct Frame {
    int page = -1;
    bool referenced = false;
    bool modified = false;
    unsigned int age = 0; // for Aging algorithm
    int load_time = 0;    // for FIFO
};

class Pager {
public:
    int frame_count;
    std::vector<Frame> frames;
    int current_time = 0;
    int page_faults = 0;

    Pager(int n) : frame_count(n), frames(n) {}

    virtual int select_victim(const std::vector<int>& future, int idx) = 0;

    void reset() {
        for (auto &f : frames) {
            f.page = -1;
            f.referenced = false;
            f.modified = false;
            f.age = 0;
            f.load_time = 0;
        }
        current_time = 0;
        page_faults = 0;
    }

    bool contains(int page) {
        for (auto &f : frames)
            if (f.page == page) return true;
        return false;
    }

    int find_frame(int page) {
        for (int i = 0; i < frame_count; i++)
            if (frames[i].page == page) return i;
        return -1;
    }
};

#endif
