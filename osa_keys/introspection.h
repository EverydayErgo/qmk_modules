#define SCROLL_DIVISOR_H 8.0
#define SCROLL_DIVISOR_V 8.0

typedef enum {
    NOT_FORCED,
    FORCED_MACOS,
    FORCED_WINDOWS
}osa_forced_os_t;

void force_macos(void);
void force_windows(void);
