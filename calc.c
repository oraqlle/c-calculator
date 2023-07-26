#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4096

typedef struct result {
    long long int value;
    short err;
} result_t;

result_t add(size_t x, size_t y)
{
    result_t res;
    res.value = x + y;
    res.err = 0;
    return res;
}

result_t sub(size_t x, size_t y)
{
    result_t res;
    res.value = x - y;
    res.err = 0;
    return res;
}

result_t mul(size_t x, size_t y)
{
    result_t res;
    res.value = x * y;
    res.err = 0;
    return res;
}

result_t div_(size_t x, size_t y)
{
    result_t res;

    if (y == 0) {
        res.value = 0;
        res.err = 2;
    } else {
        res.value = x / y;
        res.err = 0;
    }

    return res;
}

result_t mod(size_t x, size_t y)
{
    result_t res;
    res.value = x % y;
    res.err = 0;
    return res;
}

result_t select_op(char op, size_t x, size_t y)
{
    if (op == '+')
        return add(x, y);
    else if (op == '-')
        return sub(x, y);
    else if (op == '*')
        return mul(x, y);
    else if (op == '/') {
        return div_(x, y);
    } else if (op == '%')
        return mod(x, y);
    else {
        result_t res;
        res.value = 0;
        res.err = 3;
        return res;
    }
}

void print_help()
{
    puts("CLI Options");
    puts("help [CLI]  : --help | -h");

    puts("-------------------------");

    puts("Supported Operations");
    puts("add         : x + y");
    puts("subtract    : x - y");
    puts("multiply    : x * y");
    puts("divide      : x / y");
    puts("modulo      : x % y");
    puts("help [REPL] : ?");
    puts("quit        : !quit | !q");
    puts("kill        : ctrl+c");
}

int main(int argc, char* argv[])
{
    size_t x = 0;
    size_t y = 0;
    char op = ' ';
    char buf[SIZE];

    puts("Basic Calculator");
    if (argc > 1)
        if ((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0)) {
            print_help();
            exit(0);
        }

    while (1) {
        printf(">> ");

        fgets(&buf[0], SIZE, stdin);
        size_t end = strcspn(&buf[0], "\n");
        buf[end] = '\0';

        if (strcmp(&buf[0], "?") == 0)
            print_help();
        else if ((strcmp(&buf[0], "!quit") == 0) || (strcmp(&buf[0], "!q") == 0))
            break;
        else {
            sscanf(&buf[0], "%zu %c %zu", &x, &op, &y);
            result_t res = select_op(op, x, y);

            if (res.err == 2)
                puts("Division by 0 error!");
            else if (res.err == 3)
                printf("Invalid operator %c\n", op);
            else
                printf("%lld\n", res.value);
        }

        memset(&buf[0], 0, SIZE);
    }

    return 0;
}

