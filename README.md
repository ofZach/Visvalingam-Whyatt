this is a simple example to show off the Visvalingam  algorithm for polyline simplification

http://www2.dcs.hull.ac.uk/CISRG/publications/DPs/DP10/DP10.html

it's not really optimized, but the algorithm is very simple and inituitive, so hopefully this is helpful for people. 

http://bost.ocks.org/mike/simplify/

I use the suggestion from the simplify that talks about using the z value to store info

> One of the best features of Visvalingam’s algorithm is that the effective area can be subsequently stored in the geometry. For example, a point can have a z-coordinate that indicates its effective area, allowing efficient filtering for dynamic simplification even when the algorithm is run on the server. An example of this technique is shown at the top of the page, though more commonly simplification is done based on zoom level.

in my case, I store the order of removal, so that we can dynamically control the amount of of resolution of a line.  (That's hooked up to mouse now).

written for OF 0.8.0, includes an OSX project. 

![image](screenshot.png)