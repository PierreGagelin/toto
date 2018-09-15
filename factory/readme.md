
# Context
This folder holds a test of factory to register a derived class constructor. The main goal is to:
- define a known base class
- being able to create unknown derived class

# How
- A global factory is defined in the main translation unit
- Unknown derived class can be declared in an other translation unit
- Unknown derived class are registered in the factory through the instance of a global in the other translation unit
- In this way, the main translation unit is able to create and destroy unknown derived class

# Problem
It works fine with shared libraries. However when linking the library statically, it seems that translations units aren't pulled

# Solution
Passing the --whole-archive option to the linker for the static library seems to do the trick, but I'm not fond of it
