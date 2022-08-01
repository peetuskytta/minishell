# minishell

Minishell is the second project from the Unix-branch at Hive Helsinki coding school.

### STATUS = ongoing

![Screenshot 2022-07-30 at 17 00 03](https://user-images.githubusercontent.com/77061872/181917866-8a5cdf4d-4bbb-4191-99f3-e703eb9490aa.png)

## Introduction

First step in the creation of a shell. In this project, I will create a "mini-shell" capable of reading and evaluating simple user commands. 
Reading will involve trivial lexical analysis and parsing of the command. The program will, for example, involve searching for the corresponding 
binary on the machine and execute it, or execute the relevant code in the case of a “built-in” command in the shell.

So basically it's about coding a minimally functional `command prompt interpreter` aka `minishell`.

### Objectives:

- read and parse user input into commands and arguments.
- to handle expansions `$` and `~`.
- corect handling of the environment (`char **environ`) and `$PATH`.

#### Learnings (so far)

- I learned from my previous projects that I needed to plan ahead before actually starting to write code. So...

  - I began this project by reading and taking notes of the man pages for the system calls and allowed functions. By reading the manual I was already
able to put some ideas on paper on how the program should behave and how to organize the data collected from user input and what to do with the
environment variables.
  - I used about a week only reading, writing, and sketching on paper how to start the project.

- When I decided to start the project it was easier as I had a plan which included:
  - How to organize data (structs, arrays, linked list, etc..).
  - How to write basic interpreter which can be expanded (needs to be done for quotes in input).
  - How to start writing functions to create a child process in case binary is needed.
  - How to write the required built-ins for the project: `env`, `setenv`, `unsetenv`, `cd`, `pwd`, ´exit´.
  
 - I underestimated the complexity of quoting and parsing of input (July 20th 2022).
 
 #### Successes
 
 - no memory leaks in the `setenv`, `env`, `unsetenv` and `exit` builtins.
 
 ### TODO
 
 - cd, pwd
 - permission check for the whole path to a binary
 - quoting detection
 - expansion
