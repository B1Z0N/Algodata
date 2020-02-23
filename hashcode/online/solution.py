#!/bin/python
import os
import sys
from typing import Set
from pprint import pprint
from texttable import Texttable
from dataclasses import dataclass

ROWS, COLS = [int(i) for i in os.popen('stty size', 'r').read().split()]
INPUT_DIR = 'input/'
OUTPUT_DIR = 'output/'


def choose_file() -> str:
    inp_files = os.listdir(INPUT_DIR)
    prom = '\n'.join(
        f'{i}) {fname}'
        for i, fname in enumerate(inp_files)
    ) + '\nSelect number: '

    try:
        file_idx = int(input(prom))
        fname = inp_files[file_idx]
        contents = open(os.path.join(INPUT_DIR, inp_files[file_idx]), 'r')
        return contents
    except Exception as e:
        print('Bruh...')
        sys.exit(1)



@dataclass
class Library:
    book_count: int
    signup_days: int
    max_per_day: int
    book_ids: Set[int]

    def __repr__(self):
        return f'{self.book_count} books, \
{self.signup_days} signup_days, \
{self.max_per_day} days to signup;\n\
books: {self.book_ids}'


def parse():
    contents = choose_file()

    books_num, libraries_num, days_num = [
        int(s)
        for s in contents.readline().split(' ')
    ]

    book_scores = [int(b) for b in contents.readline().split(' ')[:books_num]]
    book_scores = [(score, i) for i, score in enumerate(book_scores)]

    libraries = []

    for _ in range(libraries_num):
        books_num, signup_days, max_per_day = [
            int(x)
            for x in contents.readline().split(' ')
        ]
        book_ids = set(int(b) for b in contents.readline().split(' ')[:books_num])
        libraries.append(
            Library(books_num, signup_days, max_per_day, book_ids)
        )
    return (days_num, book_scores, libraries)


def main():
    days_num, book_scores, libraries = parse()
    print(days_num)
    print(book_scores)
    print(libraries)
    book_scores.sort()
    print(solve(days_num, book_scores, libraries))


def solve(days : int, books : list, libraries : list):
    if days < 0 or not books or not libraries:
         return []
    selected_lib = None
    for lib in libraries:
        if books[0][1] in lib.book_ids:
            selected_lib = lib
            break

    if selected_lib is not None:
        new_days = days - selected_lib.signup_days # !!
        libraries.remove(selected_lib)
        solution = list(selected_lib.book_ids)
        return solution.extend(
            solve(
                new_days, list(
                    filter(lambda book: book[1] in selected_lib.book_ids, books)
                    ), libraries
                )
        )
    
    return []


if __name__ == '__main__':
    main()
