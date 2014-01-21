#include "vk/vk_data.h"

int main(int argc, char **argv) {
        VkData data;
        if (argc > 1 && data.LoadCSV(argv[1])) {
                return 0;
        } else
                return 1;
}
