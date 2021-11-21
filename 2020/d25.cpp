#include "common.h"

int64_t transform_subject_number(int64_t sn, int64_t loop_size)
{
    int64_t v = 1;
    for (int64_t i = 1; i <= loop_size; ++i) {
        v = v * sn;
        v = v % 20201227;
    }
    return v;
}

int64_t transform_subject_number_until(int64_t sn, int64_t target)
{
    int64_t v = 1;
    if (v == target) {
        return 0;
    }
    for (int64_t loop_size = 1;; ++loop_size) {
        v = v * sn;
        v = v % 20201227;
        if (v == target) {
            return loop_size;
        }
    }
}

int main()
{
#if 0
    // sample
    int64_t eavesdropped_card_public_key = 5764801;
    int64_t eavesdropped_door_public_key = 17807724;
#else
    // actual
    int64_t eavesdropped_card_public_key = 8458505;
    int64_t eavesdropped_door_public_key = 16050997;
#endif

    auto card_secret_loop_size = transform_subject_number_until(7, eavesdropped_card_public_key);
    printf("found card secret loop size %lld\n", card_secret_loop_size);

    auto door_secret_loop_size = transform_subject_number_until(7, eavesdropped_door_public_key);
    printf("found door secret loop size %lld\n", door_secret_loop_size);

    auto card_public_key = transform_subject_number(7, card_secret_loop_size);
    auto door_public_key = transform_subject_number(7, door_secret_loop_size);
    auto card_encryption_key = transform_subject_number(door_public_key, card_secret_loop_size);
    auto door_encryption_key = transform_subject_number(card_public_key, door_secret_loop_size);
    assert(card_encryption_key == door_encryption_key);

    printf("encryption key %lld\n", door_encryption_key);

    return 0;
}

// 20:44
