 /* 2026FA-ENGR-2304-83335-EDRIS-EDRIS-P04 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double truncate3(double value)
{
    return trunc(value * 1000.0) / 1000.0;
}

int main(void)
{
    int Vs, R1, R2, R3;
    double i1, i2;
    double V1, V2, V3;
    double user_i1, user_i2;
    double user_V1, user_V2, user_V3;
    int choice;
    int correct;

    srand((unsigned int)time(NULL));

    do
    {
        /* Step 1: Generate random values */
        Vs = (rand() % 9) + 1;
        R1 = (rand() % 19) + 1;
        R2 = (rand() % 19) + 1;
        R3 = (rand() % 19) + 1;

        /*
           Circuit equations:

           (R1 + R2)i1 - R2 i2 = Vs
           -R2 i1 + (R2 + R3)i2 = 0
        */

        double determinant;
        determinant = (R1 + R2) * (R2 + R3) - (R2 * R2);

        i1 = (Vs * (R2 + R3)) / determinant;
        i2 = (Vs * R2) / determinant;

        /* Calculate voltages */
        V1 = R1 * i1;
        V2 = R2 * (i1 - i2);
        V3 = R3 * i2;

        /* Truncate calculated values to 3 decimal places */
        i1 = truncate3(i1);
        i2 = truncate3(i2);
        V1 = truncate3(V1);
        V2 = truncate3(V2);
        V3 = truncate3(V3);

        /* Step 3: Present random values */
        printf("\n========================================\n");
        printf("       CIRCUIT PROBLEM GENERATOR\n");
        printf("========================================\n");

        printf("\nGenerated Circuit Values:\n");
        printf("Vs = %d V\n", Vs);
        printf("R1 = %d Ohms\n", R1);
        printf("R2 = %d Ohms\n", R2);
        printf("R3 = %d Ohms\n", R3);

        printf("\nEnter your answers using precision of 1e-3.\n");

        printf("\ni1 = ");
        scanf("%lf", &user_i1);

        printf("i2 = ");
        scanf("%lf", &user_i2);

        printf("V1 = ");
        scanf("%lf", &user_V1);

        printf("V2 = ");
        scanf("%lf", &user_V2);

        printf("V3 = ");
        scanf("%lf", &user_V3);

        /* Step 4: Compare answers */
        printf("\n========================================\n");
        printf("             RESULTS\n");
        printf("========================================\n");

        correct = 1;

        if (fabs(user_i1 - i1) < 0.001)
            printf("i1: SUCCESS\n");
        else
        {
            printf("i1: FAILURE - Correct answer = %.3f\n", i1);
            correct = 0;
        }

        if (fabs(user_i2 - i2) < 0.001)
            printf("i2: SUCCESS\n");
        else
        {
            printf("i2: FAILURE - Correct answer = %.3f\n", i2);
            correct = 0;
        }

        if (fabs(user_V1 - V1) < 0.001)
            printf("V1: SUCCESS\n");
        else
        {
            printf("V1: FAILURE - Correct answer = %.3f\n", V1);
            correct = 0;
        }

        if (fabs(user_V2 - V2) < 0.001)
            printf("V2: SUCCESS\n");
        else
        {
            printf("V2: FAILURE - Correct answer = %.3f\n", V2);
            correct = 0;
        }

        if (fabs(user_V3 - V3) < 0.001)
            printf("V3: SUCCESS\n");
        else
        {
            printf("V3: FAILURE - Correct answer = %.3f\n", V3);
            correct = 0;
        }

        if (correct)
            printf("\nSUCCESS: All answers are correct!\n");
        else
            printf("\nFAILURE: One or more answers are incorrect.\n");

        /* Step 5: Restart or exit */
        printf("\nEnter 1 to generate a new circuit.\n");
        printf("Enter 2 to exit the program.\n");
        printf("Choice: ");
        scanf("%d", &choice);

    } while (choice != 2);

    printf("\nProgram exited.\n");

    return 0;
}