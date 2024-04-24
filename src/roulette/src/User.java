public class User {
    private String name = "";
    private int balance = 500;
    
    public User(String name) {
        this.name = name;
    } 

    public String getName() {
        return name;
    }
    
    public int getBalance() {
        return balance;
    }

    private void setBalance(int balance) {
        this.balance = balance;
    }

    private void setName(String name) {
        this.name = name;
    }
}
