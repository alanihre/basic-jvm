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
