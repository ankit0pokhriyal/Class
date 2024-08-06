// Program to find exp(x,y) using recursive function

# include<stdio.h>
int exp_func(int, int );
int main()
{
    int num1, num2, res;
    printf("\n Enter the two number:");
    scanf("%d, %d", &num1, &num2);
    res = exp_func(num1, num2);
    printf("\n RESULT = %d", res);
    return 0;
}
int exp_func(int n1, int n2){
    if(n2==0){       // condition for e^0 = 1
        return 1;
    }
    else{
        return (n1 * exp_func(n1, n2-1));
    }
    
}