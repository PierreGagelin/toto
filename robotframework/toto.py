#! /usr/local/bin/python3

from robot.api import logger
import sys

sys.dont_write_bytecode = True


class toto(object):
    """
        Exposed to Robot Framework
    """

    def __init__(self):
        self.bag = []

    def add_to_bag(self, name):
        """
            Add an element to the bag
        """
        entry = random_shit()
        entry.name = name
        self.bag.append(entry)

    def display_bag(self):
        """
            Display the content of the bag
        """
        for entry in self.bag:
            entry.display()


class random_shit(object):
    """
        Some class used internally
    """

    def __init__(self):
        self.name = "uninitialized shit"

    def display(self):
        logger.debug(self.name)
