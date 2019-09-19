import java.util.Scanner;

public class Teste {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		String req = in.nextLine();
		String res = in.nextLine();
		if(req.equals(res)) {
			System.out.println("sim");
		} else {
			System.out.println("não");
		}
	}

}
