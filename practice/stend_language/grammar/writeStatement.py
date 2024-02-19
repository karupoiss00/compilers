from practice.stend_language.lexer.token_provider import pop_token

def write_statement() -> bool:
    """<WRITE STATEMENT> -> <WRITELINE> | <WRITE>"""
    return writeline() or write()

def writeline() -> bool:
    """<WRITELINE> -> WriteLine(<IDENTIFIER>)"""
    return pop_token() == "WRITELINE"

def write() -> bool:
    """<WRITE> -> Write(<IDENTIFIER>)"""
    return pop_token() == "WRITE"