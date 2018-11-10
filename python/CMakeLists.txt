

configure_file(main.py main.py COPYONLY)
configure_file(momo/momo.py momo/momo.py COPYONLY)
configure_file(toto/__init__.py toto/__init__.py COPYONLY)
configure_file(toto/all/__init__.py toto/all/__init__.py COPYONLY)
configure_file(toto/lib1/my_lib.py toto/lib1/my_lib.py COPYONLY)
configure_file(toto/lib2/__init__.py toto/lib2/__init__.py COPYONLY)
configure_file(toto/lib2/my_lib.py toto/lib2/my_lib.py COPYONLY)
configure_file(toto/lib3/my_lib.py toto/lib3/my_lib.py COPYONLY)

add_test(NAME tu_python COMMAND python3 main.py)
