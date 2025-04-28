#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Function to find the request with the shortest seek time
int findShortestSeekTime(int requests[], int n, int head, int processed[]) {
    int min_distance = INT_MAX;
    int min_index = -1;

    for (int i = 0; i < n; i++) {
        if (!processed[i]) {
            int distance = abs(requests[i] - head);
            if (distance < min_distance) {
                min_distance = distance;
                min_index = i;
            }
        }
    }
    
    return min_index;
}

// Function to simulate SSTF disk scheduling
void SSTF(int requests[], int n, int head) {
    if (n <= 0) {
        printf("No requests to process.\n");
        return;
    }

    // Array to track processed requests
    int processed[n];
    for (int i = 0; i < n; i++) {
        processed[i] = 0;
    }

    // To store the seek sequence
    int seek_sequence[n + 1];
    seek_sequence[0] = head;

    // Total seek time
    int total_seek_time = 0;
    int current_head = head;
    int count = 0;

    printf("\nSeek Sequence: %d", head);

    // Process all requests
    while (count < n) {
        // Find the next request with the shortest seek time
        int next_index = findShortestSeekTime(requests, n, current_head, processed);
        
        if (next_index == -1) break; // No more unprocessed requests
        
        // Mark the request as processed
        processed[next_index] = 1;
        
        // Calculate seek time for this request
        int seek_time = abs(requests[next_index] - current_head);
        total_seek_time += seek_time;
        
        // Update current head position
        current_head = requests[next_index];
        
        // Add to seek sequence
        count++;
        seek_sequence[count] = current_head;
        
        printf(" -> %d", current_head);
    }

    printf("\n\nTotal Seek Time: %d\n", total_seek_time);
    printf("Average Seek Time: %.2f\n", (float)total_seek_time / n);
    
    // Display the seek sequence visualization
    printf("\nSeek Sequence Visualization:\n");
    printf("Head position: %d\n\n", head);
    
    // Find the disk range for visualization
    int min_cylinder = head;
    int max_cylinder = head;
    
    for (int i = 0; i < n; i++) {
        if (requests[i] < min_cylinder) min_cylinder = requests[i];
        if (requests[i] > max_cylinder) max_cylinder = requests[i];
    }
    
    // Print a simple visualization
    for (int i = 0; i <= count; i++) {
        int position = seek_sequence[i];
        
        // Print the cylinder number
        printf("Cylinder %3d: ", position);
        
        // Print a visual representation
        for (int j = 0; j < position; j++) {
            printf(" ");
        }
        printf("*\n");
        
        // Print an arrow for movement
        if (i < count) {
            if (seek_sequence[i] < seek_sequence[i + 1]) {
                printf("             ↓\n");  // Moving down (higher cylinder)
            } else {
                printf("             ↑\n");  // Moving up (lower cylinder)
            }
        }
    }
}

int main() {
    int n, head;
    
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    
    int requests[n];
    
    printf("Enter the disk request sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    
    printf("\nSSTF Disk Scheduling Algorithm");
    SSTF(requests, n, head);
    
    return 0;
}