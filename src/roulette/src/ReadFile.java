import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/*
 * ReadFile.java
 * Reads the tableLayout.txt file and populates the tableLayout array.
 */
public class ReadFile {
    private static final String fileName = "src/data/tableLayout.txt"; // CWE-73 - File path is immutable.
	/*
     * CWE-120 - The only buffer in the program. It is never copied, therefore compliant 
     * with never copying buffer without checking size of input.
     */ 
    public static String[][] tableLayout = new String[13][5]; 

    public ReadFile() {}

	public static void doReadFile() {
		try {
			BufferedReader br = new BufferedReader(new FileReader(fileName)); 
			String line;
			int row = 0;
			int col = 0;
			
			while((line = br.readLine()) != null) {
				// CWE-187 - Strings are split ONLY on whitespace, prevents partial string comparison later.
                String[] cell = line.split("\\s+"); 
				
				for(String item : cell) {
                    if (item.equals("XX")) {
                        tableLayout[row][col] = "  ";
                    } else {
                        tableLayout[row][col] = item;
                    }
                    col++;
				}
				row++;
				col = 0;
			}
			
			br.close(); // CWE-910 - Close underlying file descriptor, is not used ever again.
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

