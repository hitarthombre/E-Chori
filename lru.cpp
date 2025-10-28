#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct PageInfo {
    int page;
    int last_used;
};

bool isPagePresent(struct PageInfo frames[], int num_frames, int page) {
    for(int i = 0; i < num_frames; i++) {
        if(frames[i].page == page) {
            return true;
        }
    }
    return false;
}

int findLRUReplacement(struct PageInfo frames[], int num_frames) {
    int lru_index = 0;
    int min_time = frames[0].last_used;
    for(int i = 1; i < num_frames; i++) {
        if(frames[i].last_used < min_time) {
            min_time = frames[i].last_used;
            lru_index = i;
        }
    }
    return lru_index;
}

void updatePageTime(struct PageInfo frames[], int num_frames, int page, int time) {
    for(int i = 0; i < num_frames; i++) {
        if(frames[i].page == page) {
            frames[i].last_used = time;
            break;
        }
    }
}

void displayFrames(struct PageInfo frames[], int num_frames, int fault, int current_time) {
    printf("Frames: ");
    for(int i = 0; i < num_frames; i++) {
        if(frames[i].page == -1) {
            printf("[ ] ");
        } else {
            printf("[%d(LU:%d)] ", frames[i].page, frames[i].last_used);
        }
    }
    if(fault) {
        printf("-> Page Fault");
    } else {
        printf("-> Page Hit");
    }
    printf("\n");
}

void lruPageReplacement(int pages[], int num_pages, int num_frames) {
    struct PageInfo frames[num_frames];
    int page_faults = 0;
    int time_counter = 0;
   
    for(int i = 0; i < num_frames; i++) {
        frames[i].page = -1;
        frames[i].last_used = -1;
    }
   
    printf("LRU Page Replacement Algorithm Simulation\n");
    printf("Number of frames: %d\n", num_frames);
    printf("Reference string: ");
    for(int i = 0; i < num_pages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\n");
   
    for(int i = 0; i < num_pages; i++) {
        int current_page = pages[i];
        time_counter++;
       
        printf("Time %2d: Referencing page %d - ", time_counter, current_page);
       
        if(!isPagePresent(frames, num_frames, current_page)) {
            page_faults++;
            bool frame_found = false;
            for(int j = 0; j < num_frames; j++) {
                if(frames[j].page == -1) {
                    frames[j].page = current_page;
                    frames[j].last_used = time_counter;
                    frame_found = true;
                    break;
                }
            }
            if(!frame_found) {
                int replace_index = findLRUReplacement(frames, num_frames);
                printf("Replacing page %d (last used at time %d) ",
                       frames[replace_index].page, frames[replace_index].last_used);
                frames[replace_index].page = current_page;
                frames[replace_index].last_used = time_counter;
            }
            displayFrames(frames, num_frames, 1, time_counter);
        } else {
            updatePageTime(frames, num_frames, current_page, time_counter);
            displayFrames(frames, num_frames, 0, time_counter);
        }
    }
   
    printf("\n=== Simulation Results ===\n");
    printf("Total Page Faults: %d\n", page_faults);
    printf("Total Page Hits: %d\n", num_pages - page_faults);
    printf("Page Fault Rate: %.2f%%\n", (float)page_faults/num_pages * 100);
}

void lruCounterImplementation(int pages[], int num_pages, int num_frames) {
    int frames[num_frames];
    int counters[num_frames];
    int page_faults = 0;
    int global_counter = 0;
   
    for(int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        counters[i] = 0;
    }
   
    printf("\n=== LRU Counter Implementation ===\n");
   
    for(int i = 0; i < num_pages; i++) {
        int current_page = pages[i];
        global_counter++;
        bool page_found = false;
       
        for(int j = 0; j < num_frames; j++) {
            if(frames[j] == current_page) {
                counters[j] = global_counter;
                page_found = true;
                break;
            }
        }
       
        if(!page_found) {
            page_faults++;
            int lru_index = 0;
            for(int j = 1; j < num_frames; j++) {
                if(frames[j] == -1) {
                    lru_index = j;
                    break;
                }
                if(counters[j] < counters[lru_index]) {
                    lru_index = j;
                }
            }
            frames[lru_index] = current_page;
            counters[lru_index] = global_counter;
        }
    }
   
    printf("Total Page Faults (Counter method): %d\n", page_faults);
}

int main() {
    int reference_string1[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int reference_string2[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int num_pages1 = sizeof(reference_string1) / sizeof(reference_string1[0]);
    int num_pages2 = sizeof(reference_string2) / sizeof(reference_string2[0]);
    int num_frames = 3;
   
    printf("=== TEST 1 ===\n");
    lruPageReplacement(reference_string1, num_pages1, num_frames);
   
    printf("\n=== TEST 2 ===\n");
    lruPageReplacement(reference_string2, num_pages2, num_frames);
   
    lruCounterImplementation(reference_string1, num_pages1, num_frames);
   
    return 0;
}

