#include <stdio.h>

void getRefString(int *ref_string, int n)
{
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ref_string[i]);
    }
}

void fifoPageReplacement(int *ref_string, int n, int frame_size)
{
    int hits = 0, page_faults = 0, frame_ptr = 0;
    int frame[frame_size];
    double hit_ratio, page_fault_ratio;

    for (int i = 0; i < frame_size; i++)
    {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < frame_size; j++)
        {
            // if page is already in frame
            if (frame[j] == ref_string[i])
            {
                hits++;
                found = 1;
                break;
            }
        }

        if (found == 0)
        {

            frame[frame_ptr] = ref_string[i];
            page_faults++;
            frame_ptr = (frame_ptr + 1) % frame_size;
        }
    }
    hit_ratio = (double)hits / n;
    page_fault_ratio = (double)page_faults / n;
    printf("Hits: %d\n", hits);
    printf("Page Faults: %d\n", page_faults);
    printf("Hit Ratio: %f\n", hit_ratio);
    printf("Page Fault Ratio: %f\n", page_fault_ratio);
}

int main()
{
    int n, frame_size;
    printf("Enter size of reference String: ");
    scanf("%d", &n);
    int ref_string[n];
    getRefString(ref_string, n);
    printf("Enter frame size: ");
    scanf("%d", &frame_size);
    int frame[frame_size];

    for (int i = 0; i < frame_size; i++)
    {
        frame[i] = -1;
    }

    fifoPageReplacement(ref_string, n, frame_size);

    return 0;
}
