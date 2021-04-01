## Assignment 1: Among us Game


## Instructions to run

* Running the precompiled code <br>

```bash
cd src
```

```bash
./Hello-World 
```
* Compiling and running <br>

```bash
bash compilefull.sh
```

```bash
cd src
```
```bash
./Hello-World
```


## Playing the game

* Press up, down top, left arrow keys to move the player up, down, top, bottom.
* Press WASD for moving camera in respective top, left, bottom, right directions.

## Two Tasks

* Task 1:  Vapourise the enemy by finding the vapourise button (white color) in the game.
* Task 2: Unlock obstacles(powerups, lives, fire) by locating the Tresure (tresure symbol) in the game. The move around and collect the powerups and lives. You are done if you collect two or more powerups and two or more lives!

### Game instructions/rules.
	* Collecting life increases health.
	* Collecting powerup increases score/time.
	* Colliding with fire decrease score/time.
	* Colliding with enemy(imposter) ends the game. The enemy follows shortest path 		algorithm(bfs here) for tracing you.
	

You must complete both the tasks before the time ends. If the time ends you loose. <br>


You have a HUD Display which indices lives(Heart), tasks completed(tick marks), light(on/off bulb) and time left(score). <br>
Your score decreases with time or colliding with fire and increases on collecting powerups/life.

There is a light which will guide you as you move on in the game(some parts of game will light up while rest will be dark).

The game starts with dark by defualt with a small light guiding you as you move forward(based on distance the lighting of objects will change)

