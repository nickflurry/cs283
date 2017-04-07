//
// Created by Stephen Slatky on 3/16/17.
//

./sdriver.pl -t trace01.txt -s ./tsh -a "-p"
#
# trace01.txt - Properly terminate on EOF.
#
./sdriver.pl -t trace02.txt -s ./tsh -a "-p"
#
# trace02.txt - Process builtin quit command.
#
./sdriver.pl -t trace03.txt -s ./tsh -a "-p"
#
# trace03.txt - Run a foreground job.
#
tsh> quit
./sdriver.pl -t trace04.txt -s ./tsh -a "-p"
#
# trace04.txt - Run a background job.
#
tsh> ./myspin 1 &
[1] (24010) ./myspin 1 &
./sdriver.pl -t trace05.txt -s ./tsh -a "-p"
#
# trace05.txt - Process jobs builtin command.
#
tsh> ./myspin 2 &
[1] (24014) ./myspin 2 &
tsh> ./myspin 3 &
[2] (24016) ./myspin 3 &
tsh> jobs
[1] (24014) Running    ./myspin 2 &
[2] (24016) Running    ./myspin 3 &
./sdriver.pl -t trace06.txt -s ./tsh -a "-p"
#
# trace06.txt - Forward SIGINT to foreground job.
#
tsh> ./myspin 4
Job [1] (24021) terminated by signal 2
./sdriver.pl -t trace07.txt -s ./tsh -a "-p"
#
# trace07.txt - Forward SIGINT only to foreground job.
#
tsh> ./myspin 4 &
[1] (24025) ./myspin 4 &
tsh> ./myspin 5
Job [2] (24027) terminated by signal 2
tsh> jobs
[1] (24025) Running    ./myspin 4 &
./sdriver.pl -t trace08.txt -s ./tsh -a "-p"
#
# trace08.txt - Forward SIGTSTP only to foreground job.
#
tsh> ./myspin 4 &
[1] (24032) ./myspin 4 &
tsh> ./myspin 5
Job [2] (24034) stopped by signal 20
tsh> jobs
[1] (24032) Running    ./myspin 4 &
[2] (24034) Stopped    ./myspin 5 
./sdriver.pl -t trace09.txt -s ./tsh -a "-p"
#
# trace09.txt - Process bg builtin command
#
tsh> ./myspin 4 &
[1] (24039) ./myspin 4 &
tsh> ./myspin 5
Job [2] (24041) stopped by signal 20
tsh> jobs
[1] (24039) Running    ./myspin 4 &
[2] (24041) Stopped    ./myspin 5 
tsh> bg %2
[2] (24041) ./myspin 5 
tsh> jobs
[1] (24039) Running    ./myspin 4 &
[2] (24041) Running    ./myspin 5 
./sdriver.pl -t trace10.txt -s ./tsh -a "-p"
#
# trace10.txt - Process fg builtin command. 
#
tsh> ./myspin 4 &
[1] (24048) ./myspin 4 &
tsh> fg %1
Job [1] (24048) stopped by signal 20
tsh> jobs
[1] (24048) Stopped    ./myspin 4 &
tsh> fg %1
tsh> jobs
./sdriver.pl -t trace11.txt -s ./tsh -a "-p"
#
# trace11.txt - Forward SIGINT to every process in foreground process group
#
tsh> ./mysplit 4
Job [1] (24056) terminated by signal 2
tsh> /bin/ps a
  PID TTY      STAT   TIME COMMAND
16955 pts/10   S      0:00 -tcsh
23999 pts/10   S      0:00 make tests
24053 pts/10   S      0:00 perl ./sdriver.pl -t trace11.txt -s ./tsh -a -p
24054 pts/10   S      0:00 ./tsh -p
24059 pts/10   R      0:00 /bin/ps a
./sdriver.pl -t trace12.txt -s ./tsh -a "-p"
#
# trace12.txt - Forward SIGTSTP to every process in foreground process group
#
tsh> ./mysplit 4
Job [1] (24063) stopped by signal 20
tsh> jobs
[1] (24063) Stopped    ./mysplit 4 
tsh> /bin/ps a
  PID TTY      STAT   TIME COMMAND
16955 pts/10   S      0:00 -tcsh
23999 pts/10   S      0:00 make tests
24060 pts/10   S      0:00 perl ./sdriver.pl -t trace12.txt -s ./tsh -a -p
24061 pts/10   S      0:00 ./tsh -p
24063 pts/10   T      0:00 ./mysplit 4
24064 pts/10   T      0:00 ./mysplit 4
24067 pts/10   R      0:00 /bin/ps a
./sdriver.pl -t trace13.txt -s ./tsh -a "-p"
#
# trace13.txt - Restart every stopped process in process group
#
tsh> ./mysplit 4
Job [1] (24071) stopped by signal 20
tsh> jobs
[1] (24071) Stopped    ./mysplit 4 
tsh> /bin/ps a
  PID TTY      STAT   TIME COMMAND
16955 pts/10   S      0:00 -tcsh
23999 pts/10   S      0:00 make tests
24068 pts/10   S      0:00 perl ./sdriver.pl -t trace13.txt -s ./tsh -a -p
24069 pts/10   S      0:00 ./tsh -p
24071 pts/10   T      0:00 ./mysplit 4
24072 pts/10   T      0:00 ./mysplit 4
24075 pts/10   R      0:00 /bin/ps a
tsh> fg %1
tsh> /bin/ps a
  PID TTY      STAT   TIME COMMAND
16955 pts/10   S      0:00 -tcsh
23999 pts/10   S      0:00 make tests
24068 pts/10   S      0:00 perl ./sdriver.pl -t trace13.txt -s ./tsh -a -p
24069 pts/10   S      0:00 ./tsh -p
24078 pts/10   R      0:00 /bin/ps a
./sdriver.pl -t trace14.txt -s ./tsh -a "-p"
#
# trace14.txt - Simple error handling
#
tsh> ./bogus
./bogus: Command not found
tsh> ./myspin 4 &
[1] (24084) ./myspin 4 &
tsh> fg
fg command requires PID or %jobid argument
tsh> bg
bg command requires PID or %jobid argument
tsh> fg a
fg: argument must be a PID or %jobid
tsh> bg a
bg: argument must be a PID or %jobid
tsh> fg 9999999
(9999999): No such process
tsh> bg 9999999
(9999999): No such process
tsh> fg %2
%2: No such job
tsh> fg %1
Job [1] (24084) stopped by signal 20
tsh> bg %2
%2: No such job
tsh> bg %1
[1] (24084) ./myspin 4 &
tsh> jobs
[1] (24084) Running    ./myspin 4 &
./sdriver.pl -t trace15.txt -s ./tsh -a "-p"
#
# trace15.txt - Putting it all together
#
tsh> ./bogus
./bogus: Command not found
tsh> ./myspin 10
Job [1] (24101) terminated by signal 2
tsh> ./myspin 3 &
[1] (24103) ./myspin 3 &
tsh> ./myspin 4 &
[2] (24105) ./myspin 4 &
tsh> jobs
[1] (24103) Running    ./myspin 3 &
[2] (24105) Running    ./myspin 4 &
tsh> fg %1
Job [1] (24103) stopped by signal 20
tsh> jobs
[1] (24103) Stopped    ./myspin 3 &
[2] (24105) Running    ./myspin 4 &
tsh> bg %3
%3: No such job
tsh> bg %1
[1] (24103) ./myspin 3 &
tsh> jobs
[1] (24103) Running    ./myspin 3 &
[2] (24105) Running    ./myspin 4 &
tsh> fg %1
tsh> quit
./sdriver.pl -t trace16.txt -s ./tsh -a "-p"
#
# trace16.txt - Additional test for signal handlers
#
tsh> ./mystop 2
Job [1] (24117) stopped by signal 20
tsh> jobs
[1] (24117) Stopped    ./mystop 2
tsh> ./myint 2
Job [2] (24120) terminated by signal 2