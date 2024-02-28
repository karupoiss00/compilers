import re
import io


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
ROF = 23
OR = 24
ASSIGN = 25
SEMICOLON = 26
IDENTIFIER = 27
FLOAT = 28
NUMBER = 29
STRING = 30
CHAR = 31
LPAREN = 32
RPAREN = 33
LBRACKET = 34
RBRACKET = 35
STAR = 36
PLUS = 37
MINUS = 38
SLASH = 39
LBRACE = 40
RBRACE = 41
GREATER_THAN = 42
GREATER_OR_EQUAL_THAN = 43
LESS_THAN = 44
LESS_OR_EQUAL_THAN = 45
WRITE = 46
WRITELINE = 47
READ = 48
READLINE = 49
AND = 50
TRUE = 51
FALSE = 52
EQUAL = 53
NOT_EQUAL = 54

CASE_SENSITIVE_LEXEMS = [WRITE, WRITELINE, READ, READLINE, STRING_TYPE, INT_TYPE, FLOAT_TYPE, BOOLEAN_TYPE, CHAR_TYPE]

LEXEMS = [
    ['START', r'^\bSTART\b', START],
    ['FINISH', r'^\bFINISH\b', FINISH],
    ['CONST', r'^\bCONST\b', CONST],
    ['NOC', r'^\bNOC\b', NOC],
    ['VAR', r'^\bVAR\b', VAR],
    ['RAV', r'^\bRAV\b', RAV],
    ['STRING_TYPE', r'^\bString\b', STRING_TYPE],
    ['INT_TYPE', r'^\bInt\b', INT_TYPE],
    ['FLOAT_TYPE', r'^\bFloat\b', FLOAT_TYPE],
    ['BOOLEAN_TYPE', r'^\bBoolean\b', BOOLEAN_TYPE],
    ['CHAR_TYPE', r'^\bChar\b', CHAR_TYPE],
    ['WRITE', r'^\bWRITE\b', WRITE],
    ['WRITELINE', r'^\bWRITELINE\b', WRITELINE],
    ['READ', r'^\bREAD\b', READ],
    ['READLINE', r'^\bREADLINE\b', READLINE],
    ['DIV', r'^\bdiv\b', DIV],
    ['MOD', r'^\bmod\b', MOD],
    ['NOT', r'^\bnot\b', NOT],
    ['IF', r'^\bif\b', IF],
    ['THEN', r'^\bthen\b', THEN],
    ['FI', r'^\bfi\b', FI],
    ['ELSE', r'^\belse\b', ELSE],
    ['WHILE', r'^\bwhile\b', WHILE],
    ['DO', r'^\bdo\b', DO],
    ['EL', r'^\bel\b', EL],
    ['FOR', r'^\bfor\b', FOR],
    ['TO', r'^\bto\b', TO],
    ['DO', r'^\bdo\b', DO],
    ['ROF', r'^\brof\b', ROF],
    ['OR', r'^\bor\b', OR],
    [':=', r'^:=', ASSIGN],
    [';', r'^;', SEMICOLON],
    ['TRUE', r'^\btrue\b', TRUE],
    ['FALSE', r'^\bfalse\b', FALSE],
    ['IDENTIFIER', r'^\b[a-zA-Z_]+\b', IDENTIFIER],
    ['FLOAT_VALUE', r'^\d+\.\d+', FLOAT],
    ['INT_VALUE', r'^\d+', NUMBER],
    ['STRING_VALUE', r'^\"([^"]|"")*\"', STRING],
    ['CHAR_VALUE', r'^\'([^\']|\'\')*\'', CHAR],
    ['(', r'^\(', LPAREN],
    [')', r'^\)', RPAREN],
    ['[', r'^\[', LBRACKET],
    [']', r'^\]', RBRACKET],
    ['{', r'^\{', LBRACE],
    ['}', r'^\}', RBRACE],
    ['*', r'^\*', STAR],
    ['+', r'^\+', PLUS],
    ['-', r'^\-', MINUS],
    ['/', r'^\/', SLASH],
    ['>=', r'^\>=', GREATER_OR_EQUAL_THAN],
    ['<=', r'^\<=', LESS_OR_EQUAL_THAN],
    ['<>', r'^<>', NOT_EQUAL],
    ['>', r'^\>', GREATER_THAN],
    ['<', r'^\<', LESS_THAN],
    ['AND', r'^\band\b', AND],
    ['=', r'^\=', EQUAL]
]


class NoNextTokenException(Exception):
    pass


class Token:
    def __init__(self, identifier: int, name: str, value: str):
        self.id = identifier
        self.name = name
        self.value = value


tokens = []
position = 0


def tokenize(text):
    global tokens
    global position

    position = 0
    tokens = []

    buf = io.StringIO(text)
    lines = buf.readlines()
    for line in lines:
        while line:
            line = line.strip()
            for lexem in LEXEMS:
                flags = 0 if lexem[2] in CASE_SENSITIVE_LEXEMS else re.I
                result = re.search(lexem[1], line, flags)

                if not result:
                    continue

                identifier = lexem[2]
                name = lexem[0].ljust(16).strip()
                value = result.group().ljust(8).strip()
                token = Token(identifier, name, value)
                tokens.append(token)

                line = line[result.end():]
                break
            else:
                break
        if len(line) != 0:
            raise Exception(f"Error, can't parse: {line}")


def get_token() -> Token:
    global position
    if position < len(tokens):
        token = tokens[position]
        position += 1
        return token
    else:
        raise NoNextTokenException


def get_tokens_count() -> int:
    return len(tokens)
