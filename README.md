# Lab 2 – Page Replacement Algorithms
CSCI 5806 – Operating Systems  
Youngstown State University  

This lab implements a **page reference trace simulator** supporting five classical page replacement algorithms:

- **FIFO – First-In, First-Out**
- **Second-Chance** (using the reference bit)
- **CLOCK** (circular list)
- **LRU (Aging Approximation)** — using the aging register
- **Optimal** — simulated as a theoretical baseline

Your implementation will help you understand how different algorithms behave under the same page reference stream, as discussed in **Chapter 3 (Memory Management)** of the textbook.

---

## 📁 Repository Structure

src/
main.cpp
pager.h
fifo.cpp
second_chance.cpp
clock.cpp
lru_aging.cpp
optimal.cpp

tests/
trace1.txt
trace2.txt
trace3.txt
run_tests.sh


- **Do NOT modify** `run_tests.sh` (used by autograding).
- You will implement the logic inside the `.cpp` files under `src/`.

---

## 🧠 Page Replacement Algorithms (What You Implement)

### 1. FIFO  
Frames are replaced in the order they were loaded.

### 2. Second-Chance  
FIFO with an additional `referenced` bit (R-bit). Processes with `R=1` get a “second chance.”

### 3. CLOCK  
A circular version of Second-Chance using a rotating hand pointer.

### 4. LRU Approximation (Aging)  
Implements the aging algorithm (textbook Figure 3.17):  
Each frame maintains an *aging register*, updated on every reference.

### 5. Optimal (OPT)  
Selects the frame whose next use is farthest in the future.  
Not implementable in real OS → used only for comparison.

---

## ▶️ Build Instructions

You may use any C++ compiler that supports C++17.

### Compile:
```bash
g++ -std=c++17 -O2 -o pager src/main.cpp


Run:
./pager --algo=CLOCK --frames=4 --input=tests/trace1.txt

Supported --algo= values:
FIFO
SC
CLOCK
AGING
OPT

📝 Expected Output

A successful run should print:

Algorithm: CLOCK
Frames: 4
Total references: 14
Page faults: 9
Fault rate: 64.3%


(Your exact results depend on the algorithm implementation.)

🧪 Testing (Local)

You can run the same script used by the autograder:

chmod +x tests/run_tests.sh
./tests/run_tests.sh


This will:

Compile your code

Run several algorithms

Check basic output formatting

📌 Autograding (GitHub Classroom)

Every time you git commit and git push, GitHub Actions will:

Compile your code

Run run_tests.sh

Assign a score based on correctness

You may view results under the Actions tab of your GitHub repository.

📰 Lab Report Requirement

In addition to code, you must submit a one-page PDF report through Blackboard summarizing:

A short explanation of each algorithm

Experimental results (page fault counts for all traces)

Comparison and analysis of algorithm behavior

Reflection on what you learned

Report details are provided in the Lab 2 handout.

📅 Due Date

January 25, 2026

Code: submitted via GitHub Classroom

Report: submitted via Blackboard

Both components are required for full credit.

🆘 Need Help?

Contact your instructor or visit office hours for debugging assistance.
Remember: You may discuss ideas with classmates, but all code must be your own.

Good luck, and have fun exploring page replacement strategies!
