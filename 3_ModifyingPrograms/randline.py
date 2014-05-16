#!/usr/bin/python

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, lines,numlines,unique,wreplace):
        self.lines = lines
        self.unique = unique
        if self.unique:
            self.lines = list(set(self.lines))
        self.wreplace = wreplace
        self.numlines = numlines
        
    def chooseline(self):
        curLine = random.choice(self.lines)
        if self.wreplace:
            self.lines.remove(curLine)
        return curLine


def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION] [OPTION] [OPTION]... FILE

Output randomly selected lines from FILE. Use -u for unique and -w for no line replacment."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--numlines",
                      action="store", dest="numlines", default=1,
                      help="output NUMLINES lines (default 1)")
    parser.add_option("-u", "--unique",action="store_true",
		dest="unique",default=False,
            	help="unique lines from file only")
    parser.add_option("-w","--without_replacement",action="store_true",
		dest="without_replace",
                default=False,help="without replacement option")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        numlines = int(options.numlines)
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
    unique = options.unique
    wreplace = options.without_replace

    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    if len(args) < 1:
        parser.error("not enough operands")
    alllines = []
    for x in range(len(args)):
        f=open(args[x])
        lines = f.readlines()
        for j in range(len(lines)):
            alllines.append(lines[j])
    try:
        generator = randline(alllines,numlines,unique,wreplace)
        for index in range(numlines):
            sys.stdout.write(generator.chooseline())
    except IOError as err:
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))
if __name__ == "__main__":
    main()
