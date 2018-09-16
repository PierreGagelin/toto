
# Goal
This folder holds a test of factory to register a derived class constructor. The main goal is to:
- define a known base class
- being able to create unknown derived class

# How
## Method 1
- A global factory is defined in the main translation unit
- Unknown derived class can be declared in an other translation unit
- Unknown derived class are registered in the factory through the instance of a global in the other translation unit
- In this way, the main translation unit is able to create and destroy unknown derived class
## Method 2
- Each derived class exposes a two-functions interface (create / destroy) with specific named convention
- Main translation unit can dlopen itself to retrieve those interfaces

# Problem
It works fine with shared libraries. However when linking the library statically, it seems that translations units aren't pulled

# Solution
Passing the --whole-archive option to the linker for the static library can force it to retrieve every translation units
