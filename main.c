#include <stdio.h>
#include <stdlib.h>


int** funk(int n, int k)
{
    int** a = malloc(n*sizeof(int*));
    for(int i=0; i<n; i++)
        a[i]=malloc(k*sizeof(int));
    return a;
}

int nod (int x, int y)
{
    if (y==0)
        return x;
    else
        return nod(y, x%y);
}
int nok (int x, int y)
{
    return (x*y)/nod(x, y);
}

void pomenyatt (int*a, int*b)
{
    int t=*a;
    *a=*b;
    *b=t;
}

int** treug(int** a, int* b, int n)
{
    for(int j=0; j<n-1; j++)
    {
        int i=j;
        while(a[i][j]==0)
        {
            i++;
            if(i>=n)
            {
                printf("\nopredelitelb raven nulu\n");
                return a;
            }
        }
        pomenyatt(&b[i], &b[j]);
        for(int k=j; k<n; k++)
            pomenyatt(&a[j][k], &a[i][k]);
        for(int k=j+1; k<n; k++)
        {
            if(a[k][j]!=0){
            int p = nok(a[j][j], a[k][j]);
            b[k]=(b[k]*p/a[k][j])+b[j]*(-p/a[j][j]);
            for(i=n-1; i>=j; i--)
                a[k][i]=(a[k][i]*p/a[k][j])+a[j][i]*(-p/a[j][j]);
            }
        }
    }
    printf("\ntreugolnaya matritsa:\n");
    for (int j=0; j<n; j++)
    {
        for (int i=0; i<n; i++)
            printf("%d ", a[j][i]);
        printf("\n");
    }
    printf("znacheniya pravyh chastey uravneniy2:\n");
    for(int i=0; i<n; i++)
        printf("%d\n", b[i]);
    printf("\n");
    return a;
}

int* reshitb(int** a, int*b, int n)
{
    float* x = calloc(n, sizeof(float));
    a = treug(a, b, n);
    for(int i=n-1; i>=0; i--)
    {
        float s=0;
        for(int j=n-1; j>i; j--)
            s=s+a[i][j]*x[j];
        x[i]=(b[i]*1.0-s)/a[i][i];
    }
    return x;
}

int main()
{
    int n, i, j;
    printf("Vvedite kol-vo peremennyih \n");
    scanf("%d", &n);
    int** a = funk(n, n);
    for (j=0; j<n; j++)
        for (i=0; i<n; i++)
        {
              scanf("%d", &a[i][j]); //a[j][i]=1+rand()%10;
        }
    printf("matritsa sistemy:\n");
    for (j=0; j<n; j++)
    {
        for (i=0; i<n; i++)
            printf("%d ", a[j][i]);
        printf("\n");
    }
    int* b = malloc(n*sizeof(int));
    for (i=0; i<n; i++)
    {
          scanf("%d", &b[i]); //b[i]=rand()%10;
    }
    printf("znacheniya pravyh chastey uravneniy:\n");
    for(i=0; i<n; i++)
        printf("%d\n", b[i]);
    printf("\n");
    float* x = calloc(n, sizeof(float));
    x = reshitb(a, b, n);
    printf("reshenie sistemy: ");
    for(i=0; i<n; i++)
        printf("%f ", x[i]);
    printf("\n");
    return 0;
}
