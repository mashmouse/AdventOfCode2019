#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>

void print_array(int *arr, int arr_length)
{
    printf("{");
    for (int i = 0; i < arr_length; i++)
    {
        printf("%d", arr[i]);
        if (i != (arr_length - 1))
        {
            printf(",");
        }
    }
    printf("}\n");
}

void intcode_compute(int *arr, int arr_length)
{
    for (int i = 0; i < arr_length; i += 4)
    {
        if (arr[i] == 99) // halt
        {
            break;
        }
        else if (arr[i] == 1) // add
        {
            int rd = arr[i + 3];
            int ro = arr[i + 1];
            int rt = arr[i + 2];
            arr[rd] = arr[ro] + arr[rt];
        }
        else if (arr[i] == 2) // multiply
        {
            int rd = arr[i + 3];
            int ro = arr[i + 1];
            int rt = arr[i + 2];
            arr[rd] = arr[ro] * arr[rt];
        }
    }
}

void compute_print_array(int *arr, int arr_length)
{
    print_array(arr, arr_length);
    intcode_compute(arr, arr_length);
    print_array(arr, arr_length);
    printf("\n");
}

int *find_noun_verb(int *origin, int arr_size, int target)
{
    int* ret= (int*)malloc(sizeof(origin[0]) * arr_size);
    memcpy(ret, origin, sizeof(origin[0]) * arr_size);
    bool start = true;
    for (int i = 0; i < 99; i++)
    {
        for (int j = 0; j < 99; j++)
        {
            if (ret[0] != target)
            {
                if (!start)
                {
                    memcpy(ret, origin, sizeof(origin[0]) * arr_size);
                } 
                else 
                {
                    start = false;
                }

                ret[1] = i;
                ret[2] = j;
                //print_array(ret, arr_size);
                intcode_compute(ret, arr_size);
                //print_array(ret, arr_size);
            }
            else
            {
                int val1 = ret[1];
                int val2 = ret[2];
                return &ret[1];
            }
        }
    }
}

int main()
{

    int sample_input_0[] = {1, 0, 0, 0, 99}; //2,0,0,0,99
    int size_sample_input_0 = sizeof(sample_input_0) / sizeof(sample_input_0[0]);
    int sample_input_1[] = {2, 3, 0, 3, 99}; //2,3,0,6,99
    int size_sample_input_1 = sizeof(sample_input_1) / sizeof(sample_input_1[0]);
    int sample_input_2[] = {2, 4, 4, 5, 99, 0}; //2,4,4,5,99,9801
    int size_sample_input_2 = sizeof(sample_input_2) / sizeof(sample_input_2[0]);
    int sample_input_3[] = {1, 1, 1, 4, 99, 5, 6, 0, 99}; //30,1,1,4,2,5,6,0,99
    int size_sample_input_3 = sizeof(sample_input_3) / sizeof(sample_input_3[0]);
    int PUZZLE_INPUT[] = {1, 12, 2, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 9, 1, 19, 1, 19, 5, 23, 1, 23, 5, 27, 2, 27, 10, 31, 1, 31, 9, 35, 1, 35, 5, 39, 1, 6, 39, 43, 2, 9, 43, 47, 1, 5, 47, 51, 2, 6, 51, 55, 1, 5, 55, 59, 2, 10, 59, 63, 1, 63, 6, 67, 2, 67, 6, 71, 2, 10, 71, 75, 1, 6, 75, 79, 2, 79, 9, 83, 1, 83, 5, 87, 1, 87, 9, 91, 1, 91, 9, 95, 1, 10, 95, 99, 1, 99, 13, 103, 2, 6, 103, 107, 1, 107, 5, 111, 1, 6, 111, 115, 1, 9, 115, 119, 1, 119, 9, 123, 2, 123, 10, 127, 1, 6, 127, 131, 2, 131, 13, 135, 1, 13, 135, 139, 1, 9, 139, 143, 1, 9, 143, 147, 1, 147, 13, 151, 1, 151, 9, 155, 1, 155, 13, 159, 1, 6, 159, 163, 1, 13, 163, 167, 1, 2, 167, 171, 1, 171, 13, 0, 99, 2, 0, 14, 0};

    int size_puzzle_input = sizeof(PUZZLE_INPUT) / sizeof(PUZZLE_INPUT[0]);
    int* puzzle_input = (int*)malloc(sizeof(PUZZLE_INPUT));
    memcpy(puzzle_input, PUZZLE_INPUT, sizeof(PUZZLE_INPUT));

    // samples from the exercise
    /*compute_print_array(sample_input_0, size_sample_input_0);
    compute_print_array(sample_input_1, size_sample_input_1);
    compute_print_array(sample_input_2, size_sample_input_2);
    compute_print_array(sample_input_3, size_sample_input_3);

    // puzzle problem
    compute_print_array(puzzle_input, size_puzzle_input);*/

    free(puzzle_input);

    int* noun_verb_address = find_noun_verb(PUZZLE_INPUT, size_puzzle_input, 19690720);
    printf("pos 1: %d\npos 2: %d\n",noun_verb_address[0], noun_verb_address[1]);

    return 0;
}
