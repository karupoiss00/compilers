import re
import io
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
                flags = None if lexem[2] in CASE_SENSITIVE_LEXEMS else re.IGNORECASE
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
