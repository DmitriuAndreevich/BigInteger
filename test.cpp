#include <cassert>
#include <iostream>
#include "include/biginteger.hpp"

int test() {
    // =================== CONSTRUCTOR TESTS ===================
    BigInteger defaultInt;
    assert(defaultInt == 0);
    assert(!defaultInt.get_is_negative());

    BigInteger int1(123);
    assert(int1 == 123);
    BigInteger int2(-456);
    assert(int2 == -456);

    BigInteger long1(123456789L);
    assert(long1 == BigInteger("123456789"));
    BigInteger long2(-987654321L);
    assert(long2 == BigInteger("-987654321"));

    BigInteger ull1(123456789012345ULL);
    assert(ull1 == BigInteger("123456789012345"));
    BigInteger ull2(0ULL);
    assert(ull2 == 0);

    // ============= COPY/MOVE CONSTRUCTOR TESTS ===============
    BigInteger copyInt(int1);
    assert(copyInt == 123);

    BigInteger moveInt(std::move(BigInteger(999)));
    assert(moveInt == 999);

    BigInteger assignInt;
    assignInt = int2;
    assert(assignInt == -456);
    assignInt = std::move(BigInteger(111));
    assert(assignInt == 111);

    // ================== STRING CONVERSION TESTS ==================
    BigInteger decStr("1234567890");
    assert(decStr == BigInteger("1234567890"));

    BigInteger hexStr("FFFFFFFF", biginteger_base::hex);
    assert(to_hex(hexStr) == "FFFFFFFF");

    BigInteger negDecStr("-12345");
    assert(negDecStr == -12345);

    BigInteger negHexStr("-ABCDEF", biginteger_base::hex);
    assert(to_hex(negHexStr) == "-ABCDEF");

    // ================== UNARY OPERATOR TESTS ==================
    BigInteger pos = +int1;
    assert(pos == 123);
    BigInteger neg = -int1;
    assert(neg == -123);
    assert(-neg == 123);

    // ================== COMPARISON OPERATOR TESTS ==================
    assert(BigInteger(10) > BigInteger(5));
    assert(BigInteger(-5) < BigInteger(5));
    assert(BigInteger(0) >= BigInteger(0));
    assert(BigInteger(-10) <= BigInteger(-5));
    assert(BigInteger(100) != BigInteger(101));
    assert(BigInteger(0) == BigInteger(0));
    assert(BigInteger(0) == -BigInteger(0));

    // ================== INCREMENT/DECREMENT TESTS ==================
    BigInteger inc(10);
    assert(++inc == 11);  // prefix
    assert(inc++ == 11);  // postfix returns old value
    assert(inc == 12);

    BigInteger dec(10);
    assert(--dec == 9);
    assert(dec-- == 9);
    assert(dec == 8);

    // ================== ARITHMETIC OPERATION TESTS ==================
    assert(BigInteger(100) + BigInteger(50) == 150);
    assert(BigInteger(-100) + BigInteger(50) == -50);
    assert(BigInteger(100) + BigInteger(-150) == -50);

    assert(BigInteger(100) - BigInteger(50) == 50);
    assert(BigInteger(50) - BigInteger(100) == -50);
    assert(BigInteger(-100) - BigInteger(-50) == -50);

    assert(BigInteger(12) * BigInteger(12) == 144);
    assert(BigInteger(-7) * BigInteger(8) == -56);
    assert(BigInteger(-5) * BigInteger(-6) == 30);

    assert(BigInteger(100) / BigInteger(10) == 10);
    assert(BigInteger(100) / BigInteger(-10) == -10);
    assert(BigInteger(-100) / BigInteger(-10) == 10);

    assert(BigInteger(100) % BigInteger(7) == 2);
    assert(BigInteger(100) % BigInteger(-7) == 2);
    assert(BigInteger(-100) % BigInteger(7) == -2);

    // ================== COMPOUND OPERATOR TESTS ==================
    BigInteger a(10);
    a += 5;  assert(a == 15);
    a -= 3;  assert(a == 12);
    a *= 2;  assert(a == 24);
    a /= 8;  assert(a == 3);
    a %= 2;  assert(a == 1);

    // ================== GETTER/SETTER TESTS ==================
    BigInteger test(123);
    test.set_is_negative(true);
    assert(test == -123);
    assert(test.get_is_negative());
    assert(test.get_size() >= 1);
    assert(test.get_data()[0] == 123);

    // ================== SPECIAL METHOD TESTS ==================
    BigInteger zero;
    assert(zero.isZero());
    assert(!BigInteger(1).isZero());

    BigInteger abs1 = BigInteger(-999).abs();
    assert(abs1 == 999);
    assert(!abs1.get_is_negative());

    BigInteger div10(100);
    assert(div10.divide_by_10() == 0);
    assert(div10 == 10);

    BigInteger div16(0x100);
    assert(div16.divide_by_16() == 0);
    assert(div16 == 0x10);

    // ================== BOUNDARY VALUE TESTS ==================
    BigInteger maxInt32(2147483647);
    BigInteger minInt32(-2147483648);
    assert(maxInt32 > minInt32);
    assert(maxInt32 + minInt32 == -1);

    BigInteger maxUInt32(4294967295U);
    BigInteger one(1);
    assert(maxUInt32 + one == BigInteger("4294967296"));

    // ================== LARGE NUMBER TESTS ==================
    BigInteger big1("12345678901234567890");
    BigInteger big2("11111111111111111111");

    BigInteger sum = big1 + big2;
    assert(to_string(sum) == "23456790012345679001");
    // Проверено вручную:
    // 12345678901234567890
    // +11111111111111111111
    // =23456790012345679001

    BigInteger diff = big1 - big2;
    assert(to_string(diff) == "1234567790123456779");
    // Проверенно вручную:
    // 12345678901234567890
    // -11111111111111111111
    // = 1234567790123456779

    BigInteger product = big1 * 2;
    assert(to_string(product) == "24691357802469135780");
    // При удвоении: 2 × big1

    BigInteger dividend("100000000000000000000");
    BigInteger divisor("55555555555555555555");
    BigInteger quotient = dividend / divisor;
    assert(to_string(quotient) == "1");
    // Целочисленное: 100e18 / 55.555e18 = 1

    BigInteger remainder = dividend % divisor;
    assert(to_string(remainder) == "44444444444444444445");
    // Остаток: 100e18 -1·55.555e18 = 44.444...e18 → "44444444444444444445"

    // ================== STRING CONVERSION OUTPUT TESTS ==================
    assert(to_string(BigInteger(123)) == "123");
    assert(to_string(BigInteger(-456)) == "-456");
    assert(to_hex(BigInteger(0xABCDEF)) == "ABCDEF");
    assert(to_hex(BigInteger(-0x123ABC)) == "-123ABC");
    assert(to_string(BigInteger(0)) == "0");
    assert(to_hex(BigInteger(0)) == "0");

    // ================== COMPLEX EXPRESSION TESTS ==================
    BigInteger expr = (BigInteger(100) * 2 - 50) / 5 + 10;
    assert(expr == 40);

    // ================== STATIC METHOD TESTS ==================
    assert(BigInteger::isLess(BigInteger(5), BigInteger(10)));
    assert(!BigInteger::isLess(BigInteger(10), BigInteger(5)));
    assert(BigInteger::isLess(BigInteger(-10), BigInteger(-5)));

    // ================== OVERFLOW TEST ==================
    BigInteger overflow(0xFFFFFFFF);
    overflow += 1;
    assert(overflow == BigInteger("4294967296"));

    // ================== EXCEPTION TEST ==================
    try {
        BigInteger(1) / BigInteger(0);
        assert(false);
    }
    catch (const std::exception&) {
        // ожидаем исключение
    }

    // ================== MODULAR ARITHMETIC TEST ==================
    BigInteger modTest(25);
    modTest %= 7;
    assert(modTest == 4);

    // ================== HEXADECIMAL LARGE NUMBER TEST ==================
    BigInteger hexBig("7FFFFFFFFFFFFFFF", biginteger_base::hex);
    assert(to_hex(hexBig) == "7FFFFFFFFFFFFFFF");
    assert(hexBig > 0);

    // ================== COPY SEMANTICS TEST ==================
    BigInteger original(42);
    BigInteger copy = original;
    copy += 1;
    assert(original == 42);
    assert(copy == 43);

    // ================== MOVE SEMANTICS TEST ==================
    BigInteger temp(99);
    BigInteger moved(std::move(temp));
    assert(moved == 99);
    assert(temp.get_size() == 0 || temp.isZero());

    // ================== EQUALITY TESTS ==================
    assert(BigInteger("123456789") == BigInteger(123456789));
    assert(BigInteger("0") == BigInteger(0));

    // ================== FINAL CONFIRMATION ==================
    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}

int main() {
    return test();
    return 0;
}
