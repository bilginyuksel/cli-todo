# cli-todo
Manage your To-do list very easily from CLI. You can save your to-dos in a structural way. cli-todo is very useful, easy to use and fast tool.

### UNIX
```bash
$ git clone https://github.com/bilginyuksel/cli-todo.git
$ cd cli-todo/init/
$ ./dbw
$ cd ..
$ sudo mv tod /bin/  ## Optional if you want to use the application from any directory.
```
### WINDOWS
You can set up the application from terminal or UI.
```terminal
> git clone https://github.com/bilginyuksel/cli-todo.git
> cd cli-todo/
> git branch support/windows
> git pull origin support/windows
> git checkout support/windows
> cd init/
> ./dbw
## Set up environment variables for tod.exe...
```
Download the windows release version from github. Double click dbw.exe file in cli-todo/init folder. Then set the environment variables for tod.exe.

_All finished. Now you can start using the application._

#### Example Usage..
```bash
$ tod branch demo # create a demo branch
$ tod branch # list branches
$ tod checkout demo # switch to demo branch
$ tod note -t "Hello my new note!" -i 1 --description "Description to my note" # create a note
$ tod note -l # list all notes
$ tod category -t Personal # create a category
$ tod category -l # list categories
$ tod note -t "New note with category" -i 2 -c Personal # created a new note
$ tod note -l -d # detailed note list
$ tod category -di Personal # category info
$ tod note -f 1 # make todo status done
$ tod note -l # list notes
$ tod checkout master
$ tod branch --delete demo # Can't delete because undone todos exists.
$ tod branch -D demo # forced delete.
``` 


