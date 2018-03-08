#include <stdint.h>

struct indblock{
   uint32_t blocks[4096];
};

struct dindblock {
    struct indblock blocks[4096];
};

struct tindblock {
    struct dindblock blocks[4096];
};

struct inode {
    char data[52]; /* not bothering to retype the details */
    struct indblock ind;
    struct dindblock dint;
    struct tindblock tind;
};

struct inode bbtinode;

int main(){}

