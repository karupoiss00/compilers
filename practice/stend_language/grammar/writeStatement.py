from grammar.identifier import identifier
from lexer.token_provider import pop_token, read_token

def write_statement() -> bool:
    """<WRITE STATEMENT> -> <WRITELINE> | <WRITE>"""
    return writeline() or write()

def writeline() -> bool:
    """<WRITELINE> -> WriteLine(<IDENTIFIER>)"""
    try:
        return read_token() == "WRITELINE" and pop_token() and pop_token() == "(" and identifier() and pop_token() == ")"
    except Exception:
        return False

def write() -> bool:
    """<WRITE> -> Write(<IDENTIFIER>)"""
    try:
        return read_token() == "WRITE" and pop_token() and pop_token() == "(" and identifier() and pop_token() == ")"
    except Exception:
        return False