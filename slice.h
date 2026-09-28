#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

struct Slice 
{
    const char* data;
    u64 length;
};

struct OptionSlice 
{
    bool some;
    struct Slice value;
};

struct Slice slice_construct(const char* data, const u64 length)
{
    return (struct Slice){
        .data = data,
        .length = length
    };
}

struct Slice slice_construct_new_len(const struct Slice slice, const u64 new_length)
{
    return (struct Slice){
        .data = slice.data,
        .length = new_length
    };
}

struct Slice slice_slice(const struct Slice slice, const u32 index)
{
    assert(index <= slice.length);

    const u32 new_length = slice.length - index;
    return (struct Slice) {
        .data = &slice.data[index],
        .length = new_length
    };
}

void slicef(const struct Slice slice, char buffer[slice.length + 1])
{
    const void* _ = memcpy(buffer, slice.data, slice.length);
    buffer[slice.length] = '\0';
}



struct Slice slice_construct0(const char* data)
{
    return slice_construct(data, strlen(data));
}

void slice_construct_from_array0(const char* data[], const u32 count, struct Slice array[count])
{

    for (u32 i = 0; i < count; i++) {
        array[i] = slice_construct0(data[i]);
    }
}

struct OptionSlice option_slice_some(struct Slice value) 
{
    return (struct OptionSlice) {
        .some = true,
        .value = value
    };
}

struct OptionSlice option_slice_none(void)
{
    return (struct OptionSlice) {
        .some = false,
        .value = (struct Slice){0}
    };
}