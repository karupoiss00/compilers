from parser.expression.expression import expression
from parser.common.identifier import identifier
from parser.common.number import number
from lexer.token_provider import match_token, pop_token
from lexer.token_type import TokenType

# LIST STATEMENTS #

def list_statements() -> bool:
    """<LIST STATEMENTS> -> <STATEMENT>;<LIST STATEMENTS>|<STATEMENT>"""
    if statement():
        if match_token(TokenType.SEMICOLON):
            pop_token()
            return list_statements()
        return True
    return False
# RULES #


def statement() -> bool:
    """<STATEMENT> -> <EMPTY STATEMENT> | <ASSIGNMENT STATEMENT> | <IF STATEMENT> | [ LIST STATEMENT ]"""
    return (
        empty_statement()
        or assignment_statement()
        or for_statement()
        or while_statement()
        or if_statement()
        or write_statement()
        or read_statement()
        or
        (
            match_token(TokenType.LBRACKET) and pop_token()
            and list_statements() and
            match_token(TokenType.RBRACKET) and pop_token()
        )
    )

def empty_statement() -> bool:
    """<EMPTY STATEMENT> -> ;"""
    if match_token(TokenType.SEMICOLON):
        pop_token()
        return True
    return False


def assignment_statement() -> bool:
    """<ASSIGNMENT STATEMENT> -> <IDENTIFIER> := <EXPRESSION>"""
    return identifier() and pop_token() and match_token(TokenType.ASSIGN) and pop_token() and expression()


def if_statement() -> bool:
    """<IF STATEMENT> -> IF <EXPRESSION> THEN <STATEMENT><OPTIONAL ELSE> FI"""
    return (
        match_token(TokenType.IF)
        and pop_token()
        and expression()
        and match_token(TokenType.THEN)
        and pop_token()
        and list_statements()
        and optional_else()
        and match_token(TokenType.FI)
        and pop_token()
    )


def optional_else() -> bool:
    """<OPTIONAL ELSE> -> e | ELSE <STATEMENT>"""
    if match_token(TokenType.ELSE):
        pop_token()
        return list_statements()
    return True


def for_statement() -> bool:
    """<FOR STATEMENT> -> for <IDENTIFIER> := <NUMBER> to <NUMBER> do <LIST STATEMENTS> rof"""
    return (
            match_token(TokenType.FOR)
            and pop_token()
            and identifier()
            and pop_token()
            and match_token(TokenType.ASSIGN)
            and pop_token()
            and number()
            and pop_token()
            and match_token(TokenType.TO)
            and pop_token()
            and number()
            and pop_token()
            and match_token(TokenType.DO)
            and pop_token()
            and list_statements()
            and match_token(TokenType.ROF)
            and pop_token()
    )


def while_statement() -> bool:
    """<WHILE STATEMENT> -> WHILE <EXPRESSION> do <LIST STATEMENTS> el"""

    return (
        match_token(TokenType.WHILE)
        and pop_token()
        and expression()
        and match_token(TokenType.DO)
        and pop_token()
        and list_statements()
        and match_token(TokenType.EL)
        and pop_token()
    )

def read_statement() -> bool:
    """<READ STATEMENT> -> <READLINE> | <READ>"""
    return readline() or read()


def readline() -> bool:
    """<READLINE> -> ReadLine(<IDENTIFIER>)"""
    return (match_token(TokenType.READLINE)
            and pop_token()
            and match_token(TokenType.LPAREN)
            and pop_token()
            and identifier()
            and pop_token()
            and match_token(TokenType.RPAREN)
            and pop_token()
    )


def read() -> bool:
    """<READ> -> Read(<IDENTIFIER>)"""
    return (match_token(TokenType.READ)
            and pop_token()
            and match_token(TokenType.LPAREN)
            and pop_token()
            and identifier()
            and pop_token()
            and match_token(TokenType.RPAREN)
            and pop_token()
    )


def write_statement() -> bool:
    """<WRITE STATEMENT> -> <WRITELINE> | <WRITE>"""
    return writeline() or write()


def writeline() -> bool:
    """<WRITELINE> -> WriteLine(<IDENTIFIER>)"""
    return (match_token(TokenType.WRITELINE)
            and pop_token()
            and match_token(TokenType.LPAREN)
            and pop_token()
            and expression()
            and match_token(TokenType.RPAREN)
            and pop_token()
    )


def write() -> bool:
    """<WRITE> -> Write(<IDENTIFIER>)"""
    return (match_token(TokenType.WRITE)
            and pop_token()
            and match_token(TokenType.LPAREN)
            and pop_token()
            and expression()
            and match_token(TokenType.RPAREN)
            and pop_token()
    )
