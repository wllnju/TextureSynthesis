TextureSynthesis
================
This project uses two single-resolution method to synthesize texture.
One is Wei's exhaustive search algorithm under the folder "WLalgorithm".
The other one is Ashikhmin's candidate search algorithm under the folder "candidate".
For each method, there is a folder called "results" (under the folder"WLalgorithm" and the folder "candidate") which used to store the synthesized images.

The folder "images" stores the texture samples (input image) which can be used to synthesize texture.

If you want to run the code, please choose the method you want to use and go to the corresponding folder (the folder "WLalgorithm" or the folder "candidate" ), compile and execute for some image in the "images" folder. For example,
 
cd WLalgorithm

make

./texture ../images/greencells.jpg

It will produce the synthesized image for input file "../images/greencells.jpg" with user-defined output size and different window_size which can be modified by user in the beginning of the main.cpp.
