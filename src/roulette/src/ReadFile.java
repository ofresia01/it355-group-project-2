import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/*
 * ReadFile.java
 * Reads the tableLayout.txt file and populates the tableLayout array.
 * Reads the tableInfo.txt file and populates the tableInfo array.
 */
public class ReadFile {
	// CWE-73 - File paths are immutable.
	private static final String tableLayoutFileName = "src/roulette/src/data/tableLayout.txt";
	private static final String tableInfoFileName = "src/roulette/src/data/tableInfo.txt";
	/*
	 * CWE-120 - The only buffers in the program. They are never copied aside from
	 * their getters, therefore compliant with never copying buffer without checking
	 * size of input.
	 */
	private static String[][] tableLayout = new String[13][5];
	private static String[] tableInfo = new String[15];

	public static String[][] getTableLayout() {
		return tableLayout;
	}

	public static String[] getTableInfo() {
		return tableInfo;
	}

	public ReadFile() {
	}

	/**
	 * Reads the tableLayout.txt file and populates the tableLayout array.
	 * Reads the tableInfo.txt file and populates the tableInfo array.
	 *
	 * @throws IOException if there is an error reading the files
	 */
	public static void doReadFile() {
		// CWE-496 - Only file contents are assigned to private arrays, not public data.
		try {
			BufferedReader br1 = new BufferedReader(new FileReader(tableLayoutFileName));
			String line;
			int row = 0;
			int col = 0;

			while ((line = br1.readLine()) != null) {
				// CWE-187 - Strings are split ONLY on whitespace, prevents partial string
				// comparison later.
				String[] cell = line.split("\\s+");

				for (String item : cell) {
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

			br1.close(); // CWE-910 - Close underlying file descriptor, is not used ever again.

		} catch (IOException e) {
			e.printStackTrace();
		}

		try {
			BufferedReader br2 = new BufferedReader(new FileReader(tableInfoFileName));
			String line;
			int row = 0;

			while ((line = br2.readLine()) != null) {
				tableInfo[row] = line;
				row++;
			}

			br2.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
