#!/usr/bin/python

import argparse
from random import randint
import collections

unique = collections.namedtuple('unique', ['set', 'val'])


def generateUnique(s, d, t):
    val = randint(d, t)
    while val in s:
        val = randint(d, t)
    s = s.union({val})
    return unique(s, val)


parser = argparse.ArgumentParser(description='FEITIR tool for generating test sets')
parser.add_argument('-t', '--topIdx',
                    help='Maximum value of generated index - number of elements in your database',
                    required=True)
parser.add_argument('-d', '--downIdx',
                    help='Minimum value of generated index',
                    default=0)
parser.add_argument('-a', '--aSetFile',
                    help='filename for A set',
                    default='a.set')
parser.add_argument('-b', '--bSetFile',
                    help='filename for B set',
                    default='b.set')
parser.add_argument('-as', '--aSize',
                    help='size of A set',
                    required=True)
parser.add_argument('-bs', '--bSize',
                    help='size of B set',
                    required=True)

args = parser.parse_args()

aFile = open(args.aSetFile, 'w')
bFile = open(args.bSetFile, 'w')

generatedNumbers = set()

for a in xrange(0, int(args.aSize)):
    u = generateUnique(generatedNumbers, int(args.downIdx), int(args.topIdx))
    generatedNumbers = u.set
    aFile.write('{}\n'.format(u.val))

for b in xrange(0, int(args.bSize)):
    u = generateUnique(generatedNumbers, int(args.downIdx), int(args.topIdx))
    generatedNumbers = u.set
    bFile.write('{}\n'.format(u.val))

assert len(generatedNumbers) == (int(args.bSize) + int(args.aSize))
