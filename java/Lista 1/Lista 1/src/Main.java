import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int m = in.nextInt();
		String comando, expressao, x = "", y = "";
		Stack stack = new Stack();

		for (int i = 0; i < m; i++) {
			comando = in.next();
			if (comando.equals("VAL")) {
				expressao = in.next();
				for (int j = 0; j < expressao.length(); j++) {
					if (expressao.charAt(j) == '0') {
						stack.push("0");
					} else if (expressao.charAt(j) == '1') {
						stack.push("1");
					} else if (expressao.charAt(j) == '~') {
						if (stack.pop().equals("0")) {
							stack.push("1");
						} else {
							stack.push("0");
						}

					} else if (expressao.charAt(j) == '^') {
						x = stack.pop();
						y = stack.pop();
						if (x.equals("1") && y.equals("1")) {
							stack.push("1");
						} else {
							stack.push("0");
						}
					} else if (expressao.charAt(j) == 'v') {
						x = stack.pop();
						y = stack.pop();
						if (x.equals("1") || y.equals("1")) {
							stack.push("1");
						} else {
							stack.push("0");
						}
					} else if (expressao.charAt(j) == '>') {
						x = stack.pop();
						y = stack.pop();
						if (x.equals("0") && y.equals("1")) {
							stack.push("0");
						} else {
							stack.push("1");
						}
					}
				}

			} else {
				expressao = in.next();
				for (int k = 0; k < expressao.length(); k++) {
					if (expressao.charAt(k) == '0') {
						stack.push("0");
					} else if (expressao.charAt(k) == '1') {
						stack.push("1");
					} else if (expressao.charAt(k) == '~') {
						stack.push("(~" + stack.pop() + ")");
					} else if (expressao.charAt(k) == 'v') {
						x = stack.pop();
						y = stack.pop();
						stack.push("(" + y + "v" + x + ")");
					} else if (expressao.charAt(k) == '^') {
						x = stack.pop();
						y = stack.pop();
						stack.push("(" + y + "^" + x + ")");
					} else if (expressao.charAt(k) == '>') {
						x = stack.pop();
						y = stack.pop();
						stack.push("(" + y + ">" + x + ")");
					}
				}
			}
			System.out.println(stack.pop());
		}
	}

}

class Stack {
	public String value;
	public Stack next;

	public Stack() {
		this.next = null;
		this.value = "";
	}

	public String pop() {
		String topItem = "";
		if (this.value == "") {
			topItem = this.next.value;
			this.next = this.next.next;
		}
		return topItem;
	}

	public void push(String value) {
		if (this.value == "") {
			Stack item = new Stack();
			item.next = this.next;
			item.value = value;
			this.next = item;
		} else {
			this.next.push(value);
		}
	}
}