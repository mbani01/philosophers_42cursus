# Philosophers
This project is a training to multi-threads/multi-process programming with the use of mutex and semaphore.
It contains 2 different programs simulating a twist of the famous Dining Philosophers problem, all with the same basic rules.
This project is also a good lesson in C optimization as we need to save every bit of CPU usage we can to ensure the survival of our philosophers.

### Concept

Philosophers (represented by parts of a program) sit around a table, with a big plate of spaghetti at its center. They each have a fork, but they need two forks to eat ; so they need to borrow their neighbor's fork to eat.

Of course, if they borrow a neighbor's fork, the neighbor can't use the fork. The processes / threads must communicate, to know the state of the forks (and of the other philosophers) at all times. There must also be a parent process that monitors everything.

### Philo, Philo_bonus !

[**philo**](https://github.com/mbani01/philosophers_42cursus/tree/master/philo) does this using **threads** as philosophers, and **mutexes** as forks.

[**philo_bonus**](https://github.com/mbani01/philosophers_42cursus/tree/master/philo_bonus) forks itself, making philosophers **processes**. Its forks are **semaphores**. It uses threads too, but only for monitoring.
