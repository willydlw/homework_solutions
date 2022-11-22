# Circle Collisions 

For this assignment, all Entities have been given circular Collision components.

## Entity Components that Determine Collision

- Entity Position (x,y)
- Entity Collision Radius (r)


## How to determine Collision?

When the distance between centers of two circles is less than sum of their radii, there is a collision.

**Given two circles**
- C1(x1, y1, r1)
- C2(x2, y2, r2)

**Distance between circles**
- Difference Vector D = (x2 - x1, y2 - y1)
- Distance = sqrt(D.x * D.x, D.y * D.y)

**Collision**
- Distance < (r1 + r2)? Yes

**Optimize Collision Calculation**

Square root operation is computationally expensive.

- Distance Squared = D.x * D.x + D.y * D.y
- Collision = Distance Squared < (r1 + r2) * (r1 + r2)

Multiplication and addition operations computationally faster than square root.


