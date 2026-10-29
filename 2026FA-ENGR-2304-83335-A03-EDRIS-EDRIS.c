 /* 2026FA-ENGR-2304-83335-EDRIS-EDRIS-P03 */

#include <stdio.h>

double determinant2x2(double a, double b, double c, double d)
{
    return (a * d) - (b * c);
}

double determinant3x3(double a11, double a12, double a13,
                      double a21, double a22, double a23,
                      double a31, double a32, double a33)
{
    double det;

    det = a11 * determinant2x2(a22, a23, a32, a33)
        - a12 * determinant2x2(a21, a23, a31, a33)
        + a13 * determinant2x2(a21, a22, a31, a32);

    return det;
}

void solve2x2(void)
{
    double a1, b1, c1;
    double a2, b2, c2;
    double delta, deltaX, deltaY;
    double x, y;

    printf("\nSolve a system of two equations:\n");
    printf("a1*x + b1*y = c1\n");
    printf("a2*x + b2*y = c2\n\n");

    printf("Enter a1 b1 c1: ");
    scanf("%lf %lf %lf", &a1, &b1, &c1);

    printf("Enter a2 b2 c2: ");
    scanf("%lf %lf %lf", &a2, &b2, &c2);

    delta = determinant2x2(a1, b1, a2, b2);

    if (delta == 0)
    {
        printf("\nThe determinant is zero.\n");
        printf("The system does not have a unique solution.\n");
        return;
    }

    deltaX = determinant2x2(c1, b1, c2, b2);
    deltaY = determinant2x2(a1, c1, a2, c2);

    x = deltaX / delta;
    y = deltaY / delta;

    printf("\nDelta = %.4f\n", delta);
    printf("Delta X = %.4f\n", deltaX);
    printf("Delta Y = %.4f\n", deltaY);

    printf("\nSolution:\n");
    printf("x = %.4f\n", x);
    printf("y = %.4f\n", y);
}

void solve3x3(void)
{
    double a11, a12, a13, b1;
    double a21, a22, a23, b2;
    double a31, a32, a33, b3;

    double delta;
    double deltaX;
    double deltaY;
    double deltaZ;

    double x, y, z;

    printf("\nSolve a system of three equations:\n");
    printf("a11*x + a12*y + a13*z = b1\n");
    printf("a21*x + a22*y + a23*z = b2\n");
    printf("a31*x + a32*y + a33*z = b3\n\n");

    printf("Enter a11 a12 a13 b1: ");
    scanf("%lf %lf %lf %lf", &a11, &a12, &a13, &b1);

    printf("Enter a21 a22 a23 b2: ");
    scanf("%lf %lf %lf %lf", &a21, &a22, &a23, &b2);

    printf("Enter a31 a32 a33 b3: ");
    scanf("%lf %lf %lf %lf", &a31, &a32, &a33, &b3);

    delta = determinant3x3(
        a11, a12, a13,
        a21, a22, a23,
        a31, a32, a33
    );

    if (delta == 0)
    {
        printf("\nThe determinant is zero.\n");
        printf("The system does not have a unique solution.\n");
        return;
    }

    deltaX = determinant3x3(
        b1, a12, a13,
        b2, a22, a23,
        b3, a32, a33
    );

    deltaY = determinant3x3(
        a11, b1, a13,
        a21, b2, a23,
        a31, b3, a33
    );

    deltaZ = determinant3x3(
        a11, a12, b1,
        a21, a22, b2,
        a31, a32, b3
    );

    x = deltaX / delta;
    y = deltaY / delta;
    z = deltaZ / delta;

    printf("\nDelta = %.4f\n", delta);
    printf("Delta X = %.4f\n", deltaX);
    printf("Delta Y = %.4f\n", deltaY);
    printf("Delta Z = %.4f\n", deltaZ);

    printf("\nSolution:\n");
    printf("x = %.4f\n", x);
    printf("y = %.4f\n", y);
    printf("z = %.4f\n", z);
}

int main(void)
{
    int choice;

    do
    {
        printf("\n====================================\n");
        printf("       CRAMER'S RULE SOLVER\n");
        printf("====================================\n");
        printf("1. Solve two equations (2x2)\n");
        printf("2. Solve three equations (3x3)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            solve2x2();
        }
        else if (choice == 2)
        {
            solve3x3();
        }
        else if (choice == 3)
        {
            printf("\nProgram exited.\n");
        }
        else
        {
            printf("\nInvalid choice.\n");
        }

    } while (choice != 3);

    return 0;
}