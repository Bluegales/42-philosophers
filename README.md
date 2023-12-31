# 42-Philosophers

## Project Description

This is the Philosophers project for the 42 school curriculum. The project focuses on the classic dining philosophers problem and aims to develop a solution that ensures proper synchronization and avoids deadlocks and resource conflicts.

## Features

- **Dining Philosophers Simulation:** Implement a solution to the dining philosophers problem.
- **Concurrency:** Utilize threads and synchronization mechanisms (mutexes, semaphores) to control access to shared resources.
- **Resource Management:** Ensure that philosophers share resources (forks) efficiently and without conflicts.
- **Visualization (Optional):** Provide a visual representation of the dining philosophers simulation.

## Getting Started

### Prerequisites

- GCC compiler
- GNU Make

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/42-philosophers.git
    ```

2. Change into the project directory:

    ```bash
    cd 42-philosophers
    ```

3. Build the project:

    ```bash
    make
    ```

4. Run Philosophers Simulation:

    ```bash
    ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_meals]
    ```
