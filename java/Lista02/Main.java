import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;

public class Main {

	public static int enderecador(String placa, int[] pot) {
		int p;
		int chave = 0;
		char[] aux = placa.toCharArray();
		for (int i = 0; i < placa.length(); i++) {
			p = (int) (aux[i] - 65);
			chave += p * pot[i];
		}
		return chave;
	}

	public static void main(String[] args) {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Scanner in = new Scanner(br);
		int a = 1;
		int mMin = in.nextInt(), fMin = in.nextInt(), fMax = in.nextInt(), chave = -1, auxproc1 = 0, auxproc2 = 0, contador = 0;
		int[] pot = {1, 26, 676, 17576, 456976, 11881376};
		Estacionamento1 e1 = new Estacionamento1(fMax, fMin, mMin);
		Estacionamento2 e2 = new Estacionamento2(fMax, fMin, mMin);
		String comando = in.next(), placa;

		while (!comando.equals("END")) {
			placa = in.next();
			contador += 1;
			if (comando.equals("IN")) {
				chave = enderecador(placa, pot);

				Tupla e1ins = e1.inserir(chave, placa);
				Tupla e2ins = e2.inserir(chave, placa);

				System.out.println(e1ins.first + " " + e1ins.second + " " + e2ins.first + " " + e2ins.second);

				comando = in.next();

			} else if (comando.equals("OUT")) {
				chave = enderecador(placa, pot);

				Tupla e1rem = e1.remover(chave);
				Tupla e2rem = e2.remover(chave);

				System.out.println(e1rem.first + " " + e1rem.second + " " + e2rem.first + " " + e2rem.second);

				comando = in.next();

			} else if (comando.equals("SCH")){
				chave = enderecador(placa, pot);

				Tupla e1proc = e1.procurar(chave);
				Tupla e2proc = e2.procurar(chave);

				System.out.println(e1proc.first + " " + e1proc.second + " " + e2proc.first + " " + e2proc.second);
				comando = in.next();

				if (e1proc.second > auxproc1) {
					auxproc1 = e1proc.second;
				}
				if (e2proc.second > auxproc2) {
					auxproc2 = e2proc.second;
				}
			}
			if(a == 140) {
				a = 140;
			}
			a++;
		}
		System.out.println(auxproc1 + " " + auxproc2);
	}

}

class Tupla {
	int first;
	int second;

	Tupla(int a, int b) {
		this.first = a;
		this.second = b;
	}
}

class Estacionamento1 {
	 int fMin, fMax, mMin, nivelOcupacao, vagasOcupadas, m;
	 No vetor[];
	 Tupla p;

	Estacionamento1(int fMax, int fMin, int mMin) {
		this.fMax = fMax;
		this.mMin = mMin;
		this.m = mMin;
		this.fMin = fMin;
		this.nivelOcupacao = 0;
		this.vagasOcupadas = 0;
		this.p = new Tupla(0,0);
		vetor = new No[m];
		for (int i = 0; i < m; i++) {
			vetor[i] = null;
		}
	}

	int hash(int chave, int k) {
		return (chave % k);
	}

	Tupla inserir(int chave, String valor) {
		if (this.nivelOcupacao * 100 > this.m * this.fMax) {
			int mAtual = m * 2;
			rehashing(mAtual);
			this.m = this.m * 2;
			return auxInserir(chave, valor);
		} else {
			return auxInserir(chave, valor);
		}
	}

	Tupla auxInserir(int chave, String valor) {
		this.p.first = hash(chave, this.m);
		this.p.second = 0;

		while (vetor[p.first] != null) {
			p.second+=1;
			p.first = hash(chave + p.second, this.m);
		}
		
		vetor[p.first] = new No(chave, valor);
		
		this.nivelOcupacao = nivelOcupacao + 1;
		this.vagasOcupadas = vagasOcupadas + 1;
		
		return p;
	}

	Tupla remover(int chave) {
		Tupla p = procurar(chave);

		if (p.first >= 0) {
			vetor[p.first].chave = -1;
			vagasOcupadas -= 1;
			if (100 * vagasOcupadas < m * fMin && m / 2 >= m) {
				int mAtual = m / 2;
				rehashing(mAtual);
				m = m / 2;
			}
		}
		return p;
	}

	Tupla procurar(int chave) {
		Tupla p = new Tupla(hash(chave, m), 0);
		boolean encontrou = false;

		while (vetor[p.first] != null && !encontrou) {
			if (vetor[p.first].chave == chave) {
				if (vetor[p.first].chave > 0) {
					return p;
				} else {
					encontrou = true;
				}
			} else {
				p.second++;
				p.first = hash(chave + p.second, m);
			}
		}
		p.first = -1; p.second = -1;
		
		return p;
	}
	
	void rehashing(int mAtual) {
		vagasOcupadas = 0; nivelOcupacao = 0;
		
		No auxiliar[] = new No[mAtual];
		
		for (int i = 0; i < this.m; i++) {
			if (vetor[i] != null) {
				if(vetor[i].chave != -1) {
					int temp = hash(vetor[i].chave, mAtual);

					while (auxiliar[temp] != null) {
						temp += 1;
						temp = hash(temp, mAtual);
					}

					nivelOcupacao += 1; vagasOcupadas += 1;

					auxiliar[temp] = vetor[i];

				}
			}
		}
		vetor = auxiliar;
	}

}

class Estacionamento2 {
	int fMin, fMax, mMin, m, nivelOcupacao, vagasOcupadas;
	No vetor[];

	Estacionamento2(int fMax, int fMin, int mMin) {
		this.fMax = fMax;
		this.mMin = mMin;
		this.m = mMin;
		this.fMin = fMin;
		this.vagasOcupadas = 0;
		this.nivelOcupacao = 0;
		vetor = new No[m];
		for (int i = 0; i < m; i++) {
			vetor[i] = null;
		}
	}

	Tupla inserir(int chave, String valor) {
		Tupla p = new Tupla(0,0);
		
		if (100 * nivelOcupacao > this.m * fMax) {
			int mAtual = m * 2;
			this.rehashing(mAtual);
			this.m = this.m * 2;
			return auxInserir(chave, valor);
		} else {
			return auxInserir(chave, valor);
		}
	}

	Tupla auxInserir(int chave, String valor) {
		Tupla p = new Tupla(hash(chave, this.m), 0);
		Tupla aux = new Tupla(0,0);

		boolean primeiro = true;
		while (vetor[p.first] != null) {
			int distancia = this.hash(p.first - ((vetor[p.first].chave) % this.m), this.m);
			
			if (distancia >= p.second || vetor[p.first].chave == -1) {
				p.second += 1;
				p.first = this.hash(chave + p.second, this.m);
			} else {
				No auxiliar = new No(vetor[p.first].chave, vetor[p.first].valor);
				vetor[p.first].valor = valor;
				vetor[p.first].chave = chave;
				
				valor = auxiliar.valor;
				chave = auxiliar.chave;
				
				
				if (primeiro) {
					primeiro = false;
					aux.first = p.first;
					aux.second = p.second;
					distancia += 1;
					p.second = distancia;
					p.first = hash(chave + p.second, this.m);
				} else {
					distancia += 1;
					p.second = distancia;
					p.first = hash(chave + p.second, this.m);
				}
			}
		}
		
		this.vetor[p.first] = new No(chave, valor);
		this.nivelOcupacao += 1; this.vagasOcupadas += 1;
		
		if (primeiro) {
			return p;
		} else {
			return aux;
		}
	}


	Tupla remover(int chave) {
		Tupla p = new Tupla(0,0);
		p = this.procurar(chave);
		
		if (p.first >= 0) {
			this.vagasOcupadas -= 1;
			vetor[p.first].chave = -1;
			
			if (this.m / 2 >= this.mMin && 100 * this.vagasOcupadas < this.m * this.fMin ) {
				int mAtual = this.m / 2;
				this.rehashing(mAtual);
				this.m = this.m / 2;
			}
		}
		return p;
	}

	Tupla procurar(int chave) {
		Tupla p = new Tupla(this.hash(chave, this.m), 0);
		
		boolean encontrou = false;
		
		while (vetor[p.first] != null && !encontrou) {
			if (vetor[p.first].chave == chave) {
				if (vetor[p.first].chave > 0) {
					return p;
				} else {
					encontrou = true;
				}
			} else {
				int distancia;
				distancia = this.hash(p.first - ((vetor[p.first].chave) % this.m), this.m);
				p.second += 1;
				p.first = this.hash(chave + p.second, this.m);
			}
		}
		p.first = -1; p.second = -1;
		return p;
	}
	
	int hash(int chave, int k) {
		if (chave >= 0) {
			return (chave % k);
		} else {
			return (chave + k) % k;
		}
	}
	
	void rehashing(int mAtual) {
		this.nivelOcupacao = 0; this.vagasOcupadas = 0;

		No aux[] = new No[mAtual];

		for (int i = 0; i < this.m; i++) {
			if (vetor[i] != null) {
				if(vetor[i].chave != -1) {
					int d = 0;
					int temp = this.hash(vetor[i].chave, mAtual);
					while (aux[temp] != null) {
						int distancia = this.hash((temp - this.hash(aux[temp].chave, mAtual)), mAtual);
						if (distancia >= d) {
							d += 1;
							temp = this.hash(vetor[i].chave + d, mAtual);
						} else {
							No auxiliar = new No(aux[temp].chave, aux[temp].valor);
							aux[temp] = vetor[i];
							vetor[i] = auxiliar;
							d += distancia + 1;
							temp = this.hash(vetor[i].chave + d, mAtual);
						}
					}
					aux[temp] = vetor[i];
					this.nivelOcupacao += 1; this.vagasOcupadas += 1;
				}
			
			}
		}
		this.vetor = aux;
	}
}

class No {
	int chave;
	String valor;

	No(int chave, String valor) {
		this.chave = chave;
		this.valor = valor;
	}
}