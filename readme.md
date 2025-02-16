# philosophers

**philosophers** is a project that simulates the dining philosophers problem using threads and mutexes. The goal of the project is to create a simulation where multiple philosophers (represented by threads) are seated at a table and must share resources (forks) in a way that prevents deadlock and ensures that all philosophers are able to eat. The project includes a bonus feature that introduces an additional challenge for synchronization.

---

## About

The **philosophers** project is based on the classical "dining philosophers problem," where a set of philosophers sit around a table, each with a fork on either side. They need both forks to eat, but they can only hold one fork at a time. The goal is to design a system where philosophers can eat without deadlock or race conditions.

### Core Requirements:
- Simulate philosophers sitting at a table with a limited number of forks.
- Ensure that each philosopher can think and eat without causing deadlock.
- Each philosopher should alternate between thinking and eating.
- Use threads for concurrency and mutexes for synchronization.

---

## Installation

To install **philosophers**, follow these steps:

1. Clone this repository:
    ```bash
    git clone https://github.com/ahmedelbahri/philosophers.git
    cd philosophers
    ```

2. Compile the project:
    ```bash
    make
    ```

3. Optionally, to remove all compiled objects:
    ```bash
    make clean
    ```

4. To remove the executable:
    ```bash
    make fclean
    ```

5. To recompile the project after cleaning:
    ```bash
    make re
    ```

---

## Usage

You can run the program by passing the number of philosophers and other parameters such as the time each philosopher will spend eating and thinking:

```bash
./philosophers <num_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [num_of_times_each_philosopher_must_eat]

```
## Bonus

In the **bonus** section, the following additional feature is implemented:

- **Enforce a philosopher to eat a certain number of times**: This bonus feature adds the possibility of limiting how many times each philosopher should eat before the simulation ends. This introduces additional complexity, as the program needs to ensure that all philosophers eat the specified number of times without causing deadlock.

To run the bonus feature, specify the number of times each philosopher should eat:

```bash
./philosophers 5 800 200 200 5
