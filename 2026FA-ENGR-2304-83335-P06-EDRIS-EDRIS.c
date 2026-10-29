/* 2026FA-ENGR-2304-83335-EDRIS-EDRIS-P06 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ROWS 5000
#define PLANTS 6

typedef struct
{
    int year, month, day;
    int units[PLANTS];
} Record;

Record data[MAX_ROWS];
int count = 0;

int loadFile(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    char line[256];
    int y, m, d, v[PLANTS];

    count = 0;

    if (fp == NULL)
        return 0;

    while (fgets(line, sizeof(line), fp) && count < MAX_ROWS)
    {
        int n = sscanf(line,
            " %d , %d , %d , %d , %d , %d , %d , %d , %d",
            &y, &m, &d,
            &v[0], &v[1], &v[2],
            &v[3], &v[4], &v[5]);

        if (n != 9)
        {
            n = sscanf(line,
                " %d %d %d %d %d %d %d %d %d",
                &y, &m, &d,
                &v[0], &v[1], &v[2],
                &v[3], &v[4], &v[5]);
        }

        if (n == 9)
        {
            data[count].year = y;
            data[count].month = m;
            data[count].day = d;

            for (int j = 0; j < PLANTS; j++)
                data[count].units[j] = v[j];

            count++;
        }
    }

    fclose(fp);
    return count;
}

void analysis(void)
{
    if (count == 0)
    {
        printf("No data loaded.\n");
        return;
    }

    printf("\nPLANT DATA ANALYSIS (%d days)\n", count);
    printf("Plant     Min     Max       Mean       Mode     Std Dev     Variance\n");

    for (int p = 0; p < PLANTS; p++)
    {
        int min = data[0].units[p];
        int max = min;
        int mode = min;
        int bestFreq = 0;

        double sum = 0;
        double variance = 0;

        for (int i = 0; i < count; i++)
        {
            int x = data[i].units[p];

            if (x < min) min = x;
            if (x > max) max = x;

            sum += x;
        }

        double mean = sum / count;

        for (int i = 0; i < count; i++)
        {
            double diff = data[i].units[p] - mean;
            variance += diff * diff;

            int freq = 0;

            for (int j = 0; j < count; j++)
            {
                if (data[j].units[p] == data[i].units[p])
                    freq++;
            }

            if (freq > bestFreq ||
                (freq == bestFreq && data[i].units[p] < mode))
            {
                bestFreq = freq;
                mode = data[i].units[p];
            }
        }

        variance /= count;

        printf("L%-6d %5d %7d %10.2f %10d %11.2f %12.2f\n",
            p + 1, min, max, mean,
            mode, sqrt(variance), variance);
    }

    printf("Standard deviation and variance use population formulas.\n");
}

void report(void)
{
    if (count == 0)
    {
        printf("No data loaded.\n");
        return;
    }

    long long totals[PLANTS] = {0};

    int bestDay = 0;
    int bestPlant = 0;
    int bestUnits = data[0].units[0];

    int bestAllDay = 0;
    int highestDailyTotal = -1;

    for (int i = 0; i < count; i++)
    {
        int dailyTotal = 0;

        for (int p = 0; p < PLANTS; p++)
        {
            int x = data[i].units[p];

            totals[p] += x;
            dailyTotal += x;

            if (x > bestUnits)
            {
                bestUnits = x;
                bestDay = i;
                bestPlant = p;
            }
        }

        if (dailyTotal > highestDailyTotal)
        {
            highestDailyTotal = dailyTotal;
            bestAllDay = i;
        }
    }

    int best = 0;
    int worst = 0;

    for (int p = 1; p < PLANTS; p++)
    {
        if (totals[p] > totals[best])
            best = p;

        if (totals[p] < totals[worst])
            worst = p;
    }

    printf("\nPRODUCTION REPORT\n");
    printf("Records: %d days\n", count);

    for (int p = 0; p < PLANTS; p++)
    {
        printf("Plant L%d total production: %lld\n",
               p + 1, totals[p]);
    }

    printf("Best overall plant: L%d (%lld units)\n",
           best + 1, totals[best]);

    printf("Worst overall plant: L%d (%lld units)\n",
           worst + 1, totals[worst]);

    printf("Best single-plant day: L%d, %04d-%02d-%02d (%d units)\n",
           bestPlant + 1,
           data[bestDay].year,
           data[bestDay].month,
           data[bestDay].day,
           bestUnits);

    printf("Best combined day: %04d-%02d-%02d (%d units across 6 plants)\n",
           data[bestAllDay].year,
           data[bestAllDay].month,
           data[bestAllDay].day,
           highestDailyTotal);
}

void searchData(void)
{
    int y, m, d, option, plant;
    int found = 0;

    printf("\n1. One plant on a date\n");
    printf("2. All plants on a date\n");
    printf("Choice: ");

    if (scanf("%d", &option) != 1)
        return;

    if (option != 1 && option != 2)
    {
        printf("Invalid option.\n");
        return;
    }

    printf("Enter date (year month day): ");

    if (scanf("%d %d %d", &y, &m, &d) != 3)
        return;

    if (option == 1)
    {
        printf("Plant number (1-6): ");

        if (scanf("%d", &plant) != 1)
            return;

        if (plant < 1 || plant > 6)
        {
            printf("Invalid plant.\n");
            return;
        }
    }

    for (int i = 0; i < count; i++)
    {
        if (data[i].year == y &&
            data[i].month == m &&
            data[i].day == d)
        {
            found = 1;

            printf("Production on %04d-%02d-%02d:\n",
                   y, m, d);

            if (option == 1)
            {
                printf("L%d: %d units\n",
                       plant, data[i].units[plant - 1]);
            }
            else
            {
                for (int p = 0; p < PLANTS; p++)
                {
                    printf("L%d: %d units\n",
                           p + 1, data[i].units[p]);
                }
            }
        }
    }

    if (!found)
        printf("Date not found in data file.\n");
}

int main(void)
{
    int choice;
    char filename[256];

    printf("Enter CSV or TXT file name: ");

    if (fgets(filename, sizeof(filename), stdin) == NULL)
        return 1;

    filename[strcspn(filename, "\r\n")] = '\0';

    if (!loadFile(filename))
    {
        printf("Could not load data. Check file location and name.\n");
        return 1;
    }

    printf("Successfully loaded %d records.\n", count);

    do
    {
        printf("\n===== STATISTICAL DATA ANALYSIS =====\n");
        printf("1. Plant Data Analysis\n");
        printf("2. Production Report\n");
        printf("3. Search Production Data\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
            break;

        switch (choice)
        {
            case 1:
                analysis();
                break;

            case 2:
                report();
                break;

            case 3:
                searchData();
                break;

            case 4:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 4);

    return 0;
}