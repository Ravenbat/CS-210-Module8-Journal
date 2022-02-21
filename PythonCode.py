import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v


def MultiplicationTable(number):
    numbers = [1,2,3,4,5,6,7,8,9,10]
    for each in numbers:
        print("{0} x {1} = {2}".format(number, each, number*each))

def DoubleValue(number):
    return number * 2;

    
