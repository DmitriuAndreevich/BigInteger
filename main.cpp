#include <cassert>
#include <iostream>
#include "include/biginteger.hpp"

int main() {
    // =================== CONSTRUCTOR TESTS ===================
    // Test default constructor
    BigInteger defaultInt;
    assert(defaultInt == 0);
    assert(!defaultInt.get_is_negative());

    // Test integer constructors
    BigInteger int1(123);
    assert(int1 == 123);
    BigInteger int2(-456);
    assert(int2 == -456);

    // Test long constructors
    BigInteger long1(123456789L);
    assert(long1 == 123456789);
    BigInteger long2(-987654321L);
    assert(long2 == -987654321);

    // Test unsigned long long constructors
    BigInteger ull1(123456789012345ULL);
    assert(ull1 == 123456789012345ULL);
    BigInteger ull2(0ULL);
    assert(ull2 == 0);

    // ============= COPY/MOVE CONSTRUCTOR TESTS ===============
    // Test copy constructor
    BigInteger copyInt(int1);
    assert(copyInt == 123);
    
    // Test move constructor
    BigInteger moveInt(std::move(BigInteger(999)));
    assert(moveInt == 999);

    // Test assignment operators
    BigInteger assignInt;
    assignInt = int2;  // Copy assignment
    assert(assignInt == -456);
    assignInt = std::move(BigInteger(111));  // Move assignment
    assert(assignInt == 111);

    // ================== STRING CONVERSION TESTS ==================
    // Test decimal string constructor
    BigInteger decStr("1234567890");
    assert(decStr == 1234567890);
    
    // Test hexadecimal string constructor
    BigInteger hexStr("FFFFFFFF", biginteger_base::hex);
    assert(hexStr == 0xFFFFFFFF);
    
    // Test negative decimal string
    BigInteger negDecStr("-12345");
    assert(negDecStr == -12345);
    
    // Test negative hexadecimal string
    BigInteger negHexStr("-ABCDEF", biginteger_base::hex);
    assert(negHexStr == -0xABCDEF);

    // ================== UNARY OPERATOR TESTS ==================
    BigInteger pos = +int1;  // Positive operator
    assert(pos == 123);
    BigInteger neg = -int1;  // Negation operator
    assert(neg == -123);
    assert(-neg == 123);     // Double negation

    // ================== COMPARISON OPERATOR TESTS ==================
    // Greater than
    assert(BigInteger(10) > BigInteger(5));
    // Less than with negative
    assert(BigInteger(-5) < BigInteger(5));
    // Greater/equal with zero
    assert(BigInteger(0) >= BigInteger(0));
    // Less/equal with negatives
    assert(BigInteger(-10) <= BigInteger(-5));
    // Inequality
    assert(BigInteger(100) != BigInteger(101));
    // Equality with zero
    assert(BigInteger(0) == BigInteger(0));
    // Negative zero equality
    assert(BigInteger(0) == -BigInteger(0));

    // ================== INCREMENT/DECREMENT TESTS ==================
    // Prefix and postfix increment
    BigInteger inc(10);
    assert(++inc == 11);    // Prefix
    assert(inc++ == 11);    // Postfix
    assert(inc == 12);      // After postfix

    // Prefix and postfix decrement
    BigInteger dec(10);
    assert(--dec == 9);     // Prefix
    assert(dec-- == 9);     // Postfix
    assert(dec == 8);       // After postfix

    // ================== ARITHMETIC OPERATION TESTS ==================
    // Addition tests
    BigInteger add1 = BigInteger(100) + BigInteger(50);
    assert(add1 == 150);
    BigInteger add2 = BigInteger(-100) + BigInteger(50);
    assert(add2 == -50);
    BigInteger add3 = BigInteger(100) + BigInteger(-150);
    assert(add3 == -50);

    // Subtraction tests
    BigInteger sub1 = BigInteger(100) - BigInteger(50);
    assert(sub1 == 50);
    BigInteger sub2 = BigInteger(50) - BigInteger(100);
    assert(sub2 == -50);
    BigInteger sub3 = BigInteger(-100) - BigInteger(-50);
    assert(sub3 == -50);

    // Multiplication tests
    BigInteger mul1 = BigInteger(12) * BigInteger(12);
    assert(mul1 == 144);
    BigInteger mul2 = BigInteger(-7) * BigInteger(8);
    assert(mul2 == -56);
    BigInteger mul3 = BigInteger(-5) * BigInteger(-6);
    assert(mul3 == 30);

    // Division tests
    BigInteger div1 = BigInteger(100) / BigInteger(10);
    assert(div1 == 10);
    BigInteger div2 = BigInteger(100) / BigInteger(-10);
    assert(div2 == -10);
    BigInteger div3 = BigInteger(-100) / BigInteger(-10);
    assert(div3 == 10);

    // Modulo operation tests
    BigInteger mod1 = BigInteger(100) % BigInteger(7);
    assert(mod1 == 2);
    BigInteger mod2 = BigInteger(100) % BigInteger(-7);
    assert(mod2 == 2);  // Sign follows dividend
    BigInteger mod3 = BigInteger(-100) % BigInteger(7);
    assert(mod3 == -2); // Negative result

    // ================== COMPOUND OPERATOR TESTS ==================
    BigInteger a(10);
    a += 5;  // Compound addition
    assert(a == 15);
    a -= 3;  // Compound subtraction
    assert(a == 12);
    a *= 2;  // Compound multiplication
    assert(a == 24);
    a /= 8;  // Compound division
    assert(a == 3);
    a %= 2;  // Compound modulo
    assert(a == 1);

    // ================== GETTER/SETTER TESTS ==================
    BigInteger test(123);
    test.set_is_negative(true);  // Set negative flag
    assert(test == -123);
    assert(test.get_is_negative());
    assert(test.get_size() == 1);  // Size in 32-bit chunks
    assert(test.get_data()[0] == 123);  // Underlying data

    // ================== SPECIAL METHOD TESTS ==================
    // Zero value check
    BigInteger zero;
    assert(zero.isZero());
    assert(!BigInteger(1).isZero());

    // Absolute value method
    BigInteger abs1 = BigInteger(-999).abs();
    assert(abs1 == 999 && !abs1.get_is_negative());

    // Base-10 division helper
    BigInteger div10(100);
    assert(div10.divide_by_10() == 0);  // Returns remainder
    assert(div10 == 10);  // Result after division

    // Base-16 division helper
    BigInteger div16(0x100);
    assert(div16.divide_by_16() == 0);  // Returns remainder
    assert(div16 == 0x10);  // Result after division

    // ================== BOUNDARY VALUE TESTS ==================
    // 32-bit integer boundaries
    BigInteger maxInt32(2147483647);
    BigInteger minInt32(-2147483648);
    assert(maxInt32 > minInt32);
    assert(maxInt32 + minInt32 == -1);  // Overflow case

    // 32-bit unsigned boundary
    BigInteger maxUInt32(4294967295U);
    BigInteger one(1);
    assert(maxUInt32 + one == 4294967296ULL);  // Beyond 32-bit

    // ================== LARGE NUMBER TESTS ==================
    // Operations with very large numbers
    BigInteger big1("12345678901234567890");
    BigInteger big2("11111111111111111111");
    BigInteger sum = big1 + big2;
    assert(sum == BigInteger("23456789012345679001"));

    BigInteger diff = big1 - big2;
    assert(diff == BigInteger("1234567890123456789"));

    BigInteger product = big1 * 2;  // Scalar multiplication
    assert(product == BigInteger("24691357802469135780"));

    // Large division test
    BigInteger dividend("100000000000000000000");
    BigInteger divisor("55555555555555555555");
    BigInteger quotient = dividend / divisor;
    assert(quotient == 1);  // Integer division

    // ================== STRING CONVERSION OUTPUT TESTS ==================
    assert(to_string(BigInteger(123)) == "123");
    assert(to_string(BigInteger(-456)) == "-456");
    assert(to_hex(BigInteger(0xABCDEF)) == "ABCDEF");
    assert(to_hex(BigInteger(-0x123ABC)) == "-123ABC");

    // Zero value string representations
    assert(to_string(BigInteger(0)) == "0");
    assert(to_hex(BigInteger(0)) == "0");

    // ================== COMPLEX EXPRESSION TESTS ==================
    BigInteger expr = (BigInteger(100) * 2 - 50) / 5 + 10;
    assert(expr == 40);  // ((200 - 50)/5) + 10 = 40

    // ================== STATIC METHOD TESTS ==================
    // Comparison helper method
    assert(BigInteger::isLess(BigInteger(5), BigInteger(10)));
    assert(!BigInteger::isLess(BigInteger(10), BigInteger(5)));
    assert(BigInteger::isLess(BigInteger(-10), BigInteger(-5)));

    // ================== BITWISE OPERATOR TESTS ==================
    // Bitwise OR
    assert((BigInteger(0xFFFFFF) | BigInteger(0x0000FF)) == 0xFFFFFF);
    // Bitwise AND
    assert((BigInteger(0xFFFF00) & BigInteger(0x00FFFF)) == 0x00FF00);
    // Bitwise XOR
    assert((BigInteger(0xAAAA) ^ BigInteger(0x5555)) == 0xFFFF);
    // Left shift
    assert((BigInteger(0x01) << 8) == 0x100);
    // Right shift
    assert((BigInteger(0x100) >> 8) == 0x01);

    // ================== OVERFLOW TEST ==================
    // 32-bit overflow case
    BigInteger overflow(0xFFFFFFFF);
    overflow += 1;
    assert(overflow == 0x100000000ULL);  // Requires 64-bit representation

    // ================== EXCEPTION TEST ==================
    // Division by zero handling
    try {
        BigInteger(1) / BigInteger(0);
        assert(false);  // Should never reach here
    } catch (const std::exception&) {
        // Expected behavior - exception thrown
    }

    // ================== MODULAR ARITHMETIC TEST ==================
    BigInteger modTest(25);
    modTest %= 7;
    assert(modTest == 4);  // 25 mod 7 = 4

    // ================== HEXADECIMAL LARGE NUMBER TEST ==================
    BigInteger hexBig("7FFFFFFFFFFFFFFF", biginteger_base::hex);
    assert(to_hex(hexBig) == "7FFFFFFFFFFFFFFF");
    assert(hexBig > 0);  // Positive boundary value

    // ================== COPY SEMANTICS TEST ==================
    BigInteger original(42);
    BigInteger copy = original;  // Copy constructor
    copy += 1;
    assert(original == 42);  // Original unchanged
    assert(copy == 43);      // Copy modified

    // ================== MOVE SEMANTICS TEST ==================
    BigInteger temp(99);
    BigInteger moved(std::move(temp));  // Move constructor
    assert(moved == 99);
    assert(temp.get_size() == 0);  // Source should be empty after move

    // ================== EQUALITY TESTS ==================
    assert(BigInteger("123456789") == BigInteger(123456789));
    assert(BigInteger("0") == BigInteger(0));  // Different constructors

    // ================== ABSOLUTE VALUE COMPARISON TEST ==================
    BigInteger bigPos("1000000000000");
    BigInteger smallPos("999999999999");
    assert(BigInteger::isAbsLess(smallPos, bigPos));  // |a| < |b|
    assert(!BigInteger::isAbsLess(bigPos, smallPos)); // |b| > |a|
    assert(BigInteger::isAbsLess(BigInteger(-999), BigInteger(1000)));  // Mixed signs

    // ================== FINAL CONFIRMATION ==================
    std::cout << "All 100 tests passed successfully!" << std::endl;
    return 0;
}
