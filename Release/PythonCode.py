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
    return 0

def DoubleValue(number):
    return number * 2;

def TimesEachItemAppear():
    totalDict = {}
    itemCounter = open('InputFile.txt', 'r')
    itemList = itemCounter.readlines()

    for each in itemList:
        totalDict[each.replace("\n", "")] = itemList.count(each) 

    itemCounter.close()

    for keys in totalDict:
        print("{} : {}".format(keys, totalDict[keys]))

def TimesOneItemAppear(item):
    totalDict = {}
    itemCounter = open('InputFile.txt', 'r')
    itemList = itemCounter.readlines()

    for each in itemList:
        totalDict[each.replace("\n", "")] = itemList.count(each) 

    itemCounter.close()
    return totalDict[item.capitalize()]

def OutputFrequency():
    totalDict = {}
    itemCounter = open('InputFile.txt', 'r')
    itemList = itemCounter.readlines()

    for each in itemList:
        totalDict[each.replace("\n", "")] = itemList.count(each)

    itemCounter.close()
    frequency = open('frequency.dat', 'w')
    
    for keys in totalDict:
        frequency.write("{} {}\n".format(keys, totalDict[keys]))

    frequency.close()



    
