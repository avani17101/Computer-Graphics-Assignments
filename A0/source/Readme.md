## Computer Graphics A0

Submitted by: Avani Gupta
2019121004


## Shapes implemented

* shape1: hexgonal dipyramid
* shape2: decagonal prism
* shape3: undecagonal pyramid

## Instructions to run
* Compiling and running
```bash
g++ shape1.cpp -o shape1 -lGL -lGLU -lglut
./shape1
```

```bash
g++ shape2.cpp -o shape2 -lGL -lGLU -lglut
./shape2
```

```bash
g++ shape3.cpp -o shape3 -lGL -lGLU -lglut
./shape3
```

## Key controls
* move object around one of axis
a, b ,c , l, m, n -> move object along x, y, z axis respectively
a, b, c -> move object in positive x, y, z axis
l, m, n -> move object in negative x, y, z axis 

 
* object spin around any one axis
x, y, z -> spin around respective x, y, or z

* camera spin around object -> v
   
* change camera positions
p, q, s -> move camera along positive x, y, z axis respectively
e, f, g ->  move camera along negative x, y, z axis respectively

* move to pre-decided positions of camera
d, o, j

* stop spinning -> r  
* start spinning again -> r followed by x/y/z


## Method
I move in anti-clockwise direction across coordinates to make eigther triangle/ quadrilateral in glut.

 Now, for calculating coordinates of shapes, I used simple geometry and coded a python script (genCoords.ipynb) for the same.

