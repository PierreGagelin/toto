# What

In this folder lay an example of robot framework usage

- simple file with Settings, Variables, Test Cases and Keywords
- python library

## How to

Robot framework goes with your python environment:

- python3 -m pip install robotframework

I had an issue and required to sudo it... Not sure it's normal

Once it's there, you can just call:

- robot toto.robot

It's quite verbose and intrusive (robot output files, python bytecode...), to disable them:

- PYTHONDONTWRITEBYTECODE=1 robot --output NONE --report NONE --log NONE

Put it in your bashrc, bash_aliases, whatever.
