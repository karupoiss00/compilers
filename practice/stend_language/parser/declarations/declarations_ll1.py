from lexer.token_provider import pop_token, read_token
from lexer.lexer import ALL_TOKENS, ALL_TYPES, COMMA, NUMBER, SEMICOLON, CONST, NOC, ASSIGN, VAR, RAV, IDENTIFIER, NoNextTokenException
from lexer.token_provider import match_token
from parser.common.identifier import identifier
from parser.expression.expression import expression


table = {
    # (Номер, Токен, Направляющие, Указатель,                   Сдвиг?, Ошибка?,Стэк?,  Конец?)
    1:  ('declarations',                [CONST, VAR],   2,      False,  True,   False,  False),
    2:  ('list_const',                  [CONST],        4,      False,  False,  True,   False),
    3:  ('list_var',                    [VAR],          13,     False,  True,   False,  False),
    4:  ('CONST',                       [CONST],        5,      True,   True,   False,  False),
    5:  ('list_section_const',          [*ALL_TOKENS],  8,      False,  True,   True,   False),
    6:  ('list_section_const_postfix',  [SEMICOLON],    5,      True,   False,  False,  False),
    7:  ('NOC',                         [NOC],          None,   True,   True,   False,  False),
    8:  ('section_const',               [*ALL_TOKENS],  9,      False,  True,   False,  False),
    9:  ('type',                        [*ALL_TYPES],   10,     True,   True,   False,  False),
    10: ('identifier',                  [IDENTIFIER],   11,     True,   True,   False,  False),
    11: ('ASSIGN',                      [ASSIGN],       12,     True,   True,   False,  False),
    12: ('expression',                  [NUMBER],       None,   True,   True,   False,  False), # TODO: Jump to expression table
    13: ('VAR',                         [VAR],          14,     True,   True,   False,  False),
    14: ('list_section_var',            [*ALL_TOKENS],  17,     False,  True,   True,   False),
    15: ('list_section_var_postfix',    [SEMICOLON],    14,     True,   False,  False,  False),
    16: ('RAV',                         [RAV],          None,   True,   True,   False,  True),
    17: ('section_var',                 [*ALL_TOKENS],  18,     False,  True,   False,  False),
    18: ('type',                        [*ALL_TYPES],   19,     True,   True,   False,  False),
    19: ('identifier_list',             [*ALL_TOKENS],  24,     False,  True,   True,   False),
    20: ('ASSIGN',                      [ASSIGN],       23,     True,   False,  False,  False),
    21: ('RAV',                         [RAV],          None,   True,   True,   False,  True),
    22: ('section_var_postfix',         [*ALL_TOKENS],  20,     False,  True,   False,  False),
    23: ('expression',                  [NUMBER],       None,   True,   True,   False,  False), # TODO: Jump to expression table
    24: ('identifier',                  [IDENTIFIER],   25,     True,   True,   False,  False),
    25: ('identifier_list_postfix',     [COMMA],        19,     True,   False,  False,  False),
    26: ('identifier_list_postfix',     [*ALL_TOKENS],  None,   False,  True,   False,  False),
}


def declarations() -> bool:
    current = 1
    stack = []
    while True:
        try:
            state = table[current]
            if read_token().id not in state[1] and state[4]:
                return False
            if read_token().id not in state[1]:
                current += 1
                continue
            if state[5]:
                stack.append(current + 1)
            if read_token().id in state[1]:
                current = state[2]
            if state[6]:
                return True
            if state[2] == None:
                try:
                    current = stack.pop()
                except:
                    return False
            if state[3]:
                pop_token()
        except NoNextTokenException:
            return False
