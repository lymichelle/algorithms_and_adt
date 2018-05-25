/* Michelle Ly
 mly8
 pa1*/

/*This program will read a file, insert the lines into an array, and store their indices in a doubly linked list in alphabetical order*/

import java.io.*;
import java.util.Scanner;

public class Lex {
	public static void main(String[] args) throws IOException{
		List A = new List();
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		String[] token = null;
		int n, lineNumber = 0;
		if(args.length < 2){
			System.err.println("Usage: FileIO infile outfile");
			System.exit(1);
		}
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));
		while( in.hasNextLine() ){
			lineNumber++;
			line = in.nextLine()+" ";    // add extra space so split works right
		}
		in.close();
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));
		String[] arr = new String[lineNumber];
		for(int i=0; i<lineNumber; i++){
			arr[i] = in.nextLine();
		}
		A.prepend(0);
		for(int j=1; j<lineNumber; j++){
			A.moveFront();	
				while(A.index()>=0){
                			if(arr[j].compareTo(arr[A.get()])<=0){
						A.insertBefore(j);		
						break;
					}
					A.moveNext();
				}
				if(A.index() == -1)
					A.append(j);
			System.out.println(A);
		}
		A.moveFront();
		while(A.index()>=0){
			out.println(arr[A.get()]);
			A.moveNext();
		}
		in.close();
		out.close();
	}
}

