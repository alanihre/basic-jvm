class String {
    char[] value;

    String(char[] arr) {
        value = arr;
    }

    public char[] toCharArray() {
        return value;
    }

    int length() {
        return value.length;
    }

    char charAt(int index) {
        return value[index];
    }
}
