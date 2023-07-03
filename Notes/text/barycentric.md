# Barycentric Coordinates
* Map a point within a triangle to uv coordinates based on the coordinates of the vertices
* Linear interpolation is bad
* Each vertex gets a weight, which are barycentric coordinates
    * Denoted alpha beta gamma
    * The closer the point is to a vertex, the bigger the barycentric coordinate
    that corresponds to that vertex
    * The values of the three can be thought of as the area of triangles formed 
    by pointing from vertices to the point
    * A -> BCP
    * B -> ACP
    * C -> ABP
    * Calculate each coordinate as a ratio of the sub triangle's area over the 
    total area, so they add to one
    * Easier to use cross product to find the paralellogram then divide by double 
    the total area, equivalent expression
    * A = ||PC X PB|| / ||AC X AB||
* Using barycentric coordinates a point in space can be expressed as
P = alpha * A + beta * B + gamma * C
