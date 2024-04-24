public class Game {
    private Game() {};

    public static void doGameLoop() {
        clearConsole();
        System.out.println("The roulette table lies before you. Where will you place your bets?");
    }

    private static void clearConsole() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }
}
