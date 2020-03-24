/**
 * This class provides some worked examples of some methods which are similar
 * to some of those that you will have to implement in your assignment. If you
 * are having trouble, try looking at these to see how you could approach each
 * problem.
 */

public class Examples {
    int bitVector; // an int whose bits will be individually manipulated

    /**
     * This method clears the fourth bit (from the right) of the bit vector
     * declared above. This is very similar to the clear method you will have to
     * implement in the BitVector.java file, and the general approach should
     * help you to figure out some of the other problems.
     *
     * Example: If bitVector has the binary value 0000001101010111, then after
     *          calling this method it will be    0000001101000111.
     *
     */
    public void clearFourthBitOfBitVector() {
        int mask = 0x1; // mask is 000000000000000000000000000000001

        mask = mask << 4; // mask is now 00000000000000000000000000010000

        mask = ~mask; // mask is now 11111111111111111111111111101111

        /*
        Recall that a bitwise AND (&) of 1 and any other bit will be the
        other bit, and recall that a bitwise AND of 0 and any other bit will
        be 0.
        This means that when we AND a bit vector with our mask, wherever
        there is a 1 in the mask, the bit vector keeps its initial value, and
        wherever there is a 0 in the mask, the bit vector will become 0.
        */
        bitVector = bitVector & mask; // clears the fourth bit of the bit vector
    }

    /**
     * Note that many of the methods in this homework assignment need to be
     * implemented in one line. This can be very tricky to do all at once, so
     * we will demonstrate how you could do so after finding a multiline
     * solution.
     *
     * If we wanted to convert our above code into one line, we could make the
     * following changes:
     *
     *    1. Notice that we can replace the first use of mask with its literal
     *       value, giving us:
     *          short mask = 0x1;
     *          mask = 0x1 << 4; // was previously: mask = mask << 4
     *          mask = ~mask;
     *          bitVector = bitVector & mask;
     *
     *   2. Notice that we now assign mask the value 0x1 << 4 before we ever
     *      use its value of 0x1 from the first line. This means that we can
     *      combine the first and second line as follows:
     *          short mask = 0x1 << 4;
     *          mask = ~mask;
     *          bitVector = bitVector & mask;
     *
     *   3. Repeat the procedure in step 1 to get:
     *          short mask = 0x1 << 4;
     *          mask = ~(0x1 << 4);
     *          bitVector = bitVector & mask;
     *
     *   4. Again, notice that this makes the first assignment useless, so
     *      repeat the procedure in step 2:
     *          short mask = ~(0x1 << 4);
     *          bitVector = bitVector & mask;
     *
     *   5. Now we see that we can replace mask in the last line with the
     *      literal value of mask from the first line, yielding our final
     *      answer:
     *          bitVector = bitVector & ~(0x1 << 4);
     *
     * If your multiline solution can't be reduced to 1 line on this assignment,
     * there is probably a simpler way to approach the problem.
     */

    /**
     * This method does the same thing as the method above, but is implemented
     * more efficiently.
     */
    public void clearFourthBitOfBitVectorInOneLine() {
        bitVector = bitVector & ~(0x1 << 4);
    }


    /**
     * Converts the rightmost (least significant) two hex digits of an unsigned
     * int to a String. Remember that a hex digit, from 0 to F, is 4 bits long,
     * so our answer should always return 4 bits.
     * @param number an arbitrary unsigned int
     * @return a String corresponding to the hex value of the rightmost two
     *         hex digits of number
     *
     * Example: hexDigitToString(0x1234) -> "34"
     *          hexDigitToString(0xABCD) -> "CD"
     *          // Remember that all ints are actually represented as binary.
     *          // While we can write and display them as hex for convenience,
     *          // they are still binary, and we can write them as such.
     *          hexDigitToString(0b0001001000110100) -> "34"
     *          hexDigitToString(0b1010101111001101) -> "CD"
     *          // We could also write them with their decimal values, though
     *          // this hides what is actually going on and makes your code much
     *          // more difficult to read.
     *          hexDigitToString(4660) -> "34"
     *          hexDigitToString(43981) -> "CD"
     *
     */
    public String rightmostTwoHexDigitsToString(int number)
    {
        String result = ""; // empty String where we will store our answer

        /*
        In order to isolate the rightmost hex digit of our number, we must get
        the number's rightmost 4 bits. We can do this with the same AND
        technique that we showed above, but with the bitmask 0b1111 == 0xF
        instead. If we AND anything with 0b1111, all of the bits on the left
        side will become 0, but the rightmost 4 bits will not change.
        */
        int rightmostHexDigit = number & 0xF;

        /*
        Recall that chars can be treated like numbers (so we can do arithmetic
        with them), and that the number characters are sequential in the ASCII
        code (i.e '0' == 48, '1' == 49, '2' == 50, etc.). Letters are also
        sequential. The code below converts the number into its correct
        hex digit using a little math and prepends it to our string.
         */
        result = (rightmostHexDigit <= 9
                 ? (char) ('0' + rightmostHexDigit) // If digit has magnitude <= 9, it should be a number
                 : (char) ('A' + (rightmostHexDigit - 10))) // If digit is magnitude 10 or more, it must be A-F
                 + result;

        /*
        At this point, result contains the first hexadecimal character of our
        answer, so we need to move on to the next hexadecimal digit to convert.
        To do this, we can shift our number to the right by 4 to move the next
        hex digit to the rightmost position. Then, we can mask with 0xF as we
        did earlier to just get the 4 bits at the end that we want.
        */
        number = number >> 4;
        rightmostHexDigit = number & 0xF;

        /*
        After isolating the correct 4 bits, we can convert them to a character
        in exactly the same way that we did before.
        */
        result = (rightmostHexDigit <= 9
                 ? (char) ('0' + rightmostHexDigit)
                 : (char) ('A' + (rightmostHexDigit - 10)))
                 + result;

        // The result should now contain the rightmost two hex digits of the
        // original number.
        return result;
    }
}
