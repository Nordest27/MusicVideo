# MusicVideo
Here is the code I used to make my song's music video. You can see the result here https://www.youtube.com/watch?v=lQtvpAp8xN0 :) (it gets kind of loud sometimes so beware)

It randomly builds three sets of points from a sphere, then makes chains of cylinders wich every one of the chains is connected to two points. The cylinders in each chain have different sizes, so it gives them a more organic look.

The chains are built so that they follow more or less the surface of the sphere that the points belong to. Then the three spheres are located in the center and resized so that it seems that there is an infinite series of them approaching size 0.

There are many controls that can be used to change the scene. The user can move the camera in 4 directions (up, down, left, right) using WASD, it can move the camera forward or backward using U or Y(forward) and J or K(backward). 
If the camera comes to close to the center it will be moved backwards in a way that the user wont notice it, giving the illusion that it is always approaching the center. 

There are also effects in the shaders activated by pressing certain keys, like distorting the view or changing the light location. It works with the OpenGL and glm libraries and I used https://github.com/opengl-tutorials/ogl 's second tutorial for the skeleton of the program. Also, I used Adam Stark's AudioFile.h code to read the .wav of my song.
