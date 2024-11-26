#include <stdio.h>

void getRefString(int *ref_string, int n)
{
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ref_string[i]);
    }
}

int findLRUPage(int *last_used, int frame_size) 
{
    int min = last_used[0];
    int pos = 0;

    for (int i = 1; i < frame_size; i++) 
    {
        if (last_used[i] < min) 
        {
            min = last_used[i];
            pos = i;
        }
    }

    return pos;
}

int main()
{
    int n;
    printf("Enter size of reference String: ");
    scanf("%d", &n);
    int ref_string[n];
    getRefString(ref_string, n);
    int frame_size;
    printf("Enter frame size: ");
    scanf("%d", &frame_size);
    int frame[frame_size];
    int last_used[frame_size]; 
    int hits = 0, page_faults = 0, time = 0;

   
    for (int i = 0; i < frame_size; i++)
    {
        frame[i] = -1;
        last_used[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < frame_size; j++)
        {
            if (frame[j] == ref_string[i])
            {
                hits++;
                found = 1;
                last_used[j] = time++;  
                break;
            }
        }

       
        if (!found)
        {
            int empty_found = 0;
           
            for (int j = 0; j < frame_size; j++)
            {
                if (frame[j] == -1)
                {
                    frame[j] = ref_string[i];
                    last_used[j] = time++; 
                    page_faults++;
                    empty_found = 1;
                    break;
                }
            }

            
            if (!empty_found)
            {
                int pos = findLRUPage(last_used, frame_size);
                frame[pos] = ref_string[i];
                last_used[pos] = time++; 
                page_faults++;
            }
        }
    }

    double hit_ratio = (double)hits / n;
    double page_fault_ratio = (double)page_faults / n;
    printf("Hits: %d\n", hits);
    printf("Page Faults: %d\n", page_faults);
    printf("Hit Ratio: %f\n", hit_ratio);
    printf("Page Fault Ratio: %f\n", page_fault_ratio);

    printf("Final frame state: ");
    for (int i = 0; i < frame_size; i++)
    {
        printf("%d ", frame[i]);
    }
    printf("\n");

    return 0;
}
