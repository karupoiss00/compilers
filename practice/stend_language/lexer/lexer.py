from lexer.temp_token_provider import get_token as get_token_from_temp_token_provider
import re

START = 0
FINISH = 1
CONST = 2
NOC = 3
VAR = 4
RAV = 5
STRING_TYPE = 6
INT_TYPE = 7
FLOAT_TYPE = 8
BOOLEAN_TYPE = 9
CHAR_TYPE = 10
DIV = 11
MOD = 12
NOT = 13
IF = 14
THEN = 15
FI = 16
ELSE = 17
WHILE = 18
DO = 19
EL = 20
FOR = 21
TO = 22
DO = 23
ROF = 24
OR = 25
ASSIGN = 26
SEMICOLON = 27
IDENTIFIER = 28
FLOAT = 29
NUMBER = 30
STRING = 31
CHAR = 32
LPAREN = 33
RPAREN = 34
LBRACKET = 35
RBRACKET = 36
STAR = 37
PLUS = 38
MINUS = 39
SLASH = 40

LEXEMS = [
    ['START', r'^\bSTART\b', START],
    ['FINISH', r'^\bFINISH\b', FINISH],
    ['CONST', r'^\bCONST\b', CONST],
    ['NOC', r'^\bNOC\b', NOC],
    ['VAR', r'^\bVAR\b', VAR],
    ['RAV', r'^\bRAV\b', RAV],
    ['String', r'^\bString\b', STRING_TYPE],
    ['Int', r'^\bInt\b', INT_TYPE],
    ['Float', r'^\bFloat\b', FLOAT_TYPE],
    ['Boolean', r'^\bBoolean\b', BOOLEAN_TYPE],
    ['Char', r'^\bChar\b', CHAR],
    ['div', r'^\bdiv\b', DIV],
    ['mod', r'^\bmod\b', MOD],
    ['not', r'^\bnot\b', NOT],
    ['if', r'^\bif\b', IF],
    ['then', r'^\bthen\b', THEN],
    ['fi', r'^\bfi\b', FI],
    ['else', r'^\belse\b', ELSE],
    ['while', r'^\bwhile\b', WHILE],
    ['do', r'^\bdo\b', DO],
    ['el', r'^\bel\b', EL],
    ['for', r'^\bfor\b', FOR],
    ['to', r'^\bto\b', TO],
    ['do', r'^\bdo\b', DO],
    ['rof', r'^\brof\b', ROF],
    ['or', r'^\bor\b', OR],
    [':=', r'^:=', ASSIGN],
    [';', r'^;', SEMICOLON],
    ['identifier', r'^\b[a-zA-Z_]+\b', IDENTIFIER],
    ['float', r'^\d+\.\d+', FLOAT],
    ['number', r'^\d+', NUMBER],
    ['string', r'^\".*\"', STRING],
    ['char', r'^\'.*\'', CHAR],
    ['(', r'^\(', LPAREN],
    [')', r'^\)', RPAREN],
    ['[', r'^\[', LBRACKET],
    [']', r'^\]', RBRACKET],
    ['*', r'^\*', STAR],
    ['+', r'^\+', PLUS],
    ['-', r'^\-', MINUS],
    ['/', r'^\/', SLASH]
]


with open('input.txt', 'r') as f:
    lines = f.readlines()
    for line in lines:
        while line:
            line = line.strip()
            for lexem in LEXEMS:
                result = re.search(lexem[1], line)
                if not result: continue
                line = line[result.end():]
                print(f'{result.group().ljust(8)} {lexem[0].ljust(16)} {lexem[2]}')
                break
            else:
                break
        if len(line) != 0:
            raise Exception(f"Error, can't parse: {line}")



def get_token() -> str:
    return get_token_from_temp_token_provider()
