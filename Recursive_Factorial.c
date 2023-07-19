// Program to find Factorial using recursive function

# include<stdio.h>
int fact(int);
int main()
{
    int num, val;
    printf(" Enter The Number:");
    scanf("%d", &num);
    val = fact(num);
    printf(" The factorial of %d =%d", num, val);
}
int fact(int n)
{
    if(n==1){
        return 1;
    }
    else 
    return (n*fact(n-1));
}