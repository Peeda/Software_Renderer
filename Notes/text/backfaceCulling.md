# Backface Culling
* Backface culling aims to optimize rendering by not rendering faces that
point away from the camera
* Vertex order in a face should be clockwise when the face points towards
the camera
* Faces that point away are usually not visible so you can just not render
## Calculating Where a Face Points
* We can easily tell whether or not a face points away from the camera by 
looking at the angle between the ray that shoots out of the camera towards 
the some point on the face and the normal of the face
* If this angle is 90 it means the face is parallel to the camera and 
is therefore just a line
* If this angle is <90 the face is pointing towards the camera and will be
rendered
* If this angle is >90 the face is pointing away and should not be rendered
## Calculating the angle
* The normal vector of some triangle face ABC can be found by crossing 
vectors AB and AC, the magnitude information doesn't matter
* We subtract the point on the face from the camera position because the
whole angle between stuff for the dot product assumes the origins of the
rays are together and they point away from each other
    * Therefore to find the angle between the ray that comes from the cam
    to the point and the normal we should find the ray that comes from the
    face to the camera, and dot that one with the normal
    * Any point can be used since the normal vector is the same for all points
    on the face and so any ray from the camera to the face should work
* From here we have a vector for the ray and a vector for the normal and must
calculate whether the angle between is greater or less than 90
* Dotting the two vectors then looking at the sign is a quick way to do this,
since output is |A||B|cos(theta) and therefore the sign indicates angle info
* If the output is positive theta is in quadrants one or four
* If the output is negative theta is in quadrants two or three
* Therefore the face is rendered if the dot product is positive, as the angle
between the two vectors is less than ninety degrees

# Why the camera had to be moved to the origin
* When the camera was at {0,0,-5} and points were translated in the z according
to the camera position, it caused some issues with culling
* Faces would display for a brief period before being culled, so you could see
faces that you shouldn't be able to see for brief periods
* The fix was to change the camera to {0,0,0} and change the transformation
function to just add five to the z coordinate for scaling
* Before the fix was implemented the ray from the camera to the face would
count the z distance as 10, since the point had already been translated by 5
in the z, and the camera was still at z = -5
* With the basic projection implemented right now z really only functions as a
scaling factor for x and y the same way the FOV does
