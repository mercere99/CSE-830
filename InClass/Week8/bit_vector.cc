#include <iostream>
#include <assert.h>

class bit_vector {
private:
    using field_t = uint64_t;

    size_t num_bits;
    field_t * bit_set;

    static constexpr size_t FIELD_BITS = sizeof(field_t) * 8;
    static constexpr field_t FIELD_MASK = FIELD_BITS - 1;

    // -- Helper Functions --
    size_t NumFields() const {
        return (num_bits) ? (num_bits-1) / FIELD_BITS + 1 : 0;
    }

public:
    bit_vector(size_t in_bits) : num_bits(in_bits), bit_set(nullptr) {
        if (num_bits) bit_set = new field_t[NumFields()];
        Clear();
    }

    ~bit_vector() {
        if (bit_set != nullptr) delete [] bit_set;
    }

    void Clear() {
        for (size_t i = 0; i < NumFields(); i++) {
            bit_set[i] = 0;
        }
    }

    bool Get(size_t pos) {
        assert(pos < num_bits);
        size_t field_id = pos / FIELD_BITS;
        size_t bit_id = pos & FIELD_MASK;
        return (bit_set[field_id] >> bit_id) & 1;
    }

    void Set(size_t pos, bool val=true) {
        assert(pos < num_bits);
        size_t field_id = pos / FIELD_BITS;
        size_t bit_id = pos & FIELD_MASK;
        uint64_t mask = ((uint64_t) 1) << bit_id;
        if (val == true) {
            bit_set[field_id] |= mask;
        }
        else {
            bit_set[field_id] &= ~mask;
        }

    }
};

int main()
{
    constexpr size_t N = 1000;
    bit_vector bv(N);

    for (size_t i = 0; i < 80; i++) {
        std::cout << bv.Get(i);
    }
    std::cout << std::endl;

    // bv.Set(3);
    // bv.Set(5);
    // bv.Set(6);
    // bv.Set(9);
    // bv.Set(10);
    // bv.Set(12);
    // bv.Set(15);
    // bv.Set(18);
    // bv.Set(20);
    // bv.Set(21);

    // bv.Set(65);
    // bv.Set(66);
    // bv.Set(69);
    // bv.Set(70);

    for (size_t i = 0; i < 80; i++) {
        if ((i % 3)== 0) bv.Set(i);
        std::cout << i << " : ";
        for (size_t i = 0; i < 80; i++) {
            std::cout << bv.Get(i);
        }
        std::cout << std::endl;
//        if ((i % 3) == 0 || (i % 5) == 0) bv.Set(i);
    }

    for (size_t i = 0; i < 80; i++) {
        std::cout << bv.Get(i);
    }
    std::cout << std::endl;
}