# Test file to test binary packing of a specfic message in python
# The goal of this program is to test the 2 different binary packing
# methods Miko found. The 2 methods are using the struct library (option 1)
# and using the cstruct library (option 2)

import struct
import cstruct

struct_string = """
    struct reaction{
        uint64_t emoji;
        int32_t count;
    } 
"""

# class definition for method 2
class reaction(cstruct.MemCStruct):
    #########################
    # WEIRD BEHAVIOR:
    # for some reason you have 
    # to specify the byte_order as little endian
    # or you will encounter unexpected behavior
    # where the size of each element of the struct
    # is set to the largest element. You cant specify
    # native order either since the problem persists.
    # You can see this by printing the binary string with and
    # without the __byte_order__ set. Would appreciate if someone
    # else could take a look at and see what is going it
    ########################
    __byte_order__ = cstruct.LITTLE_ENDIAN
    __def__ = struct_string




# In order to test these 2 methods we have to test how they would work
# if we attempted to pack a specific test example into a binary form.
# We choose the reaction message specified in the schema XML and basic.c
# as the specific instance of a message that we will try to pack into
# a binary form. 
# 
# The emoji field will be a uint64_t with a value of 6 and the count
# will be a int32_t with a value of 1023
def main():

    ## Method/option 2, use the cstruct library
    r = reaction(emoji = 6, count = 1023)
    print("Method 2 prints:")
    print(r.pack())
    print('\n')

    ## Method/option 1, use the struct library

    print("Method 1 prints")
    # Use < to enforce little endian, if you don't use this it 
    # defaults to native and size and order and you get
    # the same behavior as in option 2 I guess that mean, native
    # size and order just don't work as I expected them to
    print(struct.pack('<Ql', 6, 1023))
    return

if __name__ == '__main__':
    main()