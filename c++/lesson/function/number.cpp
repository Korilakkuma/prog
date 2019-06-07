int fibonacci(int n) {
    if (n < 3) {
        return n;
    }

    return fibonacci(n - 2) + fibonacci(n - 1);
}

int factorial(int n) {
    if (n < 2) {
        return 1;
    }

    return n * factorial(n - 1);
}
