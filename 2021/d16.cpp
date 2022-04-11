#include "common.h"

const string input =
    "005410C99A9802DA00B43887138F72F4F652CC0159FE05E802B3A572DBBE5AA5F56F6B6A4600FCCAACEA9CE0E10020"
    "13A55389B064C0269813952F983595234002DA394615002A47E06C0125CF7B74FE00E6FC470D4C0129260B005E73FC"
    "DFC3A5B77BF2FB4E0009C27ECEF293824CC76902B3004F8017A999EC22770412BE2A1004E3DCDFA146D00020670B9C"
    "0129A8D79BB7E88926BA401BAD004892BBDEF20D253BE70C53CA5399AB648EBBAAF0BD402B95349201938264C7699C"
    "5A0592AF8001E3C09972A949AD4AE2CB3230AC37FC919801F2A7A402978002150E60BC6700043A23C618E200086447"
    "82F10C80262F005679A679BE733C3F3005BC01496F60865B39AF8A2478A04017DCBEAB32FA0055E6286D31430300AE"
    "7C7E79AE55324CA679F9002239992BC689A8D6FE084012AE73BDFE39EBF186738B33BD9FA91B14CB7785EC01CE4DCE"
    "1AE2DCFD7D23098A98411973E30052C012978F7DD089689ACD4A7A80CCEFEB9EC56880485951DB00400010D8A30CA1"
    "500021B0D625450700227A30A774B2600ACD56F981E580272AA3319ACC04C015C00AFA4616C63D4DFF289319A9DC40"
    "1008650927B2232F70784AE0124D65A25FD3A34CC61A6449246986E300425AF873A00CD4401C8A90D60E8803D08A0D"
    "C673005E692B000DA85B268E4021D4E41C6802E49AB57D1ED1166AD5F47B4433005F401496867C2B3E7112C0050C20"
    "043A17C208B240087425871180C01985D07A22980273247801988803B08A2DC191006A2141289640133E80212C3D2C"
    "3F377B09900A53E00900021109623425100723DC6884D3B7CFE1D2C6036D180D053002880BC530025C00F700308096"
    "110021C00C001E44C00F001955805A62013D0400B400ED500307400949C00F92972B6BC3F47A96D21C573004700377"
    "0004323E44F8B80008441C8F51366F38F240";

using sv = string_view;

int64_t get_bits(sv& bits, int d)
{
    assert(~bits >= d);
    int64_t k = 0;
    FOR (i, 0, < d) {
        auto ch = bits[i];
        assert(ch == '0' || ch == '1');
        int b = ch == '1' ? 1 : 0;
        k <<= 1;
        k = k | b;
    }
    bits.remove_prefix(d);
    return k;
}

int64_t get_literal_number(sv& bits)
{
    int64_t k = 0;
    for (; ~bits >= 5;) {
        int next1 = get_bits(bits, 1);
        int next4 = get_bits(bits, 4);
        k = k << 4;
        k = k | next4;
        if (!next1) {
            break;
        }
    }
    return k;
}
struct ER
{
    optional<int64_t> i;
    int64_t version_sum = 0;
};

ER combine(int64_t typeid_, ER era, ER erb)
{
    era.version_sum += erb.version_sum;
    switch (typeid_) {
        case 0:
            era.i = era.i.value_or(0) + erb.i.value();
            break;
        case 1:
            era.i = era.i.value_or(1) * erb.i.value();
            break;
        case 2:
            era.i = std::min(era.i.value_or(INT64_MAX), erb.i.value());
            break;
        case 3:
            era.i = std::max(era.i.value_or(INT64_MIN), erb.i.value());
            break;
        case 5:
            if (!era.i) {
                era.i = erb.i;
            } else {
                era.i = era.i.value() > erb.i.value() ? 1 : 0;
            }
            break;
        case 6:
            if (!era.i) {
                era.i = erb.i;
            } else {
                era.i = era.i.value() < erb.i.value() ? 1 : 0;
            }
            break;
        case 7:
            if (!era.i) {
                era.i = erb.i;
            } else {
                era.i = era.i.value() == erb.i.value() ? 1 : 0;
            }
            break;
    }
    return era;
}

ER eval(sv& bs)
{
    auto version = get_bits(bs, 3);
    auto typeid_ = get_bits(bs, 3);
    if (typeid_ == 4) {
        // literal
        auto ln = get_literal_number(bs);
        return ER{ln, version};
    }
    auto length_type_id = get_bits(bs, 1);
    ER er;
    if (length_type_id == 0) {
        auto total_subpacket_length = get_bits(bs, 15);
        auto rem = ~bs - total_subpacket_length;
        assert(rem >= 0);
        for (; ~bs > rem;) {
            er = combine(typeid_, er, eval(bs));
        }
        assert(~bs == rem);
    } else {
        auto subpacket_count = get_bits(bs, 11);
        FOR (i, 0, < subpacket_count) {
            er = combine(typeid_, er, eval(bs));
        }
    }
    return er;
}

int main()
{
    string bits;
    for (auto c : input) {
        assert(isxdigit(c));
        c = (char)tolower(c);
        int n;
        if (isdigit(c)) {
            n = c - '0';
        } else {
            n = c - 'a' + 10;
        }
        for (int i = 3; i >= 0; --i) {
            bits += (n & (1 << i)) ? '1' : '0';
        }
    }

    sv bs = bits;
    ER er = eval(bs);

    printf("left: %d bits\n", ~bs);
    printf("version_sum: %lld\n", er.version_sum);
    printf("value: %lld\n", er.i.value());

    return 0;
}
