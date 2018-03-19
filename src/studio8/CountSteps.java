package studio8;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class CountSteps {

	public static void main(String args[]) {
		File f = new File("");
		Scanner s;
		try {
			s = new Scanner(f);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
	}

}