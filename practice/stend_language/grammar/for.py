from expression import expression
from identifier import identifier
from lexer.token_provider import pop_token, read_token


def for_statement() -> bool:
    """<FOR STATEMENT> -> for <IDENTIFIER> := <NUMBER> to <NUMBER> do <EXPRESSION> rof"""
    return (
        read_token() == "FOR"
        and pop_token()
        and identifier()
        and pop_token() == ":="
        and number()
        and pop_token() == "TO"
        and number()
        and pop_token() == "DO"
        and expression()
        and pop_token() == "ROF"
    )
