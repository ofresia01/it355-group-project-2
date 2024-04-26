package chat_room;

/*
 * Driver for the chat room application.
 * Invokes ChatServer's main method.
 * No objects are compared by reference in the package, conformant with CWE-595.
 * No methods return mutable objects to untrusted callers - conformant with CWE-375.
 * No usage of `NullPointerException` throwable to detect NULL pointer dereference - conformant with CWE-395.
 * No Files call System.exit() outside of the main method, compliant with CWE-382.
 */
public class Main {
    public static void main(String[] args) {
        ChatServer.main(args);
    }
}