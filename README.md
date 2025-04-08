# shellsnake
a minimalistic snake game for the shell coded in c.  
With this project, I wanted to practice using two-dimensional arrays.
I also learned how to use the ncurses library, which allows capturing user input continuously while the program is running.  
This program was coded on Linux and may not function correctly on Windows.

see html/index.html for documentation

## Versions

There are two versions:

- A **minimalistic** one, which is highly customizable -> 📁 [**Minimalistic**](https://github.com/tristangnl/shellsnake/tree/main/minimalistic)
- The **second** one, where I've added some features and styles -> **📁 Upgraded**

## Look
The minimalistic game looks like this

```
X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X  
X                                                           X  
X                                                           X  
X                                                           X  
X                                                           X  
X                         o o o o o o >     @               X  
X                         o                                 X  
X                         o                                 X  
X                         o o o o o                         X  
X                                 o                         X  
X                                 o                         X  
X                     o o o o o o o                         X  
X                                                           X  
X                                                           X  
X                                                           X  
X                                                           X  
X                                                           X  
X                                                           X  
X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X  
```

### Controls

* minimalistic :
  * **Arrows** : Move
  * **escape** : Exit

* upgraded :
  * **Arrows** : Select / Move
  * **q** : Return / Exit
  * **space / Enter** : Choose

> [!TIP]  
> You can adjust the shell font size using `Ctrl` + `+` or `Ctrl` + `-`.



### Installation
clone this repo and run ```./ShellSnake``` in the terminal on linux to play

### Compilation
with gcc:

```gcc -Wall shellsnake.c testshellsnake.c -o ShellSnake -lncurses```
  
> [!IMPORTANT]  
> Don't forget to link the ncurses library using ```-lncurses```.  
> You must have the ncurses packages installed first.

