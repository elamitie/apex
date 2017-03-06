# README #

A relatively simple 3D Rendering Engine I am working on for a portfolio class.

### Building ###
* Just pull the repository and run build_vs2015.bat
* CMake will generate a visual studio project in the resulting build folder.
* Binaries are in the Debug folder inside the visual studio folder.
* NOTE: When isolating the executables, the resources folder needs to be copied one directory above the binaries.

### Assets ###
* There are texture and shader folders in the resources folder. 
* Unless manually creating cubes and spheres (which you can do with raw gl calls in this engine, they are exposed),
* all textures should go in the same directory as your model in the Models folder.

### Extending ###
* The entry point to the engine is within the child class of `engine`
* In the demo project, this can be seen in the app folder, were there is the `application` class that inherits from `engine`.

### Author ###

* elamitie@gmail.com
* elamitie.wordpress.com (website)