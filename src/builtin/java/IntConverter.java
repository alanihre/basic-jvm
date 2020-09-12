class IntConverter {
    public static int stringSize(int num) {
        if (num == 0) {
            return 1;
        }
        int size = 0;
        while (num > 0) {
            num /= 10;
            size++;
        }

        return size;
    }

    public static char[] convert(int num) {
        int stringSize = 0;
        boolean negative = false;
        int bufOffset = 0;
        if (num < 0) {
            negative = true;
            bufOffset = 1;
            stringSize++;
            num = -num;
        }
        int intSize = stringSize(num);
        stringSize += intSize;

        char[] buf = new char[stringSize];

        if (negative) {
            buf[0] = '-';
        }

        for (int i = intSize - 1; i >= 0; i--) {
            int res = num % 10;
            buf[bufOffset + i] = (char)('0' + res);
            num -= res;
            num /= 10;
        }
        return buf;
    }
}

class StringBuilder {
    char[] buf;
    int size = 0;

    StringBuilder() {
        buf = new char[0];
    }

    void increaseSize(int delta) {
        char[] newBuf = new char[size + delta];
        for (int i = 0; i < size; i++) {
            newBuf[i] = buf[i];
        }
        size += delta;
        buf = newBuf;
    }

    public StringBuilder append(String str) {
        int oldSize = size;
        int strLen = str.length();
        increaseSize(strLen);
        for (int i = 0; i < strLen; i++) {
            buf[i + oldSize] = str.charAt(i);
        }
        return this;
    }

    public StringBuilder append(int num) {
        char[] charArray = IntConverter.convert(num);
        int oldSize = size;
        int strLen = charArray.length;
        increaseSize(strLen);
        for (int i = 0; i < strLen; i++) {
            buf[i + oldSize] = charArray[i];
        }
        return this;
    }

    public java.lang.String toString() {
        return new java.lang.String(buf);
    }
}
