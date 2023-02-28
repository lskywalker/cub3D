# CUB3D by Luke Smit
## PRESENTATION

This project aims at reproducing a basic FPS game by using the raycasting method, similar to Wolfenstein 3D (1992).
The project is made in C language and uses the MLX library as software.

## WANNA PLAY? 💥
### Installation

first, copy paste the following code on your terminal to copy the project:

```shell

git clone https://github.com/lskywalker/cub3D.git cub3D && cd cub3D

```
Now all that's left to do is compile and run the program!

```shell

make bonus && ./cub3D scenes/cub3d_bonus.cub

```

this should open a new window:

<p align = "center">
  <img src ="https://github.com/lskywalker/cub3D/blob/master/img/startposition.png" width="60%" />
</p>

### Controls

| KEY           | Action        |
| ------------- |:-------------:|
| `ESC`         | exit game     |
| `SPACE BAR`   | attack        |
| `A`           | move left     |
| `D`           | move right    |
| `W`           | move forward  |
| `S`           | move backward |
| `→`           | look right    |
| `←`           | look left     |

### The Game

You woke up in a dark and scary maze.
Try to the collect all the coins to get 100 points!
<p align = "center">
  <img src="https://github.com/lskywalker/cub3D/blob/master/img/coinexample.png" width="60%" />
</p>

Watch out for the scary nuns in the maze who will try to kill you if you get too close.
<p align = "center">
  <img src="https://github.com/lskywalker/cub3D/blob/master/img/thenunexample.png" width="60%" />
</p>

If you do encounter a nun you can try to kill it, but becareful! They will hurt you!

### Modifications 👨‍🎨
You can now create your own map by following this norm:
| Object         | Code          |
| -------------  |:-------------:|
| `1`            | wall          |
| `0`            | floor         |
| `2`            | non sprite    |
| `3`            | coin sprite   |
| `N`/`E`/`W`/`S`| player spawn position + orientation|

⚠️ Be careful ! All your paths must be valid and your map must be closed (but not necessarily a square)

You can have a look at the cub3D.pdf file for further details of the project.
