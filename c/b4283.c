#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>

int main(int a, char* b[]) {
    struct stat q;
    stat(b[1], &q); 

    int f = open(b[1], O_RDONLY);
    char* r = mmap(NULL, q.st_size, PROT_READ, MAP_PRIVATE, f, 0);
    
    char* g;
    int x[26] = { [0 ... 25] = 0 };

    for (g = r - 1; g != NULL; g = index(g + 1, '\n')) {
        if ((g - r) < q.st_size) {
            char m = toupper(*(g + 1));
            x[m - 'A'] += 1;
        }
    }

    int i;
    for (i = 0; i < 26; i+=1) {
        printf("%c %d\n", i + 'A', x[i]);
    }

    munmap(r, q.st_size);        
    close(f);
}
