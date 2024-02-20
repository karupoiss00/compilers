from grammar.identifier import identifier
from lexer.token_provider import read_token, pop_token

def read_statement() -> bool:
    """<READ STATEMENT> -> <READLINE> | <READ>"""
    return readline() or read()

def readline() -> bool:
    """<READLINE> -> ReadLine(<IDENTIFIER>)"""
    try:
        return read_token() == "READLINE" and pop_token() and pop_token() == "(" and identifier() and pop_token() == ")"
    except Exception:
        return False

def read() -> bool:
    """<READ> -> Read(<IDENTIFIER>)"""
    try:
        return read_token() == "READ" and pop_token() and pop_token() == "(" and identifier() and pop_token() == ")"
    except Exception:
        return False
