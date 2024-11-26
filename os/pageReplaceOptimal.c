#include <stdio.h>

void getRefString(int *ref_string, int n)
{
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ref_string[i]);
    }
}

int findOptimalPage(int *frame, int frame_size, int *ref_string, int n, int current_index)
{
    int farthest = current_index;
    int replace_index = -1;

    for (int i = 0; i < frame_size; i++)
    {
        int j;
        for (j = current_index + 1; j < n; j++)
        {
            if (frame[i] == ref_string[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    replace_index = i;
                }
                break;
            }
        }

              if (j == n) 
        {
            return i;
        }

             if (replace_index == -1) 
        {
            replace_index = i;
        }
    }

    return replace_index;
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
    int hits = 0, page_faults = 0;

      for (int i = 0; i < frame_size; i++)
    {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < frame_size; j++)
        {
            if (frame[j] == ref_string[i])
            {
                hits++;
                found = 1;
                break;
            }
        }

              if (!found)
        {
            int empty_found = 0;
            // Check if there's an empty frame available
            for (int j = 0; j < frame_size; j++)
            {
                if (frame[j] == -1)
                {
                    frame[j] = ref_string[i];
                    page_faults++;
                    empty_found = 1;
                    break;
                }
            }

            if (!empty_found)
            {
                // Find the page to replace using the optimal policy
                int pos = findOptimalPage(frame, frame_size, ref_string, n, i);
                frame[pos] = ref_string[i];
                page_faults++;
            }}}

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
