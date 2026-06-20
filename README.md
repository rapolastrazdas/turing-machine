# Turing Machine Simulator

A C++ simulator capable of executing multiple Turing Machines simultaneously. The simulator supports both **single-tape** and **two-tape** Turing Machine configurations, dynamically expanding the tapes as the machine heads move.

---

## Features

* **Multi-Machine Execution:** Run and monitor multiple Turing Machines at the same time.
* **Dual-Tape Support:** Seamlessly handles both 1-tape and 2-tape operations based on the input configuration.
* **Dynamic Tape Expansion:** Automatically expands tapes with blank symbols (`_`) when the head moves past the current boundaries.
* **Interactive Termination:** Allows the user to break out of execution loops at any time by pressing any key.

---

## Input File Format

The simulator reads machine configurations from a plain text file. The structure varies slightly depending on whether you are configuring a single-tape or two-tape machine.

### Single-Tape Format
```text
1
[initial_tape]
[head_position]
[current_state] [current_symbol] [new_symbol] [direction] [new_state]
...
```

### Two-Tape Format
```text
2
[initial_tape_1]
[initial_tape_2]
[head_1_position] [head_2_position]
[current_state] [current_symbol_1] [current_symbol_2] [new_symbol_1] [new_symbol_2] [direction_1] [direction_2] [new_state]
...
```
### Format Details:
**1 or 2:** The number of tapes.

**head_position:** 1-based index indicating where the head starts (internally converted to 0-based index).

**direction:** Head movement direction. Use L for Left, R for Right, or any other character to stay put.

**H:** Reserved state name for the Halt state.

### Examples
1 tape examples [1-4].txt, 

2 tape examples [5-6].txt 

### Compile and Run
#### Prerequisites

1. C++ compiler (such as g++).

2. Windows OS: The program utilizes the <conio.h> header for the _kbhit() function to intercept keyboard inputs.

#### Compilation and execution

Open your terminal or command prompt and run:

```text
g++ -o turing_simulator main.cpp
```

Run the compiled executable:

```text
./turing_simulator
```

### How to Use
**Launch the simulator:** Run the executable file.

**Set the machine count:** Enter how many Turing Machines you would like to step through simultaneously.

**Provide files:** Enter the exact filename (e.g., machine1.txt) for each machine's instructions.

**Observe or Stop:** The console will display the step-by-step state transition and tape views of all machines. Press any key on your keyboard to manually interrupt the simulation if a machine gets stuck in an infinite loop.
