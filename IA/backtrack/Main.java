import java.util.ArrayList;



public class Main {

	public static void main(String[] args) {
		String fileName = "dep.txt";
//		try {    
//			fileName = new java.io.File( "." ).getCanonicalPath()+"/"+fileName;
//			System.out.println("Chargement du fichier : "+fileName);
//		}catch(Exception e) {
//	     System.err.println("Erreur lors du chargement du fichier " + fileName);
//			System.err.println(e);
//			return;
//		}
		
		KnowlegdeBase k = Parser.parseBc(fileName);
		k.sature();
		
//		ArrayList<Terme> t1 = new ArrayList<Terme>();
//		t1.add(new Terme(false, "x1"));
//		t1.add(new Terme(false, "y1"));
//		t1.add(new Terme(true, "A"));
//		t1.add(new Terme(false, "x1"));
//		
//		ArrayList<Terme> t2 = new ArrayList<Terme>();
//		t2.add(new Terme(true, "B"));
//		t2.add(new Terme(false, "x2"));
//		t2.add(new Terme(false, "x2"));
//		t2.add(new Terme(false, "y2"));
//		
//		Atome a1 = new Atome(t1);
//		Atome a2 = new Atome(t2);
//		
//		System.out.println(a1.unifiable(a2));
		
//		Homomorphisme h = Parser.parseHomo(fileName);
//		CSP csp = h.toCSP();
	}

}