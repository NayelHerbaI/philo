*This project has been created as part of the 42 curriculum by jihi.*

# Philosophers

## Description

This project implements the dining philosophers problem with threads and mutexes.
Each philosopher alternates between eating, sleeping and thinking. The simulation stops
when a philosopher dies or when every philosopher has eaten the required number of
meals.

## Instructions

Compile the project:

```bash
make
```

Run it:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200
```

## Resources

- `pthread_create`, `pthread_join`, `pthread_mutex_lock`, `pthread_mutex_unlock`
- `gettimeofday` and `usleep`
- Dining philosophers synchronization problem

AI was used to help analyze failing test cases, reorganize the files, and check style
constraints. The final code was reviewed, compiled, and tested manually.
