#
#   - File only here for pylint no to be lost in packages, if
#     not here, all/__init__.py think it goes out-of-package during its imports
#   - As it's there, I use it to point out that python loads it even if
#     there's no one referencing it directly (toto.all is referenced though)
#

print("Importing package [name={}]".format(__name__))
