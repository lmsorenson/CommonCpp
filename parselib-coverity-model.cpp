// coverity[+kill]
void test() {
    int *p = (int*)malloc(10);
    *p = 0;
    ...
    special_abort();
}