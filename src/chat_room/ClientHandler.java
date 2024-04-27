package chat_room;

import java.io.*;
import java.net.*;

/*
 * Class responsible for the handling of individual client connections.
 * Runnable thread that takes a Socket and allows for the socket to send and receive messages.
 * No `switch` statements that omit `break`s, conformant with CWE-484
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
            // Compliant with CWE-481, is a comparison to null and not an assignment
            while ((message = input.readLine()) != null) {
                System.out.println(username + ": " + message);
                ChatServer.sendMessage(username + ": " + message, this);

                //Update Messages Recieved in ChatServer.
                ChatServer.addMessageCount();
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

    /**
     * Finalize Method for the ClientHandler Class
     * 
     * This is compliant with CWE-397 because this method needs to catch all
     * possible exceptions and keep on moving.
     * This is not a case where specification is lost due to a generic throw because
     * the specific exception is not important.
     * This is compliant with CWE-568 because super.finalize is called with the
     * finalize method.
     */
    protected void finalize() throws Throwable {
        try {
            System.out.println("Performing Finalize");
            System.out.println("Calling super.finalize");
            super.finalize();
        } catch (Throwable e) {
            throw e;
        }
    }
}