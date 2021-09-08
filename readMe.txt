# dining-philosophers

The c code in this repository is my solutions to a version of the "Dining Philosophers" problem 
originally proposed by the famous computer scientist, Dr. Dijkstra, and proposed to me when I 
took operating systems (CS-3733) at UTSA. The two short bash scripts included were my way of testing 
them more effiecinetly so I decided they would be worth uploading as well. Below, I will explain 
what each program does, and briefly describe how I compile and run these programs. 

PROGRAM DESCRIPTION:

assign4-part1 uses pthread_create() to create a number of threads based on the number passed in as a 
command line arguement. 

assign4-part2 is where we really began solving the problem. First it creates posix mutex locks to 
represent the chopsticks in between the philosophers (again based on the numnber of philosophers 
passed in as a command line parameter). After the chopsticks (mutex locks) have been created the 
philosophers (threads) will begin being created and going through the following cycle. Each philosopher 
thinks for a random amount of time, after which they try to pick up the chopsticks to their left and 
right. Once they have ownership of both locks, they will begin eating for a random amount of time, 
after which they relinquish ownership of the locks. This is a decent solution, but it has it's issues. 
Although it is very unlikely there is still the chance for deadlock, if the philosophers all grab just
one chopstick. This problem is solved in part three. 

Admittedly, assign4-part3 solves the deadlock problem in assign4-part2 in an inefficient way, but none 
the less the problem is solved. It uses a global mutex lock to decide whose turn it is to eat, so only one
philosopher can eat at a time. It also enforces ordered eating (this was part of the assignemnt, seemingly 
because we needed a reason to use conditional variables, and the conditional wait function). 

FUTURE IMPROVEMENTS:
The best improvement to my solution I think would be to figure out how to prevent all deadlock in 
assign4-part2 without enforcing one eating at a time. Now that I've finished the class I would 
think the way to do this is by utilizing the try_lock function and some conditional variable, 
that threads can go to sleep on and be woken up from when other threads finish eating. 

HOW I COMPILE, RUN, AND TEST THESE PROGRAMS:
To compile and run these programs simply download the files, compile them with the gcc compiler,
and run them with the bash scripts. As a side note, I'm fairly certain these programs won't run 
on windows computers. I developed them on a linux server, and I believe there are different thread 
functions for windows. 

