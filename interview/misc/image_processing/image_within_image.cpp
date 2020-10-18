
assume black & white
Bitmaps are just laid out as a string (change stride length)

Basic method would be 2D string matching - create suffix array

if first char of pattern is "0" and mismatch
shift right to next "0"
shift down to next "0"

================
watershed algo
================

http://en.wikipedia.org/wiki/Template_matching

USe image pyramid (multi-resolution)

create a K-d tree in 2 dims which has the edge points

Use freq domain matching

Use scale-invariant feature transform(SIFT) : generate feature vectors which are invariant under transformations (scaling, rotation, translation)

Convolution with a filter = comparing patern with little regions of what u want to find.  Derivative of Gaussian.


================
Corners are reliable -detect them using 2 methods
(1) Harris corner detection
(2) Shi and Tomasi min eigenvalue method
both use eigenvalue of summation of squared difference matrix (SSD)
which represent diff between surrounding(pixel) and surrounding(neighbours)
larger the diff, larger the eigenvalue, and more likely pixel is at corner

SSD is one similarity measure - there are others.

================

Edge detection: change of intensity
Canny method
first derivative is high
second derivative has zero crossing
================

Line detection: Hough transform 
r = x.cos(theta) + y.sin(theta)
get new diagram in (theta, r) space
use peaks in this space to find potential lines.
then find endpoints of the lines

Radon transform
