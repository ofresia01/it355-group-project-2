package chat_room;

import java.io.*;
import java.net.*;

/*
 * Class responsible for the handling of individual client connections.
 * Runnable thread that takes a Socket and allows for the socket to send and receive messages.
 * No `switch` statements that omit `break`s, conformant with CWE-484
 * No explicit invocation of `finalize()`, conformant with CWE-586
 */
public class ClientHandler extends Thread {
    private Socket socket;
    private BufferedReader input;
    private PrintWriter output;

    public ClientHandler(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
            // Access the socket's input and output streams
            input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            output = new PrintWriter(socket.getOutputStream(), true);

            // Get this client's username
            String username = input.readLine();
            System.out.println(username + " has joined the chat."); // Notify host

            // Continually ingest client messages, send them to ChatServer
            String message;
            while ((message = input.readLine()) != null) {
                System.out.println(username + ": " + message);
                ChatServer.sendMessage(username + ": " + message, this);
            }
        } catch (IOException exception) {
            System.err.println("Client error: " + exception.getMessage());
        } finally {
            try {
                // Connection to client lost - disconnect them from ChatServer
                socket.close();
                ChatServer.removeClient(this);
                System.out.println("Client disconnected");
            } catch (IOException exception) {
                System.err.println("Client error trying to disconnect: " + exception.getMessage());
            }
        }
    }

    /**
     * Method invoked by ChatServer that displays messages from other clients to
     * this client
     * 
     * @param message The message to be displayed.
     */
    public void sendMessage(String message) {
        output.println(message);
    }
}