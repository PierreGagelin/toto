#
#   Try different ways to import a package
#       1. Give a flat access to the lib1.my_lib (no __init__.py required)
#       2. Let lib2 specify what access to give (see lib2/__init__.py)
#       3. Give an access to toto.lib3.mylib as toto.lib3 (no __init__.py required)
#

from ..lib1.my_lib import *
from ..lib2 import *
from ..lib3 import my_lib as custom

print("Importing package [name={}]".format(__name__))
