import java.util.Scanner;

// CWE-20 - This class ensures all input is validated
// CWE-115 - This class ensures all input is interpreted correctly in given contexts
public class GetInput {
    
    /**
     * Takes input from the user and verifies that it is not empty
     * @param inputPrompt Message to display to user before taking input
     * @return String of non-empty input
     */
    public static String getNonEmptyString(String inputPrompt) {
        Scanner sc = new Scanner(System.in);
        String input;
        
        do {
            System.out.print(inputPrompt);
            input = sc.nextLine();
        } while(input.isEmpty());

        sc.close();
        
        return input;
    }
    
    /**
     * Takes input from the user and verifies that it is a valid integer
     * @param inputPrompt Message to display to user before taking input
     * @return Integer of valid input
     */
    public static int getInteger(String inputPrompt) {
        Scanner sc = new Scanner(System.in);
        int input;
        
        do {
            System.out.print(inputPrompt);
        } while(!sc.hasNextInt());
        
        input = sc.nextInt();
        sc.nextLine(); // Consume newline char

        sc.close();
        
        return input;
    }
    
}


