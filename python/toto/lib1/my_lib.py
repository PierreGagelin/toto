def flib1():
    print("Calling function [package={} ; name={}]".format(
        __name__, flib1.__name__))


class clib1:
    def __init__(self):
        print("Instanciate class [package={} ; name={}]".format(
            __name__, clib1.__name__))
