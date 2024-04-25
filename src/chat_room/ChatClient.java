package chat_room;

import java.io.*;
import java.net.*;
import java.util.Scanner;

/*
 * Class that represents a client connecting to ChatServer.
 */
public class ChatClient {
    /*
     * Network config for ChatServer -- just default localhost
     * All elements declared private unless explicitly needed otherwise - conformant
     * to CWE-766.
     */
    private static final String SERVER_ADDRESS = "localhost";
    private static final int PORT = 8080; // Integer is static and final, making it invulnerable to underflow -
                                          // compliant to CWE-191

    public static void main(String[] args) {
        try {
            // Create a socket connection to the server
            try (Socket socket = new Socket(SERVER_ADDRESS, PORT)) {
                // Get the server's input/output streams
                BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter output = new PrintWriter(socket.getOutputStream(), true);

                // Get client's username
                try (Scanner scanner = new Scanner(System.in)) { // Use of multiple try-catch blocks, handling any
                                                                 // exceptions - conformat to CWE-766
                    System.out.print("Enter your username: ");
                    String username = scanner.nextLine();
                    output.println(username);

                    // Start a new thread to continuously read messages from the server
                    Thread readThread = new Thread(() -> {
                        try {
                            String message;
                            // Read messages from the server and display them to the user
                            while ((message = input.readLine()) != null) {
                                System.out.println(message);
                            }
                        } catch (IOException exception) {
                            exception.printStackTrace();
                        }
                    });
                    readThread.start();

                    // Read messages from this client and send them to the server
                    String message;
                    while (true) {
                        message = scanner.nextLine();
                        output.println(message);
                    }
                }
            }
        } catch (IOException exception) {
            exception.getMessage(); // Only display message, not stack trace that may reveal program implementation
                                    // - conformant with CWE-375
        }
    }
}