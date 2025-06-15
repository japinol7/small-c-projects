#include "utils.h"
#include <string.h>

char* string_join(
    char** items, const int count, char* buffer, const size_t buffer_size
) {
    if (items == NULL || count <= 0 || buffer == NULL || buffer_size == 0) {
        return NULL;
    }

    buffer[0] = '\0'; // Init to an empty string
    size_t remaining = buffer_size - 1; // -1 for null terminator

    for (int i = 0; i < count; ++i) {
        const size_t item_len = strlen(items[i]);

        // Check if we have room for this item
        if (remaining < item_len + (i > 0 ? 1 : 0)) {
            break;
        }

        // Add newline between items
        if (i > 0) {
            strncat(buffer, "\n", remaining);
            remaining--;
        }

        strncat(buffer, items[i], remaining);
        remaining -= item_len;
    }

    return buffer;
}
