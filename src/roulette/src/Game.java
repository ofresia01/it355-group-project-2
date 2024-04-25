import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class Game {
    private static final ArrayList<Integer> redLocs = new ArrayList<Integer>(
            Arrays.asList(1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36));
    private static final ArrayList<Integer> blackLocs = new ArrayList<Integer>(
            Arrays.asList(2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35));

    private Game() {
    };

    /**
     * Executes the game loop for a given user.
     *
     * @param user the user for whom the game loop is executed
     */
    public static void doGameLoop(User user) {
        while (user.getBalance() > 0) {
            clearConsole();
            System.out.println("Your current balance is $" + user.getBalance() + ".");
            System.out.println("The roulette table lies before you. Where will you place your bet?");
            printTable();
            String betLoc = GetInput.getValidBetLoc("Enter a number between 0 and 36 or one of the legend symbols: ");
            int betInt;
            try {
                betInt = Integer.parseInt(betLoc);
            } catch (NumberFormatException e) {
                betInt = -1;
            }
            if (betInt == 37) {
                betInt = 0; // 0 is twice as likely to appear because there are 2 green spots
            }
            int betAmount = GetInput.getBetAmount("Enter a bet amount: ", user);
            user.setBalance(user.getBalance() - betAmount);
            int spinResult = spinWheel();

            clearConsole();
            System.out.println("You chose to place $" + betAmount + " on " + translateBetLoc(betLoc) + ".\n");
            System.out.println("The wheel landed on " + spinResult + "!\n");
            int winMultiplier = 0;
            if (betInt != -1) { // User bet on specific number
                if (betInt == spinResult) {
                    if (betInt == 0) {
                        winMultiplier = 18;
                    } else {
                        winMultiplier = 36;
                    }
                }
            } else {
                switch (betLoc) {
                    case "EN":
                        if (spinResult % 2 == 0) {
                            winMultiplier = 2;
                        }
                        break;
                    case "ON":
                        if (spinResult % 2 == 1) {
                            winMultiplier = 2;
                        }
                        break;
                    case "RD":
                        if (redLocs.contains(spinResult)) {
                            winMultiplier = 2;
                        }
                        break;
                    case "BK":
                        if (blackLocs.contains(spinResult)) {
                            winMultiplier = 2;
                        }
                        break;
                    case "FH":
                        if (spinResult <= 18) {
                            winMultiplier = 2;
                        }
                        break;
                    case "SH":
                        if (spinResult >= 19 && spinResult <= 36) {
                            winMultiplier = 2;
                        }
                        break;
                    case "FT":
                        if (spinResult <= 12) {
                            winMultiplier = 3;
                        }
                        break;
                    case "ST":
                        if (spinResult >= 13 && spinResult <= 24) {
                            winMultiplier = 3;
                        }
                        break;
                    case "TT":
                        if (spinResult >= 25 && spinResult <= 36) {
                            winMultiplier = 3;
                        }
                        break;
                    case "G":
                        if (spinResult == 0) {
                            winMultiplier = 18;
                        }
                        break;
                }
            }

            int winAmount;
            // CWE-667 - Ensures proper locking
            synchronized (user) {
                winAmount = betAmount * winMultiplier;
                user.setBalance(user.getBalance() + winAmount);
            }
            if (winAmount > 0) {
                System.out.println("You won $" + winAmount + "!");
            } else {
                System.out.println("You lost $" + betAmount + ".");
            }
            System.out.println("Your new balance is $" + user.getBalance() + ".\n");
            GetInput.anythingToContinue();
        }

        clearConsole();
        System.out.println(
                "You ran out of money! The game is over for now, but maybe you can consider a second mortgage?\n");
        GetInput.anythingToContinue();
    }

    /**
     * Generates a random number between 0 and 36 to simulate spinning a wheel.
     *
     * @return the randomly generated number
     */
    private static int spinWheel() {
        /*
         * CWE-334 - Space of random values is extremely large, taking up entire integer
         * space.
         */
        return new Random().nextInt(Integer.MAX_VALUE) % 38; // 37 counts as the other Green spot (0)
    }


    /**
     * Clears the console screen by printing control characters.
     */
    public static void clearConsole() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    /**
     * A method to print the table layout and information.
     */
    private static void printTable() {
        String[][] tableLayout = ReadFile.getTableLayout();
        String[] tableInfo = ReadFile.getTableInfo();

        System.out.println("------------------");
        /*
         * CWE-135 - Using length property, we ignore the additional bytes
         * of multi-byte characters in a String
         */
        for (int i = 0; i < tableLayout.length; i++) {
            System.out.print("| ");
            for (int j = 0; j < tableLayout[0].length; j++) {
                if (tableLayout[i][j].length() == 1) {
                    System.out.print(tableLayout[i][j] + "  ");
                } else {
                    System.out.print(tableLayout[i][j] + " ");
                }
            }
            System.out.println("|      " + tableInfo[i]);
        }
        System.out.println("------------------");
        System.out.println("Red: 1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36");
        System.out.println("Black: 2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35\n");
    }

    private static String translateBetLoc(String input) {
        switch (input) {
            case "EN":
                return "Even";
            case "ON":
                return "Odd";
            case "RD":
                return "Red";
            case "BK":
                return "Black";
            case "G":
                return "Green";
            case "SH":
                return "19-36";
            case "FH":
                return "1-18";
            case "FT":
                return "1-12";
            case "ST":
                return "13-24";
            case "TT":
                return "25-36";
            default:
                return input;
        }
    }
}
