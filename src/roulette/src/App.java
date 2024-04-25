/*
 * Some general CWE compliances in this program:
 * CWE-126 - Buffer over-read is impossible in Java because of ArrayIndexOutOfBoundsException
 * CWE-127 - Buffer under-read is impossible in Java because of ArrayIndexOutOfBoundsException
 * CWE-170 - Java's String class eliminates any issues with null-terminating strings
 * CWE-369 - A division operation never actually occurs, so divide by zero is impossible
 * CWE-252 - Return values are always checked before they are returned
 * CWE-480 - All values are checked before performing operations, so correct operators are used
 * CWE-483 - All blocks are enclosed in {} brackets to ensure correct block delimitation
 */

public class App {
    public static void main(String[] args) throws Exception {
        ReadFile.doReadFile();

        Game.clearConsole();
        System.out.println("Welcome to Java Roulette!" +
                "\nRemember, 99% of gamblers quit right before their biggest win!\n");
        String name = GetInput.getNonEmptyString("Please enter a name to begin: ");

        User user = new User(name); // CWE-908 - User input is non-empty and safe, can initialize user object,
                                    // ensures not null.
        Game.clearConsole();
        System.out.println("Hello " + user.getName() + "! Let's get started." +
                "\nYou will start with a balance of $" + user.getBalance() + ".\n");
        GetInput.anythingToContinue();

        Game.doGameLoop(user);
    }
}
