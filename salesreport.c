#include <stdio.h>

//swap function to aid sorting algorithm
void swap(double* x, double* y)
{
    double temp = *x;
    *x = *y;
    *y = temp;
}

//function that sorts in descending order 
void year_max_sort(double* sales, char* months[])
{
    int MAX_SIZE = 12; //max size the array can be is 12 (12 months in a year)
    int max_index;

    for (int i=0; i<(MAX_SIZE-1); i++) 
    { 
        // Find the max element in unsorted array 
        max_index = i; 
        for (int j=(i+1); j<MAX_SIZE; j++) 
        {
            if (sales[j] > sales[max_index])
            {
                max_index = j;
            }
        }
        //Perform a swap between the first element in the array and the max element
        //  do for both the sales array AND the months array!!
        swap(&sales[max_index], &sales[i]);
        
        char* temp = months[max_index];
        months[max_index] = months[i];
        months[i] = temp;

    } 
}


void load_report(double* month_data)
{
    //TODO: make it so that users can input different text files
    FILE *fptr;

    char fname[] = "sales_test.txt";
    //open file
    fptr = fopen(fname, "r");

    //read sales into month_data array
    for(int i=0; i<12; i++)
    {
        fscanf(fptr,"%lf", &month_data[i]);
    }

    //close file
    fclose(fptr);
}


void generate_report(double* month_data)
{
    //array for month names to be used for tables 
    char* month_table[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    //print off chronological sales table
    printf("==Month==  ==Sales==\n");
    for(int i=0;i<12;i++)
    {
        printf("%-10s $%7.2lf\n", month_table[i], month_data[i]);
    }
    printf("\n");

    //print off highest, lowest, and avg
    int index_high = 0;
    int index_low = 0;
    double sum = 0.0;
    double avg;

    for (int i=0;i<12;i++)
    {
        if (month_data[index_high] < month_data[i])
        {
            index_high = i;
        }

        if (month_data[index_low] > month_data[i])
        {
            index_low = i;
        }

        sum = sum + month_data[i];
    }

    //now we can calculate avg sales with sum / 12
    avg = sum / 12;

    //print the results
    printf("========= Sales Summary =========\n");
    printf("Lowest Sales:  $%.2lf, %s\n", month_data[index_low], month_table[index_low]);
    printf("Highest Sales: $%8.2lf, %s\n", month_data[index_high], month_table[index_high]);
    printf("Average Sales: $%8.2lf\n\n", avg);


    //print off 6 month moving avg
    //  for 1 year, there will be 7 6 month averages; 
    //  jan-jun feb-jul mar-aug apr-sep may-oct jun-nov jul-dec
    double temp_sum;
    double temp_avg;

    printf("==== 6 Month Moving Averages ====\n   6 Month Period    Sales Average\n"); // print header before loop
    for (int i=0; i<7; i++)
    {
        temp_sum = 0.0; //reset sum

        //calculate sum for the 6 month period
        for (int j=i; j<(i+6); j++)
        {
            temp_sum = temp_sum + month_data[j];
        }

        temp_avg = temp_sum / 6; //calculate avg

        printf("%-8s - %-9s", month_table[i], month_table[i+5]); //print month-month $average
        printf("   $%-.2lf\n", temp_avg);

    }

    //print highest sales to lowest sales
    //sort the arrays
    year_max_sort(month_data, month_table);

    //print off sales table
    printf("\n==Month==  ==Sales==\n");
    for(int i=0;i<12;i++)
    {
        printf("%-10s $%7.2lf\n", month_table[i], month_data[i]);
    }
    printf("\n");

}


int main()
{
    double month_data[12]; //array of size 12, one for each month

    load_report(month_data);
    generate_report(month_data);
    
    return 0;
}