# Distributed Raytracer
An object-oriented, multithreaded, distributed raytracer written in C++.

## Features
* Atomic shapes
  * Sphere
  * Plane
  * Quad
  * Triangle
* Triangle Meshes, including .ply parsing
* Texture Mapping
* Distributed Raytracing
  * Area lights w/ soft shadows
  * Thin lens w/ adjustable aperture
* Multiple Samplers
  * Grid based sampling
  * Jittered-grid based sampling
* Json input parsing
* Bounding cubes
* Suboptimal multithreading

## Example images

![Image of texture mapped planets](https://scontent-lhr8-1.xx.fbcdn.net/v/t1.15752-9/73302617_1015980858742248_6017589596508913664_n.png?_nc_cat=109&_nc_ohc=3r-w29DoFSEAX88r3yd&_nc_ht=scontent-lhr8-1.xx&oh=96fa1aa9beef50aabd8f808655016f31&oe=5EC72EC2)

## Future Work
* Full bounding volume hierarchy
* Global illumination via rendering equation
* Optimizations and bugfixing
