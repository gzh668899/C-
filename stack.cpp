char stack_op[100];
int stack_num[100];
int top_op;
int top_num;

void calc_op()
{
    int b = stack_num[top_num - 1];
    top_num--;
    int a = stack_num[top_num - 1];
    char op = stack_op[top_op - 1];
    top_op--;

    if (op == '*')
    {
        stack_num[top_num - 1] = a * b;
    }
    else if (op == '/')
    {
        if (b == 0)
        {
            stack_num[top_num - 1] = 0;
        }
        else 
        {
            stack_num[top_num - 1] = a / b;
        }
    }
    else if (op == '+')
    {
        stack_num[top_num - 1] = a + b;
    }
    else if (op == '-')
    {
        stack_num[top_num - 1] = a - b;
    }

    if (stack_num[top_num - 1] < 0)
    {
        stack_num[top_num - 1] = 0;
    }
    if (stack_num[top_num - 1] > 9999)
    {
        stack_num[top_num - 1] = stack_num[top_num - 1] % 10000;
    }

}

int calc(char *cmd)
{
    top_op = 0;
    top_num = 0;
    int index;
    char ch = cmd[index++];

    while (ch)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            stack_num[top_num++] = value[ch - 'A'];
        }
        else if (ch >= '0' && ch <= '9')
        {
            stack_num[top_num++] = ch - '0';
        }
        else if (ch == '(')
        {
            stack_op[top_op++] = ch;
        }
        else if (ch == '*' || ch == '/') //栈顶运算符的优先级要大于等于当前运算符的优先级，才进行运算
        {
            while ((top_op - 1 >= 0) && (stack_op[top_op - 1] == '*' || stack_op[top_op - 1] == '/'))
            {
                calc_op();
            }
            stack_op[top_op++] = ch;
        }
        else if (ch == '+' || ch == '-') //+ - * /
        {
            while ((top_op - 1 >= 0) && (stack_op[top_op - 1] != '('))
            {
                calc_op();
            }
            stack_op[top_op++] = ch;
        }
        else
        {
            while (stack_op[top_op - 1] != '(')
            {
                calc_op();
            }
            top_op--;
        }
        ch = cmd[index++];
    }

    while (stack_op > 0)
    {
        calc_op();
    }

    return stack_num[0];
}
