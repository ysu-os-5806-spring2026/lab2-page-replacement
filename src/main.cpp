#include "pager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "fifo.cpp"
#include "second_chance.cpp"
#include "clock.cpp"
#include "lru_aging.cpp"
#include "optimal.cpp"

Pager* create_pager(const std::string& algo, int frames) {
    if (algo == "FIFO") return new FIFO(frames);
    if (algo == "SC") return new SecondChance(frames);
    if (algo == "CLOCK") return new ClockPager(frames);
    if (algo == "AGING") return new LRUAging(frames);
    if (algo == "OPT") return new Optimal(frames);
    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "Usage: ./pager --algo=FIFO --frames=4 --input=trace1.txt\n";
        return 1;
    }

    std::string algo = argv[1] + 7;
    int frames = stoi(argv[2] + 9);
    std::string infile = argv[3] + 8;

    std::ifstream in(infile);
    std::vector<int> trace;
    int x;
    while (in >> x) trace.push_back(x);

    Pager* p = create_pager(algo, frames);
    if (!p) {
        std::cout << "Unknown algorithm!\n";
        return 1;
    }

    for (int i = 0; i < trace.size(); i++) {
        int page = trace[i];

        if (!p->contains(page)) {
            p->page_faults++;
            int victim = p->select_victim(trace, i);
            p->frames[victim].page = page;
            p->frames[victim].load_time = p->current_time;
            p->frames[victim].age = 0;
        }

        int f = p->find_frame(page);
        p->frames[f].referenced = true;

        if (algo == "AGING") {
            dynamic_cast<LRUAging*>(p)->aging_tick();
        }

        p->current_time++;
    }

    std::cout << "Algorithm: " << algo << "\n";
    std::cout << "Frames: " << frames << "\n";
    std::cout << "Total references: " << trace.size() << "\n";
    std::cout << "Page faults: " << p->page_faults << "\n";
    std::cout << "Fault rate: " << (100.0 * p->page_faults / trace.size()) << "%\n";

    return 0;
}
