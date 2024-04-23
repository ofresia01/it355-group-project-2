package chat_room;

import java.io.*;
import java.net.*;
import java.util.Scanner;

/*
 * Class that represents a client connecting to ChatServer.
 */
public class ChatClient {
    // Network config for ChatServer -- just default localhost
    private static final String SERVER_ADDRESS = "localhost";
    private static final int PORT = 8080;

    public static void main(String[] args) {
        try {
            // Create a socket connection to the server
            try (Socket socket = new Socket(SERVER_ADDRESS, PORT)) {
                // Get the server's input/output streams
                BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter output = new PrintWriter(socket.getOutputStream(), true);

                // Get client's username
                try (Scanner scanner = new Scanner(System.in)) {
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
                        }
                        catch (IOException exception) {
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
        }
        catch (IOException exception) {
            exception.printStackTrace();
        }
    }
}