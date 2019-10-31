
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Scanner in = new Scanner(br);
        String operation = in.next(), process, requirement, killed = "";
        int answer = -2;
        Graph graph = new Graph();
        while (!operation.equals("END")) {
            if (operation.equals("REQ")) {
                process = in.next();
                requirement = in.next();
                answer = graph.insert(process, requirement);
                if (answer == -1) {
                    System.out.println("AVAIL");
                } else {
                    System.out.println("WAIT " + answer);
                }

            } else if (operation.equals("FRE")) {
                process = in.next();
                answer = graph.free(process, false);
                System.out.println("TERM " + answer);

            } else if (operation.equals("DLK")) {
                process = in.next();
                if (!graph.dlk(process)) {
                    System.out.println("NONE");
                } else {
                    killed = graph.removeCycle(process, true);
                    System.out.println(killed);
                }
            }
            operation = in.next();

        }

    }
}

class Vertex {

    String name;
    LinkedList<Vertex> pointingOut;
    LinkedList<Vertex> pointingIn;
    boolean visited;
    boolean beingVisited;

    public Vertex(String name) {
        this.name = name;
        this.pointingOut = new LinkedList<>();
        this.pointingIn = new LinkedList<>();
    }

}

class Graph {

    HashMap<String, Vertex> vertixes;
    ArrayList<Vertex> list;

    Graph() {
        this.vertixes = new HashMap<>();
        this.list = new ArrayList<>();
    }

    Vertex exists(String name) {
        if (vertixes.containsKey(name)) {
            Vertex v = vertixes.get(name);
            return v;
        } else {
            Vertex v = new Vertex(name);
            vertixes.put(name, v);
            list.add(v);
            return v;
        }
    }

    int insert(String process, String requirement) {
        Vertex p = this.exists(process);
        Vertex r = this.exists(requirement);

        if (r.pointingOut.isEmpty()) { // se o recurso estiver livre
            r.pointingOut.add(p);
            vertixes.replace(r.name, r);
            p.pointingIn.add(r);
            vertixes.replace(p.name, p);
            return -1; //conseguiu alocar o recurso
        } else {
            if (!p.pointingOut.contains(r)) { // se p n tiver solicitado o recurso ainda
                p.pointingOut.add(r);
                vertixes.replace(p.name, p);
                r.pointingIn.add(p);
                vertixes.replace(r.name, r);
            }
            return r.pointingIn.size();
        }

    }

    public int free(String process, boolean deadlock) {
        Vertex p = vertixes.get(process);

        int liberated = p.pointingIn.size();
        if (deadlock) {
            for (Map.Entry v : vertixes.entrySet()) {
                if (vertixes.get(v.getKey()).pointingIn.contains(p)) {
                    vertixes.get(v.getKey()).pointingIn.remove(p);
                    vertixes.replace(vertixes.get(v.getKey()).name, vertixes.get(v.getKey()));
                }
            }
        }

        for (int i = 0; i < p.pointingIn.size(); i++) {
            Vertex vertex = p.pointingIn.get(i);
            vertex.pointingOut.clear(); // remove apontador do recurso para o processo
            if (vertex.pointingIn.size() > 0) {
                Vertex newPointingOut = vertex.pointingIn.getFirst(); // pega o primeiro da fila
                vertex.pointingOut.add(newPointingOut); // aponta o recurso para o novo processo
                vertex.pointingIn.remove(newPointingOut); // remove o processo que estava na fila
                vertixes.replace(vertex.name, vertex);
                newPointingOut.pointingIn.add(vertex); // adiciona o recurso a lista de recursos do processo
                newPointingOut.pointingOut.remove(vertex); // removendo o recurso da fila
                vertixes.replace(newPointingOut.name, newPointingOut);
            } else {
                vertixes.replace(vertex.name, vertex);
            }
        }
        vertixes.remove(process, p);
        list.remove(p);
        return liberated;
    }
    public boolean dlk(String process) {
        boolean answer = this.hasCycle(process);
        for(Vertex v : list){
            v.visited = false;
            v.beingVisited = false;
        }
        return answer;

    }

    public boolean hasCycle(String process) {
        Vertex sourceVertex = vertixes.get(process);
        sourceVertex.beingVisited = true;

        for (Vertex neighbor : sourceVertex.pointingOut) {
            if (neighbor.beingVisited == true) {
                return true;
            } else if (!neighbor.visited && hasCycle(neighbor.name)) {
                return true;
            }
        }

        sourceVertex.beingVisited = false;
        sourceVertex.visited = true;
        return false;
    }


    String removeCycle(String process, boolean deadlock) {
        Vertex vertex = vertixes.get(process);
        String liberated = ("KILL " + vertex.pointingIn.size() + " " + vertex.pointingOut.size());
        this.free(process, true);
        return liberated;
    }

}
