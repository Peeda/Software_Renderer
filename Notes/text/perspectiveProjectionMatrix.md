https://learnwebgl.brown37.net/08_projections/projections_perspective.html
https://scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix.html
https://cseweb.ucsd.edu/classes/wi18/cse167-a/lec4.pdf
https://www.youtube.com/watch?v=U0_ONQQ5ZNM

# The Current Projection Implementation
* Translate points away by five in the Z
* Divide x and y by z, perspective divide
* Scale and translate arbitrarily to fit to screen

# Perspective Projection Matrix
* Accounts for FOV and aspect ratio
    * Bigger FOV scales down the image size
    * Different aspect ratios warp in similar fashion
    * Making the aspect ratio wider stretches images into the center
* Remaps Z values to a range from 0 to 1, in a nonlinear fashion
    * More weight is placed towards smaller Z values (closer to camera) which
    helps remedy z fighting
* After these transformations are applied perspective divide and scaling is applied
