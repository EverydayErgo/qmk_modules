typedef enum {
    NOT_FORCED,
    FORCED_MACOS,
    FORCED_WINDOWS
}osa_forced_os_t;

void force_macos(void);
void force_windows(void);
