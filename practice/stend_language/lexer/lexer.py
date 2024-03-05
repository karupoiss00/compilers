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
COMMA = 55

ALL_TOKENS = [i for i in range(0, 55 + 1)]
ALL_TYPES = (STRING_TYPE, INT_TYPE, FLOAT_TYPE, BOOLEAN_TYPE, CHAR_TYPE)
CASE_SENSITIVE_LEXEMS = [WRITE, WRITELINE, READ, READLINE, STRING_TYPE, INT_TYPE, FLOAT_TYPE, BOOLEAN_TYPE, CHAR_TYPE]
from lexer.token_type import TokenType


CASE_SENSITIVE_LEXEMS = [
    TokenType.WRITE, 
    TokenType.WRITELINE, 
    TokenType.READ, 
    TokenType.READLINE, 
    TokenType.STRING_TYPE, 
    TokenType.INT_TYPE, 
    TokenType.FLOAT_TYPE, 
    TokenType.BOOLEAN_TYPE, 
    TokenType.CHAR_TYPE,
]

LEXEMS = [
    ['START', r'^\bSTART\b', TokenType.START],
    ['FINISH', r'^\bFINISH\b', TokenType.FINISH],
    ['CONST', r'^\bCONST\b', TokenType.CONST],
    ['NOC', r'^\bNOC\b', TokenType.NOC],
    ['VAR', r'^\bVAR\b', TokenType.VAR],
    ['RAV', r'^\bRAV\b', TokenType.RAV],
    ['STRING_TYPE', r'^\bString\b', TokenType.STRING_TYPE],
    ['INT_TYPE', r'^\bInt\b', TokenType.INT_TYPE],
    ['FLOAT_TYPE', r'^\bFloat\b', TokenType.FLOAT_TYPE],
    ['BOOLEAN_TYPE', r'^\bBoolean\b', TokenType.BOOLEAN_TYPE],
    ['CHAR_TYPE', r'^\bChar\b', TokenType.CHAR_TYPE],
    ['WRITE', r'^\bWRITE\b', TokenType.WRITE],
    ['WRITELINE', r'^\bWRITELINE\b', TokenType.WRITELINE],
    ['READ', r'^\bREAD\b', TokenType.READ],
    ['READLINE', r'^\bREADLINE\b', TokenType.READLINE],
    ['DIV', r'^\bdiv\b', TokenType.DIV],
    ['MOD', r'^\bmod\b', TokenType.MOD],
    ['NOT', r'^\bnot\b', TokenType.NOT],
    ['IF', r'^\bif\b', TokenType.IF],
    ['THEN', r'^\bthen\b', TokenType.THEN],
    ['FI', r'^\bfi\b', TokenType.FI],
    ['ELSE', r'^\belse\b', TokenType.ELSE],
    ['WHILE', r'^\bwhile\b', TokenType.WHILE],
    ['DO', r'^\bdo\b', TokenType.DO],
    ['EL', r'^\bel\b', TokenType.EL],
    ['FOR', r'^\bfor\b', TokenType.FOR],
    ['TO', r'^\bto\b', TokenType.TO],
    ['DO', r'^\bdo\b', TokenType.DO],
    ['ROF', r'^\brof\b', TokenType.ROF],
    ['OR', r'^\bor\b', TokenType.OR],
    ['COMMA', r'^,', TokenType.COMMA],
    [':=', r'^:=', TokenType.ASSIGN],
    [';', r'^;', TokenType.SEMICOLON],
    ['TRUE', r'^\btrue\b', TokenType.TRUE],
    ['FALSE', r'^\bfalse\b', TokenType.FALSE],
    ['IDENTIFIER', r'^\b[a-zA-Z_]+\b', TokenType.IDENTIFIER],
    ['FLOAT_VALUE', r'^\d+\.\d+', TokenType.FLOAT],
    ['INT_VALUE', r'^\d+', TokenType.NUMBER],
    ['STRING_VALUE', r'^\"([^"]|"")*\"', TokenType.STRING],
    ['CHAR_VALUE', r'^\'([^\']|\'\')*\'', TokenType.CHAR],
    ['(', r'^\(', TokenType.LPAREN],
    [')', r'^\)', TokenType.RPAREN],
    ['[', r'^\[', TokenType.LBRACKET],
    [']', r'^\]', TokenType.RBRACKET],
    ['{', r'^\{', TokenType.LBRACE],
    ['}', r'^\}', TokenType.RBRACE],
    ['*', r'^\*', TokenType.STAR],
    ['+', r'^\+', TokenType.PLUS],
    ['-', r'^\-', TokenType.MINUS],
    ['/', r'^\/', TokenType.SLASH],
    ['>=', r'^\>=', TokenType.GREATER_OR_EQUAL_THAN],
    ['<=', r'^\<=', TokenType.LESS_OR_EQUAL_THAN],
    ['<>', r'^<>', TokenType.NOT_EQUAL],
    ['>', r'^\>', TokenType.GREATER_THAN],
    ['<', r'^\<', TokenType.LESS_THAN],
    ['AND', r'^\band\b', TokenType.AND],
    ['=', r'^\=', TokenType.EQUAL],
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
                flags = 0 if lexem[2] in CASE_SENSITIVE_LEXEMS else re.IGNORECASE
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
