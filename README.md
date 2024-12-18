# 42_PHILOSOPHERS

Goal

    - Mandatory : Handle threads and mutex and optimize use of CPU
      - Write a program that takes between 0 and 200 philosophers.
      - Each philosopher is a thread.
      - They all eat, think then sleep in a loop until one of them die or all have eaten a certain nb of time
      - A philosopher die if he didn't start to eat time_to_die since the beginning of its last meal 
      - There is one fork between each philo, and in order two eat they need to take their right and left forks.
      - While a philo is holding a fork , his neighbour can't take it
      - Philosophers can't communicate beetweenn them
      - Time are in miliseconds
      
    - Bonus : Handle processes and semaphores and optimize use of CPU
      - Same rules than above except :
      - Each philosopher is a process.
      - There is a number of forks equal to the number of philosopher at the center of the table
    
Launch

    - Compile with the makefile
    
    - Mandatory : ./philo <Nb_of_philo> <Time_to_die> <Time_to_eat> <Time_to_sleep> <Number_of_meals_of_each_philo>
      Number_of_meals_of_each_philo : This arguments is optional

    - Bonus : ./philo_bonus <Nb_of_philo> <Time_to_die> <Time_to_eat> <Time_to_sleep> <Number_of_meals_of_each_philo>
      Number_of_meals_of_each_philo : This arguments is optional

Authorized functions

    - Mandatory : 
      - memset, printf, malloc, free, write, usleep, gettimeofday
      - pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
    - Bonus :
      - memset, printf, malloc, free, write, usleep, gettimeofday, exit
      - fork, kill, waitpid
      - pthread_create, pthread_detach, pthread_join
      - sem_open, sem_close, sem_post, sem_wait, sem_unlink

What is forbidden

    - Function lseek
    - Global variables
    - for
    - do ... while
    - switch
    - case
    - goto
    - Ternary operators
    - Variable-size tables

The project must be written in accordance with the 42's Norm
