# Negative Z values
* So I was confused about how negative Z works
* My previous thought was that for points with negative Z, therefore behind 
the camera, the basic projection calculation where you just divide by Z should
make the x and y negative, and therefore they won't be drawn to the screen
* When I tested this recently when working with culling this wasn't the case,
which was quite puzzling

* I realized that my previous thoughts were wrong, each obj file contains points
that range roughly from like -1 to 1, and when projected to 2d the coordinates
should have some negative some positive
* The handling of negative values is in the part where point have half of the
window width and height added to them before drawing
* Therefore points with negative x values will be put to the left of the middle
and point with positive x will be put to the right of the middle
    * Same for y
* So by making x and y negative you're just reflecting points about the axes
