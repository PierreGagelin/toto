#
#   Main file for various python tests units
#


def tu_import():
    """
    Test Unit

    Verify excepted availability
    """

    import momo
    import toto.all as toto

    try:
        print("Compare module local and real name [local={} ; real={}]".format("toto", toto.flib1.__module__))
        print("Compare module local and real name [local={} ; real={}]".format("toto", toto.flib2.__module__))
        print("Compare module local and real name [local={} ; real={}]".format("toto.custom", toto.custom.flib3.__module__))

        toto.flib1()
        toto.flib2()
        toto.custom.flib3()

        toto.clib1()
    except:
        print("FAILED: these are supposed to be available")
        return 1

    try:
        momo.momo.momo()
        print("FAILED: these are not supposed to be available")
        return 1
    except:
        print("Expected exception [package={}]".format(momo.__name__))
        pass

    return 0


if __name__ == "__main__":
    import sys

    rc = tu_import()
    sys.exit(rc)
