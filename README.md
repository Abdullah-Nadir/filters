# filters
A program that applies filters to BMPs, per the below.

```
$ ./filter -r IMAGE.bmp REFLECTED.bmp
```

where IMAGE.bmp is the name of an image file and REFLECTED.bmp is the name given to an output image file, now reflected.

## Goals
The goal of this project is to use the command line interface to produce various filtered images, depending on a flag, using C language.

## Features
This project has 4 flags (filters) that can be applied to .bmp images format. 

- Grayscale: This aplies a pure Black and White filter to the chosen image.
- Reflection: This aplies a Reflection filter to the image, so it mirrors all the pixels horizontally.
- Blur: This aplies the "box blur" algorithm to the image, so it mimics a Gaussian Blur.
- Edges: This is a filter that detect edges in the image and highlights it by changing the color of the pixels on the edge and around it. This filter uses the Sobel Operator algorithm to detect edges.


## Usage of the filter.c
As I said before, it's possible to use four flags to run the program:

- `-b`: Blur -> aplies the blur filter to the image.
- `-e`: Edges -> aplies the edges filter to the image.
- `-g`: Grayscale -> aplies the grayscale filter to the image.
- `-r`: Reflection -> aplies the reflection filter to the image.


### Usage

>`./filter -<flag> images/infile.bmp outfile.bmp`

