void kmain(void)
{
    unsigned char *VGA = (unsigned char*)0xB8000;
    VGA[0] = 'A';
    VGA[1] = 0x0A;

    while (1);
}