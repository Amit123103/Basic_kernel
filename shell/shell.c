#include "kernel.h"
#include "shell/shell.h"

static void shell_print_help(void) {
    kprintf("Available commands:\n");
    kprintf("  help   clear   version   time\n");
    kprintf("  memory cpu   reboot   shutdown\n");
    kprintf("  echo   about   ls   pwd\n");
}

static void shell_handle_command(const char *cmd) {
    if (cmd[0] == '\0') {
        return;
    }

    if (cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p' && cmd[4] == '\0') {
        shell_print_help();
    } else if (cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == 'e' && cmd[3] == 'a' && cmd[4] == 'r' && cmd[5] == '\0') {
        vga_clear();
    } else if (cmd[0] == 'v' && cmd[1] == 'e' && cmd[2] == 'r' && cmd[3] == 's' && cmd[4] == 'i' && cmd[5] == 'o' && cmd[6] == 'n' && cmd[7] == '\0') {
        kprintf("MyKernel version 0.1.0\n");
    } else if (cmd[0] == 't' && cmd[1] == 'i' && cmd[2] == 'm' && cmd[3] == 'e' && cmd[4] == '\0') {
        kprintf("RTC time not yet implemented\n");
    } else if (cmd[0] == 'm' && cmd[1] == 'e' && cmd[2] == 'm' && cmd[3] == 'o' && cmd[4] == 'r' && cmd[5] == 'y' && cmd[6] == '\0') {
        kprintf("Memory manager initialized\n");
    } else if (cmd[0] == 'c' && cmd[1] == 'p' && cmd[2] == 'u' && cmd[3] == '\0') {
        kprintf("x86_64 CPU detected\n");
    } else if (cmd[0] == 'r' && cmd[1] == 'e' && cmd[2] == 'b' && cmd[3] == 'o' && cmd[4] == 'o' && cmd[5] == 't' && cmd[6] == '\0') {
        kprintf("Reboot requested\n");
        acpi_reboot();
    } else if (cmd[0] == 's' && cmd[1] == 'h' && cmd[2] == 'u' && cmd[3] == 't' && cmd[4] == 'd' && cmd[5] == 'o' && cmd[6] == 'w' && cmd[7] == 'n' && cmd[8] == '\0') {
        kprintf("Shutdown requested\n");
        acpi_shutdown();
    } else if (cmd[0] == 'e' && cmd[1] == 'c' && cmd[2] == 'h' && cmd[3] == 'o' && cmd[4] == '\0') {
        kprintf("echo command placeholder\n");
    } else if (cmd[0] == 'a' && cmd[1] == 'b' && cmd[2] == 'o' && cmd[3] == 'u' && cmd[4] == 't' && cmd[5] == '\0') {
        kprintf("MyKernel educational OS shell\n");
    } else if (cmd[0] == 'l' && cmd[1] == 's' && cmd[2] == '\0') {
        kprintf(".") ; kprintf("\n");
    } else if (cmd[0] == 'p' && cmd[1] == 'w' && cmd[2] == 'd' && cmd[3] == '\0') {
        kprintf("/\n");
    } else {
        kprintf("Unknown command: ");
        kprintf(cmd);
        kprintf("\n");
    }
}

void shell_init(void) {
    kprintf("MyKernel shell initialized\n");
}

void shell_run(void) {
    static const char *commands[] = {
        "help",
        "clear",
        "version",
        "time",
        "memory",
        "cpu",
        "reboot",
        "shutdown",
        "echo",
        "about",
        "ls",
        "pwd"
    };

    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); ++i) {
        shell_handle_command(commands[i]);
    }
}
