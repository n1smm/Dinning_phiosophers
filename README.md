# PHILOSPHERS

![philosophers](dinning_philosophers_DALLE.jpg)

## Description
This project is a simulation of the dining philosophers problem. The dining philosophers problem is a classic synchronization problem that models a dining room with five philosophers sitting at a table doing one of two things: eating or thinking. While eating, they are not thinking, and while thinking, they are not eating. The problem is how to design a discipline of behavior (a concurrent algorithm) such that each philosopher gets a chance to eat and think. \
###This project uses threads and mutexes to simulate the philosophers and their eating habits.

## usage
To run the program, simply run the following command in the terminal:
```
make
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

