import java.util.Arrays;
import java.util.Scanner;

// CWE-20 - This class ensures all input is validated
// CWE-115 - This class ensures all input is interpreted correctly in given contexts
public class GetInput {
    private static Scanner sc = new Scanner(System.in);

    /**
     * Takes input from the user and verifies that it is not empty. Used for name
     * 
     * @param inputPrompt Message to display to user before taking input
     * @return String of non-empty input
     */
    public static String getNonEmptyString(String inputPrompt) {
        String input;

        do {
            System.out.print(inputPrompt);
            input = sc.nextLine();
        } while (input.isEmpty());

        return input;
    }

    /**
     * Takes input from the user and verifies that it is a valid integer
     * 
     * @param inputPrompt Message to display to user before taking input
     * @return Integer of valid input
     */
    public static int getBetAmount(String inputPrompt, User user) {
        int input;

        do {
            System.out.print(inputPrompt);
            if (sc.hasNextInt()) {
                input = sc.nextInt();
                if (input > user.getBalance()) {
                    System.out.println("You don't have enough money to make that bet.");
                }
                if (input >= 0 && input <= user.getBalance()) {
                    break;
                }
            }
            sc.nextLine();
        } while (true);

        return input;
    }

    private static final String[] validStrings = { "EN", "ON", "RD", "BK", "SH", "FH", "FT", "ST", "TT", "G" };

    /**
     * Takes input from the user and verifies that it is a valid bet location
     * 
     * @param inputPrompt Message to display to user before taking input
     * @return String of valid bet (EN, ON, RD, BK, SH, FH, FT, ST, TT, G) or 0-36
     */
    public static String getValidBetLoc(String inputPrompt) {
        String input;

        System.out.print(inputPrompt);
        do {
            input = sc.nextLine().toUpperCase();
            if (isNumeric(input)) {
                int number = Integer.parseInt(input);
                if (number < 0 || number > 36) {
                    input = "";
                }
            }
        } while (!isNumeric(input) && !Arrays.asList(validStrings).contains(input));

        return input;

    }

    /**
     * Checks if the given string is a valid numeric value.
     *
     * @param str the string to be checked
     * @return true if the string is a valid numeric value, false otherwise
     */
    private static boolean isNumeric(String str) {
        return str.matches("-?\\d+(\\.\\d+)?");
    }

    @SuppressWarnings("resource")
    public static void anythingToContinue() {
        System.out.print("Press enter to continue...");
        try {
            new java.util.Scanner(System.in).nextLine();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
