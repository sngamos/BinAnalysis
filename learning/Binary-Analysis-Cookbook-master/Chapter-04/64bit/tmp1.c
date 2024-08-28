#include<stdio.h>
int foo(int i) {
int k;
int res =0;
char buf[20];
for (k=1;k<10;k++){
res=res+i;
}
printf("Enter your name :");
fscanf(stdin,"%s",buf);
printf("Hello %s\n",buf);
return res;
}


int main() {
int k;
k=foo(2);
printf("Sum = %d\n",k);
return 0;
}
