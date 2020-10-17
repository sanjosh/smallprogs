
TODO

x.cos(theta) + y.sin(theta) = r

given bunch of (x,y) pts, find their (r,theta) map
this is a nonlinear map
cartesian --> polar

points which are collinear in the cartesian image space yield curves 
which intersect at a common (r, theta) point. 

Hough transform used to identify param of curve which best fits the pts;

The Hough transform is essentially a histogram. Edge pixels mapping to the same theta and r area assumed to define a line in the image. To compute the frequency of occurrence, theta and r are discretized (partitioned into a number of bins). Once all edge pixels have been converted to polar form, the bins are analyzed to determine the lines in the original image.

http://stackoverflow.com/questions/4709725/explain-hough-transformation

==============

same can be applied to circles, ellipse
