int factorial(int n){
    if(n == 0) return 1;
    else return (factorial(n-1)*n); 
}

int main(int argc, char** argv){
    int n = 3;
    int fctrl = factorial(n);
    printf("Factorial %d is: %d\n", n, factorial(n)); 
    return 0;
}
