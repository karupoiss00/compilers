from lexer import tokenize, get_token, get_tokens_count

tests = [
    ('''
START 
CONST 
    String id := 123; 
    Int id := 123; 
    Float id := 1.23;
    Boolean id := 1.24;
    Char id := 123
NOC
VAR
    Int id := 123 
RAV 
{ 
    READ(id);
    FOR id := 5 TO 10 
    DO 
        id := 1;
        IF id > 0 THEN 
            id := 10
        ELSE 
            id := 0
        FI
    ROF; 
    id := 1; 
    ;;
    IF id > 0 
    THEN 
        id := 10;
        FOR id := 5 TO 10 
        DO 
            id := 1;
            IF id > 0 THEN 
                id := 10 
            ELSE 
                id := 0 
            FI
        ROF 
    ELSE 
        id := 0; 
        FOR id := 5 TO 10 
        DO 
            id := 1;
            IF id > 0 THEN 
                id := 10 
            ELSE 
                id := 0 
            FI
        ROF; 
        WHILE id < 5
        DO
            id := id + 1;
            READLINE(id);
            WHILE id < 5
            DO
                id := id + 1
            EL
        EL
    FI;

    WRITELINE(id + 1);
    WRITE(id + 2)
} 
FINISH
''', [
    [0, "START"],
    [2, "CONST"],
    [6, "String"],
    [27, "id"],
    [25, ":="],
    [29, "123"],
    [26, ";"],
    [7, "Int"],
    [27, "id"],
    [25, ":="],
    [29, "123"],
    [26, ";"],
    [8, "Float"],
    [27, "id"],
    [25, ":="],
    [28, "1.23"],
    [26, ";"],
    [9, "Boolean"],
    [27, "id"],
    [25, ":="],
    [28, "1.24"],
    [26, ";"],
    [10, "Char"],
    [27, "id"],
    [25, ":="],
    [29, "123"],
    [3, "NOC"],
    [4, "VAR"],
    [7, "Int"],
    [27, "id"],
    [25, ":="],
    [29, "123"],
    [5, "RAV"],
    [40, "{"],
    [48, "READ"],
    [32, "("],
    [27, "id"],
    [33, ")"],
    [26, ";"],
    [21, "FOR"],
    [27, "id"],
    [25, ":="],
    [29, "5"],
    [22, "TO"],
    [29, "10"],
    [19, "DO"],
    [27, "id"],
    [25, ":="],
    [29, "1"],
    [26, ";"],
    [14, "IF"],
    [27, "id"],
    [42, ">"],
    [29, "0"],
    [15, "THEN"],
    [27, "id"],
    [25, ":="],
    [29, "10"],
    [17, "ELSE"],
    [27, "id"],
    [25, ":="],
    [29, "0"],
    [16, "FI"],
    [23, "ROF"],
    [26, ";"],
    [27, "id"],
    [25, ":="],
    [29, "1"],
    [26, ";"],
    [26, ";"],
    [26, ";"],
    [14, "IF"],
    [27, "id"],
    [42, ">"],
    [29, "0"],
    [15, "THEN"],
    [27, "id"],
    [25, ":="],
    [29, "10"],
    [26, ";"],
    [21, "FOR"],
    [27, "id"],
    [25, ":="],
    [29, "5"],
    [22, "TO"],
    [29, "10"],
    [19, "DO"],
    [27, "id"],
    [25, ":="],
    [29, "1"],
    [26, ";"],
    [14, "IF"],
    [27, "id"],
    [42, ">"],
    [29, "0"],
    [15, "THEN"],
    [27, "id"],
    [25, ":="],
    [29, "10"],
    [17, "ELSE"],
    [27, "id"],
    [25, ":="],
    [29, "0"],
    [16, "FI"],
    [23, "ROF"],
    [17, "ELSE"],
    [27, "id"],
    [25, ":="],
    [29, "0"],
    [26, ";"],
    [21, "FOR"],
    [27, "id"],
    [25, ":="],
    [29, "5"],
    [22, "TO"],
    [29, "10"],
    [19, "DO"],
    [27, "id"],
    [25, ":="],
    [29, "1"],
    [26, ";"],
    [14, "IF"],
    [27, "id"],
    [42, ">"],
    [29, "0"],
    [15, "THEN"],
    [27, "id"],
    [25, ":="],
    [29, "10"],
    [17, "ELSE"],
    [27, "id"],
    [25, ":="],
    [29, "0"],
    [16, "FI"],
    [23, "ROF"],
    [26, ";"],
    [18, "WHILE"],
    [27, "id"],
    [44, "<"],
    [29, "5"],
    [19, "DO"],
    [27, "id"],
    [25, ":="],
    [27, "id"],
    [37, "+"],
    [29, "1"],
    [26, ";"],
    [49, "READLINE"],
    [32, "("],
    [27, "id"],
    [33, ")"],
    [26, ";"],
    [18, "WHILE"],
    [27, "id"],
    [44, "<"],
    [29, "5"],
    [19, "DO"],
    [27, "id"],
    [25, ":="],
    [27, "id"],
    [37, "+"],
    [29, "1"],
    [20, "EL"],
    [20, "EL"],
    [16, "FI"],
    [26, ";"],
    [47, "WRITELINE"],
    [32, "("],
    [27, "id"],
    [37, "+"],
    [29, "1"],
    [33, ")"],
    [26, ";"],
    [46, "WRITE"],
    [32, "("],
    [27, "id"],
    [37, "+"],
    [29, "2"],
    [33, ")"],
    [41, "}"],
    [1, "FINISH"]
]),
('''
START } FINISH
''', [
    [0, "START"],
    [41, "}"],
    [1, "FINISH"]
]),
]

for test_id, test_data in enumerate(tests):
    test, expected_token_list = test_data
    tokenize(test)

    if len(expected_token_list) != get_tokens_count():
        raise Exception(f'''
    Tokens count does not match
    \tExpected: {len(expected_token_list)}
    \tGot: {get_tokens_count()}''')

    for token in expected_token_list:
        result_token = get_token()

        if result_token.id != token[0] or result_token.value != token[1]:
            print(f'{test_id + 1}:\tFAIL')
            print(f'\tExpected: {token}')
            print(f'\tGot: {result_token}')
            continue

    print(f'{test_id + 1}:\tOK')