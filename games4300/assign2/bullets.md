Shooting Bullets From Player to Mouse 

Given speed scalar S, how do we get speed vector?

Distance between player and mouse: D = (mx - px, my - py)

Distance has length L (magnitude) and we need to scale that to S 

Normalize the distance vector N = (D.x/L, D.y/L) 

The normalized vector has length 1.

The scaled velocity vector Vel = (S * N.x, S * N.y)


Alternatively we can use trigonometry to calculate the velocity vector

D = (mx - px, my - py)

D has angle theta = atan2f(D.y, D.x)

Velocity vector Vel = (S * cos(theta), S * sin(theta))