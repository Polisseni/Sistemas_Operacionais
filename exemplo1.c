// Kernel mínimo em C

// kernel.c

void kernel_main() {
    char *video_memory = (char*) 0xB8000;

    video_memory[0] = 'O';
    video_memory[1] = 0x07; // cor

    video_memory[2] = 'S';
    video_memory[3] = 0x07;

    video_memory[4] = '!';
    video_memory[5] = 0x07;

    while (1); // loop infinito
}

// O que isso faz?
// 0xB8000 → endereço da memória de vídeo (modo texto)
// Cada caractere ocupa 2 bytes:
// 1 byte = letra
// 1 byte = cor
// O código escreve:
// 👉 OS! direto na tela

// Sem printf, sem stdio.h, sem sistema operacional — isso é bare metal.

// Bootloader (Assembly mínimo)

; boot.asm

[org 0x7c00]
mov ah, 0x0e
mov al, 'B'
int 0x10

jmp $

times 510-($-$$) db 0
dw 0xaa55

// Como isso vira um “SO”?

// Fluxo:

// BIOS carrega o bootloader
// Bootloader carrega o kernel
// Kernel executa (kernel_main)
// Você controla tudo